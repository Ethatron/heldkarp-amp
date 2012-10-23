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
//nclude "concrt/ppl_extras.h"

using namespace Concurrency;

/* number of possible parallel branches, this is clamped
 * by the minimum-spanning tree connectivity and by the
 * number of cores
 */
#define PARALLEL_BRANCHES	32

#include "SSE2.h"

/* ********************************************************************************************
 */
namespace tsp_vpuccr_cm {

/* 4-way vectors
 */
const int SIMDsize		= 4;	// in elements (for passed-in memory allocations)
const int AccessAlignment	= 4;	// in elements (for locally allocated memory only)
const int MemoryAlignment	= 16;	// in bytes

/* ********************************************************************************************
 */
#include "../helpers/SBM.h"

template<typename sumtype, typename idxtype>
class PathMem {
protected:
  typedef vector<sumtype, SSE2Allocator<sumtype> > sumvector;
  typedef vector<idxtype, SSE2Allocator<idxtype> > idxvector;

  /* edge matrix with weights applied, the edge weights, and the minimum spanning tree */
  static sumvector
    wghtmatrix[PARALLEL_BRANCHES],		// [numnodes][edgestride]
    weights[PARALLEL_BRANCHES],			//           [edgestride]
    mstree[PARALLEL_BRANCHES];			//           [edgestride]
  static idxvector
    connections[PARALLEL_BRANCHES];		//           [edgestride]
  /* we don't count static_memory against peak_memory */

  /* per-thread memory requirements:
   *
   *  wghtmatrix[numnodes][edgestride][1] ->
   *  weights             [edgestride][1] ->
   *  mstree              [edgestride][1] ->
   *  connections         [edgestride][1] ->
   *
   *  2000 * 2000 * sizeof(double) ->
   *         2000 * sizeof(double) ->
   *         2000 * sizeof(double) ->
   *         2000 * sizeof(short ) ->
   *
   *  32,000,000 bytes
   *      16,000 bytes
   *      16,000 bytes
   *       4,000 bytes
   */

  static int numnodes;		// number of nodes, in elements
  static int edgestride;	// number of one row of edges, in elements, aligned
  static int boolstride;	// number of one row of bools, in bits, aligned

#define	boolulongs()	(boolstride / (sizeof(ulong) * 8))
};

template<typename sumtype, typename idxtype>
class Path : protected SBMatrix< PathMem<sumtype, idxtype> > {
  typedef vector<sumtype, SSE2Allocator<sumtype> > sumvector;
  typedef vector<idxtype, SSE2Allocator<idxtype> > idxvector;

public:
  /* Held-Karp solution */
  sumtype lowerBound;
  int lowestSubgraph;
  int lambdaSteps;

  /* tree of permutations */
  int depth;
  Path *seed;

  idxvector parent;				//           [edgestride]

private:
  /* per-path memory requirements:
   *
   *  parent            [edgestride] ->
   *  included[numnodes][boolstride] ->
   *
   *         2000 * sizeof(short) ->
   *  2000 * 2000 * sizeof(ulong) / 32 ->
   *
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

  /* --------------------------------------------------------------------------------------
   */

  void __fastcall initialize(int firstNeighbor, idxvector &connections) {
    __m128i cval, pval;
    __m128i *cmem = (__m128i *)&connections[0];
    __m128i *pmem = (__m128i *)&this->parent[0];
    size_t length = (sizeof(idxtype) * edgestride + 15) / 16;

    duplicate<idxtype>(firstNeighbor, cval, pval);
    for (size_t j = 0; j < length; j += 1) {      /* memory-controller can manage two out-streams */
      _mm_store_si128(cmem + j, cval);
      _mm_store_si128(pmem + j, pval);
    }

    /* mask out over-aligned connections */
    for (int j = numnodes; j < edgestride; j++)
      connections[j] = 2;
  }

  void connect(int i, int j, sumvector &wghtmatrix, idxvector &connections) {
    this->lowerBound += wghtmatrix[i * edgestride + j];

    /* register new connections */
    connections[i]++;
    connections[j]++;
  }

  /* --------------------------------------------------------------------------------------
   * main function (50-60% of time spend here)
   */

  template<typename edgtype>
  void computeOneTree(int pb, const vector<edgtype> &edgematrix) {
    /* choose the thread-local resources */
    sumvector &weights     = PathMem::weights[pb];
    sumvector &wghtmatrix  = PathMem::wghtmatrix[pb];
    sumvector &mstree      = PathMem::mstree[pb];
    idxvector &connections = PathMem::connections[pb];

    /* compute adjusted costs */
    class minima omi(sizeof(sumtype) == sizeof(double));

    {
      /* localize arrays to pass by assignment */
      sumtype *_weights          = &weights[0];
      sumtype *_wghtmatrix       = &wghtmatrix[0];
      const ulong *_included     = this->raw(pb);
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
	_weights, _edgematrix, _included, _wghtmatrix
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
	  bitfield = _mm_cvtsi32_si128(_included[bitpos >> 5]);
	  /* 00000000000000000000000000000???? */
//	  bitfield = _mm_extracti_si64(bitfield, 4, basebit);
	  bitfield = _mm_srli_epi32(bitfield, basebit);
	  /* 000043210000432100000432100004321 */
	  bitfield = _mm_shufflelo_epi16(bitfield, _MM_SHUFFLE(0, 0, 0, 0));
	  /* 4321----321-----21-------1------- */
	  bitfield = _mm_mullo_epi16(bitfield, _mm_set_epi16(0, 0, 0, 0, (short)(1 << 12), (short)(1 << 13), (short)(1 << 14), (short)(1 << 15)));
	  /* 4-------3-------2--------1------- */
	  bitfield = _mm_and_si128(bitfield, _mm_set_epi16(0, 0, 0, 0, (short)(1 << 15), (short)(1 << 15), (short)(1 << 15), (short)(1 << 15)));
	  bitfield = _mm_unpacklo_epi16(_mm_setzero_si128(), bitfield);

	  if (sizeof(sumtype) == sizeof(double)) {
	    __m128d d01, d23;

	    weightedadd<sumtype, edgtype>(d01, d23, row, col, edgestride, bitfield, _weights, _wghtmatrix, _edgematrix);

	    /* very predictable (only first thread enters this) */
	    if (!row)
	      omi.orderedmin<sumtype>(d01, d23, col, numnodes);
	  }
	  else {
	    __m128 f0123;

	    weightedadd<sumtype, edgtype>(f0123, row, col, edgestride, bitfield, _weights, _wghtmatrix, _edgematrix);

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
    initialize(firstNeighbor, connections);

    /* compute the minimum spanning tree on nodes [1, numnodes - 1] ------------------------ */

    /* calculate length of path */
    this->lowerBound = 0;

    /* add first edge */
    this->connect(0, firstNeighbor, wghtmatrix, connections);
    this->parent[firstNeighbor] = 0;

    report("FS %d %d %f\n", firstNeighbor, secondNeighbor, this->lowerBound);

    /* copy out initial costs from weight-matrix */
    initialize(firstNeighbor, wghtmatrix, mstree);

    /* consume all unassigned edges */
    for (int k = 2, l = 0, h = numnodes; k < numnodes; k++) {
      /* search first unassigned with lowest cost  - - - - - - - - - - - - - - - - - - - - - */
      class minimum mini(sizeof(sumtype) == sizeof(double), numnodes);

      int i = l - SIMDsize;
      while ((i += SIMDsize) < h) {
	__m128i cnum0123;

	// ---- ---- ---- ---- 0001 0034 0156 0000
	cnum0123 = _mm_loadu_si128((__m128i *)&connections[i]);
	// ---- ---- ---- ---- FFFF FFFF FFFF 0000
	cnum0123 = _mm_cmpeq_epi16(cnum0123, _mm_setzero_si128());

	/* 4 shorts == 1 double, prevent NaN compare */
	if (_mm_comineq_sd(_mm_castsi128_pd(_mm_srli_epi16(cnum0123, 2)), _mm_setzero_pd()))
	  mini.unorderedmin(&mstree[0], i, cnum0123);
      }

      i = mini.getBest<sumtype>(l, h);

      report(" %d %g [%d,%d]\n", i, mstree[i], l, h);

      /* add unassigned with lowest cost from "wghtmatrix[i]"  - - - - - - - - - - - - - - - */
      this->connect(i, this->parent[i], wghtmatrix, connections);

      /* reassign costs from "wghtmatrix[i]" - - - - - - - - - - - - - - - - - - - - - - - - */
      __m128i curidx0123 = _mm_set1_epi16(i);

      int j = l - SIMDsize;
      while ((j += SIMDsize) < h) {
	__m128i cnum0123;

	// ---- ---- ---- ---- 0001 0034 0156 0000
	cnum0123 = _mm_loadu_si128((__m128i *)&connections[j]);
	// ---- ---- ---- ---- FFFF FFFF FFFF 0000
	cnum0123 = _mm_cmpeq_epi16(cnum0123, _mm_setzero_si128());

	/* 4 shorts == 1 double, prevent NaN compare */
	if (_mm_comineq_sd(_mm_castsi128_pd(_mm_srli_epi16(cnum0123, 2)), _mm_setzero_pd()))
	  weightedmin(i, j, edgestride, cnum0123, curidx0123, &parent[0], &mstree[0], &wghtmatrix[0]);
      }
    }

    /* add last edge */
    this->connect(0, secondNeighbor, wghtmatrix, connections);
    this->parent[0] = secondNeighbor;

    /* built shortest non-cycle sub-graph -------------------------------------------------- */
    __m128i lidx0123 = _mm_set1_epi16(-1);
    __m128i lnum0123 = _mm_set1_epi16(0x7FFF);

    int j = 0 - SIMDsize;
    while ((j += SIMDsize) < numnodes) {
      __m128i cnum0123;
      __m128i cmsk0123;

      // ---- ---- ---- ---- 0003 0034 0156 0001
      cnum0123 = _mm_loadu_si128((__m128i *)&connections[j]);
      // ---- ---- ---- ---- FFFF FFFF FFFF 0000
      cmsk0123 = _mm_cmpgt_epi16(cnum0123, _mm_set1_epi32(2));

      /* 4 shorts == 1 double, prevent NaN compare */
      if (_mm_comineq_sd(_mm_castsi128_pd(_mm_srli_epi16(cmsk0123, 2)), _mm_setzero_pd()))
	above2min(lnum0123, lidx0123, j, cnum0123);
    }

    /* round-to-nearest, round half towards minus infinity, prevent sum-of-squares problem */
    this->lowerBound = round(this->lowerBound);
    this->lowestSubgraph = above2min(lnum0123, lidx0123);

    report("OT %f %d\n", this->lowerBound, this->lowestSubgraph);
  }

  template<typename edgtype>
  bool computeHeldKarp(int pb, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    /* choose the thread-local resources */
    sumvector &weights     = PathMem::weights[pb];
    idxvector &connections = PathMem::connections[pb];

    this->parent.resize(edgestride);

    /* prepare weights (initially zero) */
    clear(weights);

    this->lowerBound = maxvec<sumtype>();
    this->lowestSubgraph = 0;

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

#if	0
      fprintf(stdout, " l %f,", lambda);
      fprintf(stdout, " lc %5d,", lambda_count);
      fprintf(stdout, " lb %f,", this->lowerBound);
      fprintf(stdout, " ls %2d,", this->lowestSubgraph);
      for (int n = 0; n < numnodes; n++)
	fprintf(stdout, " %3d (%1d)", this->parent[n], connections[n]);
      fprintf(stdout, "\n");
      fflush(stdout);
#endif

      /* cut early */
      if (!(this->lowerBound < bestLowerBound))
	break;
      if (!(this->lowestSubgraph > -1))
	break;
      if (!(this->lowerBound < prevLowerBound))
	lambda *= lambda_reduction;

      /* connections(0)[0] is always "2" */
      __m128i inom0123 = _mm_setzero_si128();

      int j = 0 - SIMDsize;
      while ((j += SIMDsize) < numnodes)
	sumsquares(j, inom0123, &connections[0]);

      if (sizeof(sumtype) == sizeof(double)) {
	__m128d dnom01, dnom23;

	/* reduction */
	sumsquares(dnom01, dnom23, inom0123);

	/* switch, equals "lowestSubgraph == -1"
	if (_mm_ucomieq_sd(dnom01, _mm_setzero_pd()))
	  break; */

	/* embarrassingly parallel */
	__m128d t01, t23;

	// lambda * this->lowerBound / denom
	t01 = _mm_set1_pd((float)lambda);
	t23 = _mm_set1_pd((float)lambda);
	t01 = _mm_mul_pd(t01, _mm_set1_pd((double)this->lowerBound));
	t23 = _mm_mul_pd(t23, _mm_set1_pd((double)this->lowerBound));
	t01 = _mm_div_pd(t01, dnom01);
	t23 = _mm_div_pd(t23, dnom23);

	/* connections(0)[0] is always "2", thus "weight(0)[0]" is always 0 */
	j = 0 - SIMDsize;
	while ((j += SIMDsize) < numnodes)
	  mulsquares(j, t01, t23, &weights[0], &connections[0]);
      }
      else {
	__m128  fnom0123;

	/* reduction */
	sumsquares(fnom0123, inom0123);

	/* switch, equals "lowestSubgraph == -1"
	if (_mm_ucomieq_ss(fnom0123, _mm_setzero_ps()))
	  break; */

	/* embarrassingly parallel */
	__m128 t0123;

	// lambda * this->lowerBound / denom
	t0123 = _mm_set_ps1((float)lambda);
	t0123 = _mm_mul_ps(t0123, _mm_set_ps1((float)this->lowerBound));
	t0123 = _mm_div_ps(t0123, fnom0123);

	/* connections(0)[0] is always "2", thus "weight(0)[0]" is always 0 */
	j = 0 - SIMDsize;
	while ((j += SIMDsize) < numnodes)
	  mulsquares(j, t0123, &weights[0], &connections[0]);
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
    for (int p = 0; p < pb; p++) {
      glob_memory += PathMem::wghtmatrix [p].size() ? sizeof(sumtype) * (numnodes * edgestride) : 0;
      glob_memory += PathMem::weights    [p].size() ? sizeof(sumtype) * (           edgestride) : 0;
      glob_memory += PathMem::mstree     [p].size() ? sizeof(sumtype) * (           edgestride) : 0;
      glob_memory += PathMem::connections[p].size() ? sizeof(idxtype) * (           edgestride) : 0;

      PathMem::wghtmatrix [p].clear();
      PathMem::weights    [p].clear();
      PathMem::mstree     [p].clear();
      PathMem::connections[p].clear();
    }

    SBMatrix::exit(pb);
  }

  template<typename edgtype>
  static Path *setup(int pb, int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    Path *root = new Path();

    /* root node initializes static memories */
    for (int j = 0; j < pb; j++) {
      PathMem::wghtmatrix [j].resize(numnodes * edgestride);
      PathMem::weights    [j].resize(edgestride);
      PathMem::mstree     [j].resize(edgestride);
      PathMem::connections[j].resize(edgestride);
    }

    /* round to full ulongs */
    PathMem::numnodes   =  numnodes;
    PathMem::boolstride = (edgestride + 31) & (~31);
    PathMem::edgestride =  edgestride;

    /* clear out exclusion-matrix */
    root->SBMatrix::setup(pb, numnodes, edgestride);
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

    child->SBMatrix::permute(pb, i, j, *this);
    child->depth = this->depth + 1;
    child->seed = this;
    if (!child->computeHeldKarp(pb, edgematrix, bestLowerBound)) {
      delete child;
      child = NULL;
    }

    return child;
  }
};

vector<float, SSE2Allocator<float> > PathMem<float, short>::weights[PARALLEL_BRANCHES];
vector<float, SSE2Allocator<float> > PathMem<float, short>::wghtmatrix[PARALLEL_BRANCHES];
vector<float, SSE2Allocator<float> > PathMem<float, short>::mstree[PARALLEL_BRANCHES];
vector<short, SSE2Allocator<short> > PathMem<float, short>::connections[PARALLEL_BRANCHES];

int PathMem<float, short>::numnodes;
int PathMem<float, short>::boolstride;
int PathMem<float, short>::edgestride;

vector<double, SSE2Allocator<double> > PathMem<double, short>::weights[PARALLEL_BRANCHES];
vector<double, SSE2Allocator<double> > PathMem<double, short>::wghtmatrix[PARALLEL_BRANCHES];
vector<double, SSE2Allocator<double> > PathMem<double, short>::mstree[PARALLEL_BRANCHES];
vector<short , SSE2Allocator<short > > PathMem<double, short>::connections[PARALLEL_BRANCHES];

int PathMem<double, short>::numnodes;
int PathMem<double, short>::boolstride;
int PathMem<double, short>::edgestride;

#ifdef	CONSERVE_MEMORY
critical_section SBMatrixMem< PathMem<float , short> >::r;
critical_section SBMatrixMem< PathMem<double, short> >::r;
vector<ulong, SSE2Allocator<ulong> > SBMatrixMem< PathMem<float , short> >::continuous[PARALLEL_BRANCHES];
vector<ulong, SSE2Allocator<ulong> > SBMatrixMem< PathMem<double, short> >::continuous[PARALLEL_BRANCHES];
#endif

/* ********************************************************************************************
 */
#include "solver/ConcRT-Priorized.cpp"

#undef	PARALLEL_BRANCHES

}
