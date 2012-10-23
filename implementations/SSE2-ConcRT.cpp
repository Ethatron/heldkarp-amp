/* -----------------------------------------------------------------------------

	Copyright (c) 2012 Niels Fröhling              niels@paradice-insight.us

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to	deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   -------------------------------------------------------------------------- */

#include <assert.h>
#include <ppl.h>

using namespace Concurrency;

/* number of possible parallel branches, this is clamped
 * by the minimum-spanning tree connectivity and by the
 * number of cores
 */
#define PARALLEL_BRANCHES	32

#include "SSE2.h"

/* ********************************************************************************************
 */
namespace tsp_vpuccr {

/* 4-way vectors
 */
const int SIMDsize		= 4;	// in elements (for passed-in memory allocations)
const int AccessAlignment	= 4;	// in elements (for locally allocated memory only)
const int MemoryAlignment	= 16;	// in bytes

/* ********************************************************************************************
 */

template<typename sumtype>
class PathMem {
protected:
  typedef vector<sumtype, SSE2Allocator<sumtype> > sumvector;

  /* edge matrix with weights applied, the edge weights, and the minimum spanning tree */
  static sumvector
    wghtmatrix[PARALLEL_BRANCHES],		// [numnodes][edgestride]
    weights[PARALLEL_BRANCHES],			//           [edgestride]
    mstree[PARALLEL_BRANCHES];			//           [edgestride]
  /* we don't count static_memory against peak_memory */

  /* per-thread memory requirements:
   *
   *  wghtmatrix[numnodes][edgestride][1] ->
   *  weights             [edgestride][1] ->
   *  mstree              [edgestride][1] ->
   *
   *  2000 * 2000 * sizeof(double) ->
   *         2000 * sizeof(double) ->
   *         2000 * sizeof(double) ->
   *
   *  32,000,000 bytes
   *      16,000 bytes
   *      16,000 bytes
   */

  static int numnodes;		// number of nodes, in elements
  static int edgestride;	// number of one row of edges, in elements, aligned
  static int boolstride;	// number of one row of bools, in bits, aligned

#define	boolulongs()	(boolstride / (sizeof(ulong) * 8))
};

template<typename sumtype, typename idxtype>
class Path : protected PathMem<sumtype> {
  typedef vector<idxtype, SSE2Allocator<idxtype> > idxvector;

public:
  /* Held-Karp solution */
  sumtype lowerBound;
  int lambdaSteps;

  /* tree of permutations */
  int depth;
  Path *seed;

  /* number of connections */
  idxvector connections;			//           [edgestride]
  idxvector parent;				//           [edgestride]

private:
  /* exclusion matrix */
  vector<ulong> excluded;			// [numnodes][boolstride]

  /* per-path memory requirements:
   *
   *  connections       [edgestride] ->
   *  parent            [edgestride] ->
   *  excluded[numnodes][boolstride] ->
   *
   *         2000 * sizeof(short) ->
   *         2000 * sizeof(short) ->
   *  2000 * 2000 * sizeof(ulong) / 32 ->
   *
   *    4,000 bytes
   *    4,000 bytes
   *  500,000 bytes
   */

  friend bool operator < (const Path &a, const Path  &b) {
    return (a.lowerBound >= b.lowerBound);
  }

  /* --------------------------------------------------------------------------------------
   * helpers (or optimized)
   */

  static void __fastcall initialize(int firstNeighbor, sumvector &wghtmatrix, sumvector &mstree) {
//  mstree.assign(wghtmatrix.begin() + firstNeighbor * edgestride + 0, wghtmatrix.begin() + firstNeighbor * edgestride + numnodes);

    /* copy out initial costs from weight-matrix */
    for (int j = 0; j < numnodes; j += SIMDsize) {
      if (sizeof(sumtype) == sizeof(double)) {
	_mm_store_pd((double *)&mstree[j + 0], _mm_load_pd((const double *)&wghtmatrix[firstNeighbor * edgestride + j + 0]));
	_mm_store_pd((double *)&mstree[j + 2], _mm_load_pd((const double *)&wghtmatrix[firstNeighbor * edgestride + j + 2]));
      }
      else {
	_mm_store_ps((float  *)&mstree[j + 0], _mm_load_ps((const float  *)&wghtmatrix[firstNeighbor * edgestride + j + 0]));
      }
    }
  }

  static void __fastcall clear(sumvector &weights) {
//  weights.assign(weights.size(), 0);

    for (int j = 0; j < numnodes; j += SIMDsize) {
      if (sizeof(sumtype) == sizeof(double)) {
	_mm_store_pd((double *)&weights[j + 0], _mm_setzero_pd());
	_mm_store_pd((double *)&weights[j + 2], _mm_setzero_pd());
      }
      else {
	_mm_store_ps((float  *)&weights[j + 0], _mm_setzero_ps());
      }
    }

    /* mask out over-aligned weights */
    for (int j = numnodes; j < edgestride; j++)
      weights[j] = maxvec<sumtype>();
  }

  static void clear(vector<ulong> &excluded) {
    excluded.resize(numnodes * boolulongs());
//  excluded.assign(numnodes * boolulongs(), 0);

    memset(&excluded[0], 0, numnodes * boolulongs() * sizeof(ulong));
  }

  static void __fastcall clone(vector<ulong> &dstexcluded, const vector<ulong> &srcexcluded) {
    dstexcluded.resize(numnodes * boolulongs());
//  dstexcluded.assign(srcexcluded.begin(), srcexcluded.end());

    memcpy(&dstexcluded[0], &srcexcluded[0], numnodes * boolulongs() * sizeof(ulong));
  }

  /* --------------------------------------------------------------------------------------
   */

  void __fastcall initialize(int firstNeighbor) {
//  this->connections.assign(this->connections.size(), 0);
//  this->parent.assign(this->parent.size(), firstNeighbor);

    __m128i cval, pval;
    __m128i *cmem = (__m128i *)&this->connections[0];
    __m128i *pmem = (__m128i *)&this->parent[0];
    size_t length = (sizeof(idxtype) * edgestride + 15) / 16;

    duplicate<idxtype>(firstNeighbor, cval, pval);
    for (size_t j = 0; j < length; j += 1) {
      /* memory-controller can manage two out-streams */
      _mm_store_si128(cmem + j, cval);
      _mm_store_si128(pmem + j, pval);
    }

    /* mask out over-aligned connections */
    for (int j = numnodes; j < edgestride; j++)
      this->connections[j] = 2;
  }

  void connect(int i, int j, sumvector &wghtmatrix) {
    this->lowerBound += wghtmatrix[i * edgestride + j];

    /* register new connections */
    this->connections[i]++;
    this->connections[j]++;
  }

  /* --------------------------------------------------------------------------------------
   * main function (50-60% of time spend here)
   */

  template<typename edgtype>
  void computeOneTree(int pb, const vector<edgtype> &edgematrix) {
    /* choose the thread-local resources */
    sumvector &weights    = PathMem::weights[pb];
    sumvector &wghtmatrix = PathMem::wghtmatrix[pb];
    sumvector &mstree     = PathMem::mstree[pb];

    /* compute adjusted costs */
    class minima omi(sizeof(sumtype) == sizeof(double));

    {
      /* localize arrays to pass by assignment */
      sumtype *_weights          = &weights[0];
      sumtype *_wghtmatrix       = &wghtmatrix[0];
      const ulong *_excluded     = &this->excluded[0];
      const edgtype *_edgematrix = &edgematrix[0];

#if _MSC_VER != 1700
      /* < VC2012 can't identify static variables in a class without "this" */
      const int numnodes   = PathMem::numnodes;
      const int edgestride = PathMem::edgestride;
      const int boolstride = PathMem::boolstride;
#endif

      /* embarrassingly parallel */
      parallel_for(0, PathMem::numnodes, 1, [&,
#if _MSC_VER != 1700
	numnodes, edgestride, boolstride,
#endif
	_weights, _edgematrix, _excluded, _wghtmatrix
      ](int row) {

//    for (int row = 0; row < PathMem::numnodes; row += 1) {
#if _MSC_VER == 1700
	const int numnodes   = PathMem::numnodes;
	const int edgestride = PathMem::edgestride;
	const int boolstride = PathMem::boolstride;
#endif
	/* mostly unaligned accesses, take care these are in cache early */
	const edgtype *_edgemem = &_edgematrix[0] + (row + 0) * edgestride + (0);
	_mm_prefetch((const char *)(_edgemem +     0     ), _MM_HINT_T0);
	_mm_prefetch((const char *)(_edgemem + edgestride), _MM_HINT_T1);

	for (int col = 0; col < numnodes; col += SIMDsize) {
	  /* mostly unaligned accesses, take care these are in cache early */
	  const edgtype *_edgemem = &_edgematrix[0] + (row + 0) * edgestride + (col + 16);
	  _mm_prefetch((const char *)(_edgemem +     0     ), _MM_HINT_T0);
	  _mm_prefetch((const char *)(_edgemem + edgestride), _MM_HINT_T1);

	  __m128i bitfield;

	  int bitpos = (row + 0) * boolstride + (col + 0);
	  int basebit = bitpos & 31;

	  /* ----------------010000100????0010 */
	  bitfield = _mm_cvtsi32_si128(_excluded[bitpos >> 5]);
	  /* 00000000000000000000000000000???? */
//	  bitfield = _mm_extracti_si64(bitfield, 4, basebit);
	  bitfield = _mm_srli_epi32(bitfield, basebit);
	  /* 000043210000432100000432100004321 */
	  bitfield = _mm_shufflelo_epi16(bitfield, _MM_SHUFFLE(0, 0, 0, 0));
	  /* 4321----321-----21-------1------- */
	  bitfield = _mm_mullo_epi16(bitfield, _mm_set_epi16(0, 0, 0, 0, (short)(1 << 12), (short)(1 << 13), (short)(1 << 14), (short)(1 << 15)));
	  /* 4-------3-------2--------1------- */
	  bitfield = _mm_and_si128(bitfield, _mm_set_epi16(0, 0, 0, 0, (short)(1 << 15), (short)(1 << 15), (short)(1 << 15), (short)(1 << 15)));
	  bitfield = _mm_xor_si128(bitfield, _mm_set_epi16(0, 0, 0, 0, (short)(1 << 15), (short)(1 << 15), (short)(1 << 15), (short)(1 << 15)));
	  bitfield = _mm_unpacklo_epi16(_mm_setzero_si128(), bitfield);

	  if (sizeof(sumtype) == sizeof(double)) {
	    __m128d d01, d23;

	    weightedadd<sumtype, edgtype>(d01, d23, row, col, edgestride, bitfield, _weights, _wghtmatrix, _edgematrix);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 0) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - DBL_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - (edgematrix[(row + 0) * edgestride + (col + 0)] + weights[(row + 0)] + weights[(col + 0)])) < 0.001);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 1) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - DBL_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - (edgematrix[(row + 0) * edgestride + (col + 1)] + weights[(row + 0)] + weights[(col + 1)])) < 0.001);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 2) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - DBL_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - (edgematrix[(row + 0) * edgestride + (col + 2)] + weights[(row + 0)] + weights[(col + 2)])) < 0.001);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 3) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - DBL_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - (edgematrix[(row + 0) * edgestride + (col + 3)] + weights[(row + 0)] + weights[(col + 3)])) < 0.001);

	    /* very predictable (only first thread enters this) */
	    if (!row)
	      omi.orderedmin<sumtype>(d01, d23, col, numnodes);
	  }
	  else {
	    __m128 f0123;

	    weightedadd<sumtype, edgtype>(f0123, row, col, edgestride, bitfield, _weights, _wghtmatrix, _edgematrix);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 0) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - FLT_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - (edgematrix[(row + 0) * edgestride + (col + 0)] + weights[(row + 0)] + weights[(col + 0)])) < 0.001);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 1) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - FLT_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - (edgematrix[(row + 0) * edgestride + (col + 1)] + weights[(row + 0)] + weights[(col + 1)])) < 0.001);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 2) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - FLT_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - (edgematrix[(row + 0) * edgestride + (col + 2)] + weights[(row + 0)] + weights[(col + 2)])) < 0.001);

	    if (_excluded[bitpos >> 5] & (1 << ((bitpos + 3) & 31)))
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - FLT_MAX) < 0.001);
	    else
	      assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - (edgematrix[(row + 0) * edgestride + (col + 3)] + weights[(row + 0)] + weights[(col + 3)])) < 0.001);

	    /* very predictable (only first thread enters this) */
	    /* very predictable and lots of independencies for OoO */
	    if (!row)
	      omi.orderedmin<sumtype>(f0123, col, numnodes);
	  }
	}
      });
    }

    /* get the two cheapest edges from 0 --------------------------------------------------- */

    int firstNeighbor, secondNeighbor;

    omi.getBest<sumtype>(firstNeighbor, secondNeighbor);

    /* initialize tree */
    initialize(firstNeighbor);

    /* compute the minimum spanning tree on nodes [1, numnodes - 1] ------------------------ */

    /* calculate length of path */
    this->lowerBound = 0;

    /* add first edge */
    this->connect(0, firstNeighbor, wghtmatrix);
    this->parent[firstNeighbor] = 0;

    report("FS %d %d %f\n", firstNeighbor, secondNeighbor, this->lowerBound);

    /* copy out initial costs from weight-matrix */
    initialize(firstNeighbor, wghtmatrix, mstree);

    /* consume all unassigned edges */
    for (int k = 2, l = 0, h = numnodes; k < numnodes; k++) {
#if 0
      /* remember last first found to start next */
      int i, j, g;
      sumtype m;

      /* search first unassigned */
      i = l + 1;
      while (this->connections[i])
	i++;
      l = i - 1;
      g = i + 1;

      /* search next unassigned with lowest cost */
      j = i + 0;
      m = mstree[i];
      while (++j < h) {
	if (!this->connections[j]) {
	  i = (mstree[j] < m ?        j  : i);
	  m = (mstree[j] < m ? mstree[j] : m);

	  g = j + 1;
	}
      }

      h = g;
//    report("%d %g\n", i, mstree[i]);
#else
      /* search first unassigned with lowest cost */
      class minimum mini(sizeof(sumtype) == sizeof(double), numnodes);

      int i = l - SIMDsize;
      while ((i += SIMDsize) < h) {
	__m128i cnum0123;

	// ---- ---- ---- ---- 0001 0034 0156 0000
	cnum0123 = _mm_loadu_si128((__m128i *)&this->connections[i]);
	// ---- ---- ---- ---- FFFF FFFF FFFF 0000
	cnum0123 = _mm_cmpeq_epi16(cnum0123, _mm_setzero_si128());

	/* 4 shorts == 1 double, prevent NaN compare */
	if (_mm_comineq_sd(_mm_castsi128_pd(_mm_srli_epi16(cnum0123, 2)), _mm_setzero_pd()))
	  mini.unorderedmin(&mstree[0], i, cnum0123);
      }

      i = mini.getBest<sumtype>(l, h);

      report(" %d %g [%d,%d]\n", i, mstree[i], l, h);
#endif

      /* add unassigned with lowest cost from "wghtmatrix[i]" */
      this->connect(i, this->parent[i], wghtmatrix);

#if 0
      /* parallel possible */
      int j = l - 1;
      while (++j < h) {
	if (!this->connections[j]) {
	  parent[j] = (mstree[j] > wghtmatrix[i * edgestride + j] ?            i                   : parent[j]);
	  mstree[j] = (mstree[j] > wghtmatrix[i * edgestride + j] ? wghtmatrix[i * edgestride + j] : mstree[j]);

	  report("%d %d %g\n", j, parent[j], mstree[j]);
	}
      }
#else
      __m128i curidx0123 = _mm_set1_epi16(i);

      int j = l - SIMDsize;
      while ((j += SIMDsize) < h) {
	__m128i cnum0123;

	int f = j;
	short p[4];
	sumtype m[4];

	if (!this->connections[f]) {
	  p[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ?            i                   : parent[f]);
	  m[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ? wghtmatrix[i * edgestride + f] : mstree[f]);
	}
	else {
	  p[f % 4] = parent[f];
	  m[f % 4] = mstree[f];
	}

	f++;
	if (!this->connections[f]) {
	  p[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ?            i                   : parent[f]);
	  m[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ? wghtmatrix[i * edgestride + f] : mstree[f]);
	}
	else {
	  p[f % 4] = parent[f];
	  m[f % 4] = mstree[f];
	}

	f++;
	if (!this->connections[f]) {
	  p[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ?            i                   : parent[f]);
	  m[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ? wghtmatrix[i * edgestride + f] : mstree[f]);
	}
	else {
	  p[f % 4] = parent[f];
	  m[f % 4] = mstree[f];
	}

	f++;
	if (!this->connections[f]) {
	  p[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ?            i                   : parent[f]);
	  m[f % 4] = (mstree[f] > wghtmatrix[i * edgestride + f] ? wghtmatrix[i * edgestride + f] : mstree[f]);
	}
	else {
	  p[f % 4] = parent[f];
	  m[f % 4] = mstree[f];
	}

	if ((m[0] < 0) || (m[1] < 0) || (m[2] < 0) || (m[3] < 0)) {
	  int a = 0;
	}
	if ((p[0] == 20) && (p[1] == 33) && (p[2] == 26) && (p[3] == 0)) {
	  if ((m[0] == 7) && (m[1] == 7) && (m[2] == 22) && (m[3] == 0)) {
	    int a = 0;
	  }
	}

	// ---- ---- ---- ---- 0001 0034 0156 0000
	cnum0123 = _mm_loadu_si128((__m128i *)&this->connections[j]);
	// ---- ---- ---- ---- FFFF FFFF FFFF 0000
	cnum0123 = _mm_cmpeq_epi16(cnum0123, _mm_setzero_si128());

	/* 4 shorts == 1 double, prevent NaN compare */
	if (_mm_comineq_sd(_mm_castsi128_pd(_mm_srli_epi16(cnum0123, 2)), _mm_setzero_pd())) {
	  weightedmin(i, j, edgestride, cnum0123, curidx0123, &parent[0], &mstree[0], &wghtmatrix[0]);

	  //report("%d %d %g\n", j+0, parent[j+0], mstree[j+0]);
	  //report("%d %d %g\n", j+1, parent[j+1], mstree[j+1]);
	  //report("%d %d %g\n", j+2, parent[j+2], mstree[j+2]);
	  //report("%d %d %g\n", j+3, parent[j+3], mstree[j+3]);
	}

	f = j % 4;

	assert(parent[j+0] == p[f+0]);
	assert(parent[j+1] == p[f+1]);
	assert(parent[j+2] == p[f+2]);
	assert(parent[j+3] == p[f+3]);

	assert(mstree[j+0] == m[f+0]);
	assert(mstree[j+1] == m[f+1]);
	assert(mstree[j+2] == m[f+2]);
	assert(mstree[j+3] == m[f+3]);
      }
#endif
    }

    /* add last edge */
    this->connect(0, secondNeighbor, wghtmatrix);
    this->parent[0] = secondNeighbor;

    report("OT %f\n", this->lowerBound);

    /* round-to-nearest, round half towards minus infinity, prevent sum-of-squares problem */
    this->lowerBound = round(this->lowerBound);
  }

  template<typename edgtype>
  bool computeHeldKarp(int pb, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    /* choose the thread-local resources */
    sumvector &weights = PathMem::weights[pb];

    this->connections.resize(edgestride);
    this->parent.resize(edgestride);

    /* prepare weights (initially zero) */
    clear(weights);

    this->lowerBound = maxvec<sumtype>();

    /* lagrangian optimization */
    sumtype lambda = (sumtype)0.1;
    int     lambda_count = 0;
    sumtype lambda_reduction = (sumtype)::lambda_reduction;
    sumtype lambda_termination = (sumtype)::lambda_termination;

    while (lambda > lambda_termination) {
      sumtype prevLowerBound = this->lowerBound;

      /* interpretes:
       * - weights (all of it)
       * - edgematrix (all of it)
       *
       * fills:
       * - wghtmatrix (all of it)
       * - degree (all of it)
       * - parent (all of it)
       */
      this->computeOneTree(pb, edgematrix);

      /* cut early */
      if (!(this->lowerBound < bestLowerBound))
	break;
      if (!(this->lowerBound < prevLowerBound))
	lambda *= lambda_reduction;

      {
	/* reduction */
	int denom = 0;
        /* connections[0] is always "2" */
	for (int i = 1; i < numnodes; i++) {
	  int d = (this->connections[i] - 2);
	  denom += d * d;
	}

	/* switch */
	if (denom == 0)
	  break;

	/* embarrassingly parallel */
	sumtype t = lambda * this->lowerBound / denom;
	for (int i = 1; i < numnodes; i++) {
	  weights[i] += t * (this->connections[i] - 2);
	}
      }

      lambda_count++;
    }

    /* is this a possibly shorter path? */
    this->lambdaSteps = lambda_count;
    return (this->lowerBound < bestLowerBound);
  }

public:
  Path() { mst.lock(); curr_memory += sizeof(Path) + sizeof(idxtype) * (edgestride); peak_memory = max(peak_memory, curr_memory); mst.unlock(); }
  virtual ~Path() { mst.lock(); curr_memory -= sizeof(Path) + sizeof(idxtype) * (edgestride); num_iterations += this->lambdaSteps; mst.unlock(); }

  static void exit(int pb) {
    for (int j = 0; j < pb; j++) {
      PathMem::weights[j].clear();
      PathMem::wghtmatrix[j].clear();
      PathMem::mstree[j].clear();
    }
  }

  template<typename edgtype>
  static Path *setup(int pb, int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    Path *root = new Path();

    /* root node initializes static memories */
    for (int j = 0; j < pb; j++) {
      PathMem::weights[j].resize(edgestride);
      PathMem::wghtmatrix[j].resize(numnodes * edgestride);
      PathMem::mstree[j].resize(edgestride);
    }

    /* round to full ulongs */
    PathMem::numnodes   =  numnodes;
    PathMem::boolstride = (edgestride + 31) & (~31);
    PathMem::edgestride =  edgestride;

    /* clear out exclusion-matrix */
    clear(root->excluded);

    /* mask out all j->j edges (specifically 0->0) */
    for (int j = 0; j < numnodes; j++) {
      int bitposj = (j + 0) * boolstride + (j + 0);
      int basebitj = bitposj & 31;

      assert(!(root->excluded[bitposj >> 5] & (1 << basebitj)));

      root->excluded[bitposj >> 5] |= (1 << basebitj);
    }

    root->depth = 0;
    root->seed = NULL;
    root->computeHeldKarp<edgtype>(0, edgematrix, bestLowerBound);

    return root;
  }

  template<typename edgtype>
  Path *permute(int pb, int i, int j, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    /* memory allocation limit */
    if (curr_memory >= memory_limit)
      return NULL;
    /* loop-detection: depth exceeds the possible number of connections */
    if (this->depth >= numnodes)
      return NULL;

    Path *child = new Path();
    if (!child) {
      /* soft-abort, we can continue ignoring this
       * later maybe some memory is free again
       * won't find the optimal solution anymore of course
       */
      return child;
    }

    int bitposi = (i + 0) * boolstride + (j + 0);
    int bitposj = (j + 0) * boolstride + (i + 0);
    int basebiti = bitposi & 31;
    int basebitj = bitposj & 31;

    assert(!(this->excluded[bitposi >> 5] & (1 << basebiti)));
    assert(!(this->excluded[bitposj >> 5] & (1 << basebitj)));

    /* clone out exclusion-matrix */
    clone(child->excluded, this->excluded);
//  child->excluded = this->excluded;

    child->excluded[bitposi >> 5] |= (1 << basebiti);
    child->excluded[bitposj >> 5] |= (1 << basebitj);

    child->depth = this->depth + 1;
    child->seed = this;
    if (!child->computeHeldKarp(pb, edgematrix, bestLowerBound)) {
      delete child;
      child = NULL;
    }

    return child;
  }

  int verify() {
    int i = -1;

    /* search first node with too many connections */
    for (int j = 0; j < numnodes; j++) {
      if ((this->connections[j] > 2)) {
	i = j;

	/* search next node with lowest too many connections */
	for (j = i + 1; j < numnodes; j++) {
	  if ((this->connections[j] > 2) && (this->connections[j] < this->connections[i]))
	    i = j;
	}

	break;
      }
    }

    return i;
  }
};

vector<float, SSE2Allocator<float> > PathMem<float>::weights[PARALLEL_BRANCHES];
vector<float, SSE2Allocator<float> > PathMem<float>::wghtmatrix[PARALLEL_BRANCHES];
vector<float, SSE2Allocator<float> > PathMem<float>::mstree[PARALLEL_BRANCHES];

int PathMem<float>::numnodes;
int PathMem<float>::boolstride;
int PathMem<float>::edgestride;

vector<double, SSE2Allocator<double> > PathMem<double>::weights[PARALLEL_BRANCHES];
vector<double, SSE2Allocator<double> > PathMem<double>::wghtmatrix[PARALLEL_BRANCHES];
vector<double, SSE2Allocator<double> > PathMem<double>::mstree[PARALLEL_BRANCHES];

int PathMem<double>::numnodes;
int PathMem<double>::boolstride;
int PathMem<double>::edgestride;

/* ********************************************************************************************
 */
#include "solver/ConcRT.cpp"

#undef	PARALLEL_BRANCHES

}
