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

/* number of possible parallel branches, this is clamped
 * by the minimum-spanning tree connectivity and by the
 * number of cores
 */
#define PARALLEL_BRANCHES	32

#include "SSE2.h"

/* ********************************************************************************************
 */
namespace tsp_vpu {

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
    wghtmatrix,			// [numnodes][edgestride]
    weights,			//           [edgestride]
    mstree;			//           [edgestride]
  /* we don't count static_memory against peak_memory */

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
  idxvector connections;	//           [edgestride]
  idxvector parent;		//           [edgestride]

private:
  /* exclusion matrix */
  vector<ulong> excluded;	// [numnodes][boolstride]

  friend bool operator < (const Path &a, const Path  &b) {
    return (a.lowerBound >= b.lowerBound);
  }

  /* --------------------------------------------------------------------------------------
   * helpers (or optimized)
   */

  static void initialize(int firstNeighbor, sumvector &wghtmatrix, sumvector &mstree) {
#if 0
    /* very bad, bad bad bad */
    sumvector::iterator b = wghtmatrix.begin() + firstNeighbor * edgestride + 0;
    sumvector::iterator e = wghtmatrix.begin() + firstNeighbor * edgestride + numnodes;

    /* copy out initial costs from weight-matrix */
    mstree.assign(b, e);
#else
//  memcpy(&mstree[0], &wghtmatrix[firstNeighbor * edgestride], numnodes * sizeof(sumtype));
    for (int j = 0; j < numnodes; j += SIMDsize) {
      if (sizeof(sumtype) == sizeof(double)) {
	_mm_store_pd((double *)&mstree[j + 0], _mm_load_pd((const double *)&wghtmatrix[firstNeighbor * edgestride + j + 0]));
	_mm_store_pd((double *)&mstree[j + 2], _mm_load_pd((const double *)&wghtmatrix[firstNeighbor * edgestride + j + 2]));
      }
      else {
	_mm_store_ps((float  *)&mstree[j + 0], _mm_load_ps((const float  *)&wghtmatrix[firstNeighbor * edgestride + j + 0]));
      }
    }
#endif
  }

  static void clear(sumvector &weights) {
#if 0
    /* very bad, bad bad bad */
    weights.assign(weights.size(), 0);
#else
//  memset(&weights[0], 0, edgestride * sizeof(sumtype));

    for (int j = 0; j < numnodes; j += SIMDsize) {
      if (sizeof(sumtype) == sizeof(double)) {
	_mm_store_pd((double *)&weights[j + 0], _mm_setzero_pd());
	_mm_store_pd((double *)&weights[j + 2], _mm_setzero_pd());
      }
      else {
	_mm_store_ps((float  *)&weights[j + 0], _mm_setzero_ps());
      }
    }
#endif

    /* mask out over-aligned weights */
    for (int j = numnodes; j < edgestride; j++)
      weights[j] = maxvec<sumtype>();
  }

  static void clear(vector<ulong> &excluded) {
#if 0
    /* very bad, bad bad bad */
    excluded.resize(numnodes * boolulongs());
    excluded.assign(numnodes * boolulongs(), 0);
#else
    excluded.resize(numnodes * boolulongs());
    memset(&excluded[0], 0, numnodes * boolulongs() * sizeof(ulong));
#endif
  }

  static void clone(vector<ulong> &dstexcluded, const vector<ulong> &srcexcluded) {
#if 0
    /* very bad, bad bad bad */
    vector<ulong>::const_iterator b = srcexcluded.begin();
    vector<ulong>::const_iterator e = srcexcluded.end();

    dstexcluded.resize(srcexcluded.size());
    dstexcluded.assign(b, e);
#else
    dstexcluded.resize(numnodes * boolulongs());
    memcpy(&dstexcluded[0], &srcexcluded[0], numnodes * boolulongs() * sizeof(ulong));
#endif
  }

  /* --------------------------------------------------------------------------------------
   */

  void initialize(int firstNeighbor) {
#if 0
    /* very bad, bad bad bad */
    this->connections.assign(this->connections.size(), 0);
    this->parent.assign(this->parent.size(), firstNeighbor);
#else
//  memset(&this->connections[0], 0, edgestride * sizeof(idxtype));
//  for (int j = 0; j < edgestride; j += 1)
//    this->parent[j] = firstNeighbor;

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
#endif
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
  void computeOneTree(const vector<edgtype> &edgematrix) {
    /* compute adjusted costs */
    class minima omi(sizeof(sumtype) == sizeof(double));

    /* embarrassingly parallel */
    for (int row = 0; row < numnodes; row += 1) {
      /* mostly unaligned accesses, take care these are in cache early */
      const edgtype *_edgemem = &edgematrix[0] + (row + 0) * edgestride + (0);
      _mm_prefetch((const char *)(_edgemem +     0     ), _MM_HINT_T0);
      _mm_prefetch((const char *)(_edgemem + edgestride), _MM_HINT_T1);

      for (int col = 0; col < numnodes; col += SIMDsize) {
	/* mostly unaligned accesses, take care these are in cache early */
	const edgtype *_edgemem = &edgematrix[0] + (row + 0) * edgestride + (col + 16);
	_mm_prefetch((const char *)(_edgemem +     0     ), _MM_HINT_T0);
	_mm_prefetch((const char *)(_edgemem + edgestride), _MM_HINT_T1);

	__m128i bitfield;

	int bitpos = (row + 0) * boolstride + (col + 0);
	int basebit = bitpos & 31;

	/* ----------------010000100????0010 */
	bitfield = _mm_cvtsi32_si128(this->excluded[bitpos >> 5]);
	/* 00000000000000000000000000000???? */
//	bitfield = _mm_extracti_si64(bitfield, 4, basebit);
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

	  weightedadd<sumtype, edgtype>(d01, d23, row, col, edgestride, bitfield, &weights[0], &wghtmatrix[0], &edgematrix[0]);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 0) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - DBL_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - (edgematrix[(row + 0) * edgestride + (col + 0)] + weights[(row + 0)] + weights[(col + 0)])) < 0.001);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 1) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - DBL_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - (edgematrix[(row + 0) * edgestride + (col + 1)] + weights[(row + 0)] + weights[(col + 1)])) < 0.001);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 2) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - DBL_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - (edgematrix[(row + 0) * edgestride + (col + 2)] + weights[(row + 0)] + weights[(col + 2)])) < 0.001);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 3) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - DBL_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - (edgematrix[(row + 0) * edgestride + (col + 3)] + weights[(row + 0)] + weights[(col + 3)])) < 0.001);

	  /* very predictable (only first thread enters this) */
	  if (!row)
	    omi.orderedmin<sumtype>(d01, d23, col, numnodes);
	}
	else {
	  __m128 f0123;

	  weightedadd<sumtype, edgtype>(f0123, row, col, edgestride, bitfield, &weights[0], &wghtmatrix[0], &edgematrix[0]);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 0) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - FLT_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 0)] - (edgematrix[(row + 0) * edgestride + (col + 0)] + weights[(row + 0)] + weights[(col + 0)])) < 0.001);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 1) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - FLT_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 1)] - (edgematrix[(row + 0) * edgestride + (col + 1)] + weights[(row + 0)] + weights[(col + 1)])) < 0.001);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 2) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - FLT_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 2)] - (edgematrix[(row + 0) * edgestride + (col + 2)] + weights[(row + 0)] + weights[(col + 2)])) < 0.001);

	  if (excluded[bitpos >> 5] & (1 << ((bitpos + 3) & 31)))
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - FLT_MAX) < 0.001);
	  else
	    assert(fabs(wghtmatrix[(row + 0) * edgestride + (col + 3)] - (edgematrix[(row + 0) * edgestride + (col + 3)] + weights[(row + 0)] + weights[(col + 3)])) < 0.001);

	  /* very predictable (only first thread enters this) */
	  /* very predictable and lots of independencies for OoO */
	  if (!row)
	    omi.orderedmin<sumtype>(f0123, col, numnodes);
	}
      }
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
    for (int k = 2, l = 1; k < numnodes; k++) {
      /* remember last first found to start next */
      int i, h = numnodes;

      /* search first unassigned */
      for (i = l; i < numnodes; i++) {
	if ((this->connections[i] == 0)) {
	  l = i;
	  break;
	}
      }

      /* search next unassigned with lowest cost */
      for (int j = i + 1; j < numnodes; j++) {
	if (this->connections[j] == 0) {
	  if (mstree[j] < mstree[i])
	    i = j;

	  h = j + 1;
	}
      }

      report(" %d %g [%d,%d]\n", i, mstree[i], l, h);

      /* add unassigned with lowest cost from "wghtmatrix[i]" */
      this->connect(i, this->parent[i], wghtmatrix);

      for (int j = l; j < numnodes; j++) {
	if ((this->connections[j] == 0) && (wghtmatrix[i * edgestride + j] < mstree[j])) {
	  mstree[j] = wghtmatrix[i * edgestride + j];

	  this->parent[j] = i;
	}
      }
    }

    /* add last edge */
    this->connect(0, secondNeighbor, wghtmatrix);
    this->parent[0] = secondNeighbor;

    report("OT %f\n", this->lowerBound);

    /* round-to-nearest, round half towards minus infinity, prevent sum-of-squares problem */
    this->lowerBound = round(this->lowerBound);
  }

  template<typename edgtype>
  bool computeHeldKarp(const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
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
      this->computeOneTree(edgematrix);

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
	for (int i = 1; i < numnodes; i++)
	  weights[i] += t * (this->connections[i] - 2);
      }

      lambda_count++;
    }

    /* is this a possibly shorter path? */
    this->lambdaSteps = lambda_count;
    return (this->lowerBound < bestLowerBound);
  }

public:
  Path() { curr_memory += sizeof(Path) + sizeof(idxtype) * (edgestride); peak_memory = max(peak_memory, curr_memory); }
  virtual ~Path() { curr_memory -= sizeof(Path) + sizeof(idxtype) * (edgestride); num_iterations += this->lambdaSteps; }

  static void exit() {
    PathMem::weights.clear();
    PathMem::wghtmatrix.clear();
    PathMem::mstree.clear();
  }

  template<typename edgtype>
  static Path *setup(int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    Path *root = new Path();

    /* root node initializes static memories */
    PathMem::weights.resize(edgestride);
    PathMem::wghtmatrix.resize(numnodes * edgestride);
    PathMem::mstree.resize(edgestride);

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
    root->computeHeldKarp<edgtype>(edgematrix, bestLowerBound);

    return root;
  }

  template<typename edgtype>
  Path *permute(int i, int j, int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
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
    if (!child->computeHeldKarp(edgematrix, bestLowerBound)) {
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

vector<float, SSE2Allocator<float> > PathMem<float>::weights;
vector<float, SSE2Allocator<float> > PathMem<float>::wghtmatrix;
vector<float, SSE2Allocator<float> > PathMem<float>::mstree;

int PathMem<float>::numnodes;
int PathMem<float>::boolstride;
int PathMem<float>::edgestride;

vector<double, SSE2Allocator<double> > PathMem<double>::weights;
vector<double, SSE2Allocator<double> > PathMem<double>::wghtmatrix;
vector<double, SSE2Allocator<double> > PathMem<double>::mstree;

int PathMem<double>::numnodes;
int PathMem<double>::boolstride;
int PathMem<double>::edgestride;

/* ********************************************************************************************
 */
#include "solver/Plain.cpp"

#undef	PARALLEL_BRANCHES

}
