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
#include <amp.h>
#include <amp_graphics.h>
#include <amp_short_vectors.h>

#include "../helpers/amp/amp_short_arrays.h"

using namespace Concurrency;
using namespace Concurrency::graphics;

/* number of possible parallel branches, this is clamped
 * by the minimum-spanning tree connectivity and by the
 * number of cores
 */
#define PARALLEL_BRANCHES	32

#include "SSE2.h"
#include "AMP.h"

/* ********************************************************************************************
 */
namespace tsp_amp_ccr {

/* 4-way vectors
 * double access-alignment (for reduction)
 */
const int SIMDsize		= 4;	// in elements (for passed-in memory allocations)
const int AccessAlignment	= 8;	// in elements (for locally allocated memory only)
const int MemoryAlignment	= 16;	// in bytes

/* just a marker to know what's up */
#define amp_uav
#define amp_srv

/* execute a block of code only once,
 * use thread "0" for that
 */
#define singlethread(n, func)				\
  if ((tileheight == 1) || !th.local[0]) {		\
    if ((n) == th.local[1]) {				\
      const int j = (n);				\
      func						\
    }							\
  }

/* execute a block of code some chosen times
 */
#define limitedthread(i, n, func)			\
  if ((tileheight == 1) || !th.local[0]) {		\
    if (th.local[1] < (n)) {				\
      const int i = th.local[1];			\
      func						\
    }							\
  }

/* execute a block of code some chosen times
 */
#define wfrontthread(w, func)				\
  if ((tileheight == 1) || !th.local[0]) {		\
    if (th.local[1] < WAVEFRONT_SIZE) {			\
      const int w = th.local[1];			\
      func						\
    }							\
  }

/* execute a block of code over the stride of numnodes,
 * edgesimds is the valid memory region,
 * do this in parallel
 */
#define rangedthread(l, h, func)			\
  if ((tileheight == 1) || !th.local[0]) {		\
    if ((th.local[1] >= (l)) && (th.local[1] < (h))) {	\
      const int j = th.local[1];			\
      func						\
    }							\
  }

/* execute a block of code on all threads in parallel
 */
#define allthread(a, func)				\
  if (1) {						\
    const int a = th.local[1];				\
    func						\
  }

/* execute a block of code over the stride of numnodes,
 * edgesimds is the valid memory region,
 * do this in parallel
 */
#define clampstride(i, e, func)				\
  if (th.local[1] < (e)) {				\
    const int i = th.local[1];				\
    func						\
  }

/* execute a block of code over the size of a wave-front,
 * do this in parallel, any "wavefront-local" conditional
 * won't slow down the code as the entire wavefront sees
 * the same branch(es)
 * this runs in parallel per tileheight (no check)
 */
#define clampwfront(w, func)				\
  if (th.local[1] < WAVEFRONT_SIZE) {			\
    const int w = th.local[1];				\
    func						\
  }

/* execute a block of code over multiple strides of numnodes,
 * edgesimds is the valid memory region,
 * do this in parallel
 */
#define pfrontthread(w, s, e, numnodes, func)		\
  for (int pt = (s); pt < (e); pt += tileheight) {	\
    const int w = pt + th.local[0];			\
    if (w < (numnodes)) {				\
      func						\
    }							\
  }

/* perform a binary reduction, first execute the seeding
 * block of code, then successively apply the reducing
 * block of code until all data is consumed
 *
 * the incoming data doesn't need to be pow2
 */
#define reducethread(max, cond, init, seed, reduce) {	\
  /* globally valid thread-to-location mappings */	\
  const int i  = (th.local[1] << 0) + 0;		\
  const int i0 = (th.local[1] << 1) + 0;		\
  const int i1 = (th.local[1] << 1) + 1;		\
  							\
  int length = ((max) + 1) >> 1; {			\
    if (((tileheight == 1) || !th.local[0]) && (cond)) {\
      if ((th.local[1] < length))			\
        seed						\
      if ((th.local[1] == length) && (length & 1))	\
        init						\
    }							\
    							\
    /* ensure "half" has been calculated */		\
    yield(th, 1);					\
  }							\
  							\
  while ((length = (length + 1) >> 1) > 1) {		\
    if (((tileheight == 1) || !th.local[0]) && (cond)) {\
      if ((th.local[1] < length))			\
	reduce						\
      if ((th.local[1] == length) && (length & 1))	\
        init						\
    }							\
  							\
    /* ensure "quarter" has been calculated */		\
    yield(th, 2);					\
  }							\
  							\
  {							\
    if (((tileheight == 1) || !th.local[0]) && (cond)) {\
      if (th.local[1] < 1)				\
        reduce						\
    }							\
  							\
    /* "broadcast" the result to all other threads	\
     * which is only possible if they stopped here	\
     * and didn't pass					\
     */							\
    yield(th, 0);					\
  }}

/* ********************************************************************************************
 */

// float4 / double4, short4 / int4
template<typename sumvectype, typename idxvectype>
class PathMem {
protected:
public:
  typedef Concurrency::array<sumvectype, 2> wghtgrid;
  typedef Concurrency::array<sumvectype, 1> sumarray;
  typedef Concurrency::array<idxvectype, 1> idxarray;
  typedef Concurrency::graphics::texture<int4, 1> idxtrans;

  /* edge matrix with weights applied, the edge weights, and the minimum spanning tree */
  amp_uav static wghtgrid
    *wghtmatrix[PARALLEL_BRANCHES];		// [numnodes][edgestride]
  amp_uav static sumarray
    *weights[PARALLEL_BRANCHES],		//           [edgestride]
    *mstree[PARALLEL_BRANCHES];			//           [rdctstride]
  amp_uav static idxarray
    *connections[PARALLEL_BRANCHES],		//           [rdctstride]
    *parent[PARALLEL_BRANCHES];			//           [edgestride]
  amp_srv static idxtrans
    *parentx[PARALLEL_BRANCHES];		//           [edgestride]
  /* we don't count static_memory against peak_memory */

  /* per-thread memory requirements:
   *
   *  wghtmatrix[numnodes][edgestride][1] ->
   *  weights             [edgestride][1] ->
   *  mstree              [edgestride][1] ->
   *  connections         [rdctstride][1] ->
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
  static int edgesimds;		// number of one row of edges, in simd-units
  static int edgelog2;		// number of one row of edges, in elements, next pow2
  static int boolstride;	// number of one row of bools, in bits, aligned

#define	boolulongs()	(boolstride / (sizeof(ulong) * 8))
//efine	maxvec()	(sizeof(sumtype) == sizeof(double) ? DBL_MAX : FLT_MAX)
};

template<typename sumtype, typename idxtype, typename sumvectype, typename idxvectype>
class Path : protected PathMem<sumvectype, idxvectype> {
  typedef vector<idxtype, SSE2Allocator<idxtype> > idxvector;
  typedef vector<ulong  , SSE2Allocator<ulong  > > bolvector;

  typedef Concurrency::graphics::writeonly_texture_view<int4, 1>
    idxview;		// write-only
  typedef Concurrency::array_view<const ulong, 2>
    bolview;		// read-only

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
  /* exclusion matrix */
  vector<ulong> included;			// [numnodes][boolstride]

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

  static void __fastcall clear(vector<ulong> &included) {
    included.resize(numnodes * boolulongs());
    memset(&included[0], -1, numnodes * boolulongs() * sizeof(ulong));
  }

  static void __fastcall clone(vector<ulong> &dstincluded, const vector<ulong> &srcincluded) {
    dstincluded.resize(numnodes * boolulongs());
    memcpy(&dstincluded[0], &srcincluded[0], numnodes * boolulongs() * sizeof(ulong));
  }

  /* --------------------------------------------------------------------------------------
   * helpers (or optimized)
   */

  /* ensure the data for one full "tilestride" has been
   * calculated
   *
   * if it is also the task of another wave-front we yield
   * execution to them
   *
   * otherwise it was calculated by the same wave-front
   * this code is in already and we don't need to block
   */
  template<const int tileheight, const int tilestride>
  static void yieldall(tiled_index<tileheight, tilestride> th) restrict(amp,cpu) {
    if ((tilestride * tileheight) > WAVEFRONT_SIZE)
      th.barrier.wait_with_tile_static_memory_fence();
    else
      tile_static_memory_fence(th.barrier);
  }

  template<const int tileheight, const int tilestride>
  static void yield(tiled_index<tileheight, tilestride> th, int substride = 0) restrict(amp,cpu) {
    if ((tilestride >> substride) > WAVEFRONT_SIZE)
      th.barrier.wait_with_tile_static_memory_fence();
    else
      tile_static_memory_fence(th.barrier);
  }

  /* ensure the data just written is available to the other
   * threads in this wave-front (1:N), or if it goes over
   * memory, that it is available to all other wave-fronts
   *
   * the memory fence is stronger than the tile-fence, no
   * need to do both in that case
   */
  template<const int tileheight, const int tilestride>
  static void broadcast(tiled_index<tileheight, tilestride> th, bool istatic = false) restrict(amp,cpu) {
    if ((tilestride * 1) > WAVEFRONT_SIZE) {
      if (!istatic)
	all_memory_fence(th.barrier);
      else
	tile_static_memory_fence(th.barrier);
    }
  }

  /* -------------------------------------------------------------------------------------- */

  template<const int tileheight, const int tilestride>
  static void clear(tiled_index<tileheight, tilestride> th, int numnodes, int edgesimds, sumarray &weights) restrict(amp,cpu) {
    /* mask out over-aligned weights */
    sumvectype l(
      (3 < (SIMDsize - numnodes % SIMDsize) ? maxvec<sumtype>() : 0),
      (2 < (SIMDsize - numnodes % SIMDsize) ? maxvec<sumtype>() : 0),
      (1 < (SIMDsize - numnodes % SIMDsize) ? maxvec<sumtype>() : 0),
      (0 < (SIMDsize - numnodes % SIMDsize) ? maxvec<sumtype>() : 0)
    );

    /* if "numnodes % SIMDsize" == 0, then "numnodes / SIMDsize" == edgesimds (< j) */
    limitedthread(j, (edgesimds), {
      weights(j) = (j == (numnodes / SIMDsize) ? l : 0);
    });

#if 0
    singlethread(numnodes / SIMDsize, {
      /* no indexed access to vector */
      const sumtype m = (sizeof(sumtype) == sizeof(double) ? DBL_MAX : FLT_MAX);
      switch (SIMDsize - numnodes % SIMDsize) {
//	case 0: weights(numnodes / SIMDsize) = sumvectype(m, m, m, m); break;
	case 3: weights(numnodes / SIMDsize) = sumvectype(0, m, m, m); break;
	case 2: weights(numnodes / SIMDsize) = sumvectype(0, 0, m, m); break;
	case 1: weights(numnodes / SIMDsize) = sumvectype(0, 0, 0, m); break;
      }
    });
#endif
  }

  template<const int tileheight, const int tilestride>
  static void initialize(tiled_index<tileheight, tilestride> th, int firstNeighbor, int edgesimds, wghtgrid &wghtmatrix, sumarray &mstree) restrict(amp,cpu) {
    /* ensure "firstNeighbor" has been calculated */
    yieldall(th);

    limitedthread(j, edgesimds, {
      mstree(j) = wghtmatrix(firstNeighbor, j);
    });
  }

  /* --------------------------------------------------------------------------------------
   */

  template<const int tileheight, const int tilestride>
  static void initialize(tiled_index<tileheight, tilestride> th, int firstNeighbor, int numnodes, int edgesimds, idxarray &parent, idxarray &connections) restrict(amp,cpu) {
    /* mask out over-aligned connections */
    idxvectype l(
      (3 < (SIMDsize - numnodes % SIMDsize) ? 2 : 0),
      (2 < (SIMDsize - numnodes % SIMDsize) ? 2 : 0),
      (1 < (SIMDsize - numnodes % SIMDsize) ? 2 : 0),
      (0 < (SIMDsize - numnodes % SIMDsize) ? 2 : 0)
    );

    /* if "numnodes % SIMDsize" == 0, then "numnodes / SIMDsize" == edgesimds (< j) */
    limitedthread(j, edgesimds, {
      parent     (j) = firstNeighbor;
      connections(j) = (j == (numnodes / SIMDsize) ? l : 0);
    });

#if 0
    /* mask out over-aligned connections */
    singlethread(numnodes / SIMDsize, {
      parent(numnodes / SIMDsize) = firstNeighbor;

      /* no indexed access to vector */
      switch (SIMDsize - numnodes % SIMDsize) {
//	case 0: connections(numnodes / SIMDsize) = idxvectype(2, 2, 2, 2); break;
	case 3: connections(numnodes / SIMDsize) = idxvectype(0, 2, 2, 2); break;
	case 2: connections(numnodes / SIMDsize) = idxvectype(0, 0, 2, 2); break;
	case 1: connections(numnodes / SIMDsize) = idxvectype(0, 0, 0, 2); break;
      }
    });
#endif
  }

  static void connect(int i, int j, wghtgrid &wghtmatrix, idxarray &connections, sumtype &lowerBound) restrict(amp,cpu) {
    /* indexed access to vector */
    lowerBound += wghtmatrix(i, j / SIMDsize)[j % SIMDsize];

    /* register new connections */
    connections(i / SIMDsize)[i % SIMDsize]++;
    connections(j / SIMDsize)[j % SIMDsize]++;
  }

  /* --------------------------------------------------------------------------------------
   * main function (50-60% of time spend here)
   */

  template<typename edgtype, typename edgvectype, typename edgresview, const int tileheight, const int tilestride>
  static void computeOneTree(
    tiled_index<tileheight, tilestride> th,
    int4       (&cv)[tilestride >> 1],
    sumvectype (&mv)[tilestride >> 1],
    edgresview &edgematrix,
    wghtgrid    &wghtmatrix,
    sumarray   &weights,
    sumarray   &mstree,
    idxarray   &parent,
    idxarray   &connections,
    bolview     includs,
    int numnodes,
    int edgesimds,
    sumtype &lowerBound,
    int &lowestSubgraph
  ) restrict(amp,cpu) {
    /* divide into 4/32/64 buckets (wavefront size) */
    tile_static struct amphelper::ampminima<sumvectype, int4, tilestride> omi;

    /* VS is very bad at aliasing variables into thread-local storage
     * also no reference-casting, no unions (because of non-trivial
     * constructor ...), bad situation!
     */
//  tile_static int4      cv[tilestride >> 1];
//  tile_static int4      lv[tilestride >> 1];
//  tile_static sumvectype mv[tilestride >> 1];

    /* ensure "weights" has been calculated */
    yield(th);

    /* compute adjusted costs (all rows)
     *
     * this is the only block where the excess threads (> tilestride)
     * are used at all, after this block they'll basically run idle
     */
    pfrontthread(row, 0, numnodes, numnodes, {
      /* vertical */
      sumvectype vwght = weights(row / SIMDsize)[row % SIMDsize];

      /* burst reads for each tile-layout case:
       *
       *  1024x1 ... 32x32 (4-way double) -> 32768 bytes ->  16 bursts of (8 * 256 bytes) -> all channels used
       *  1024x1 ... 32x32 (4-way float ) -> 16384 bytes ->   8 bursts of (8 * 256 bytes)
       *  1024x1 ... 32x32 (4-way ulong ) -> 16384 bytes ->   8 bursts of (8 * 256 bytes)
       *  1024x1 ... 32x32 (4-way ushort) ->  8192 bytes ->   4 bursts of (8 * 256 bytes)
       *  1024x1 ... 32x32 (4-way uchar ) ->  4096 bytes ->   2 bursts of (8 * 256 bytes)
       *
       *  16x16            (4-way double) ->  8192 bytes ->  4/1 burst of (8 * 256 bytes)
       *  16x16            (4-way float ) ->  4096 bytes ->  2/1 burst of (8 * 256 bytes)
       *  16x16            (4-way ulong ) ->  4096 bytes ->  2/1 burst of (8 * 256 bytes)
       *  16x16            (4-way ushort) ->  2048 bytes ->  1/1 burst of (8 * 256 bytes)
       *  16x16            (4-way uchar ) ->  1024 bytes ->  1/2 burst of (8 * 256 bytes)
       *
       *  8x8              (4-way double) ->  2048 bytes ->  1/1 burst of (8 * 256 bytes)
       *  8x8              (4-way float ) ->  1024 bytes ->  1/2 burst of (8 * 256 bytes)
       *  8x8              (4-way ulong ) ->  1024 bytes ->  1/2 burst of (8 * 256 bytes)
       *  8x8              (4-way ushort) ->   512 bytes ->  1/4 burst of (8 * 256 bytes)
       *  8x8              (4-way uchar ) ->   256 bytes ->  1/8 burst of (8 * 256 bytes)
       *
       * texture (slow path): uchar/ushort/ulong
       * array   (fast path): float/double
       */
      clampstride(c, edgesimds, {
      	/* rotate the access pattern in case multiple wavefront/tile_rows
      	 * are active to prevent memory channel bank conflicts
      	 */
      	int col = (c + row) % (edgesimds);

	/* horizontal */
        sumvectype hwght = weights(col);
	sumvectype wght;

	int pos = (col * SIMDsize);
	int basebit = pos & 31;
	int bitfield = includs(row, pos >> 5);

	// wghtmatrix[row * edgestride + col] = edgematrix[row * edgestride + col] + weights[row] + weights[col];
	wght = sumvectype(edgematrix(row, col)) + (vwght + hwght);

	/* GPUs have vectorized cmov */
	wght = amphelper::setenabled(wght, int4(
	  bitfield & (1 << (basebit + 0)),
	  bitfield & (1 << (basebit + 1)),
	  bitfield & (1 << (basebit + 2)),
	  bitfield & (1 << (basebit + 3))
	), sumvectype(maxvec<sumtype>()));

	wghtmatrix(row, col) = wght;
      });
    });

    /* ensure "wghtmatrix[0]" has been calculated */
    yield(th);

    /* horizontal reduction (X to 4/32/64, vectorized, single wave-front) */
    wfrontthread(w, {
      omi.init(w, maxvec<sumtype>());

      /* start & end, clamped to edgesimds */
      int l = min((w + 0) * omi.blcksize, edgesimds);
      int h = min((w + 1) * omi.blcksize, edgesimds);
      for (int col = l; col < h; col++) {
        int pos = (col * SIMDsize);

        int4 curindex = int4(pos + 0, pos + 1, pos + 2, pos + 3);
        sumvectype wght = wghtmatrix(0, col);

        /* assign to one of the 4/32/64 buckets */
        omi.orderedmin(w, wght, curindex);
      }
    });

    /* get the two cheapest edges from 0 --------------------------------------------------- */
    int firstNeighbor  = 0;
    int secondNeighbor = 0;

    /* vertical reduction (4/32/64 to 2, then 2 to 1, vectorized, single wave-front) */
    limitedthread(w, 2, { omi.orderedred2(edgesimds, w); });
    singlethread (   0, { omi.orderedred1(edgesimds   ); });

    /* ensure "omi" is visible to other threads/wavefronts (1:N) */
    broadcast(th, true /* == tile_static */);

    /* horizontal reduction (4-way vector to scalar, suck from thread-local into registers) */
    omi.orderedmallest<sumtype>(firstNeighbor, secondNeighbor);

    /* initialize tree */
    initialize(th, firstNeighbor, numnodes, edgesimds, parent, connections);

    /* compute the length of minimum spanning tree on nodes [1, numnodes - 1] -------------- */
    lowerBound = 0;

    /* copy out initial costs from weight-matrix (waits for "wghtmatrix" being valid) */
    initialize(th, firstNeighbor, edgesimds, wghtmatrix, mstree);

    /* sync-free, wave-fronts are ordered after "initialize" */
    singlethread(0, {
      /* add first edge */
      connect(0, firstNeighbor, wghtmatrix, connections, lowerBound);

      parent(firstNeighbor / SIMDsize)[firstNeighbor % SIMDsize] = 0;
    });

    /* ensure "connect[]" and "parent[]" is visible to other threads/wavefronts */
    broadcast(th, false /* == memory */);

    /* consume all unassigned edges */
    for (int k = 2, l = 0, h = edgesimds; k < numnodes /* * !th.local[1] */; k++) {
      /* search first unassigned with lowest cost  - - - - - - - - - - - - - - - - - - - - - */
      /* ensure "parent[]" and "mstree[]" has been calculated */
      yield(th);

      reducethread(h, 1, {
	/* pad binary reduction "overflow" */
	mv[length] = sumvectype(maxvec<sumtype>());
      }, {
	int pos0 = (i0 * SIMDsize);
	int pos1 = (i1 * SIMDsize);

	/* excess connections are neutral "2" */
	int4 curindex0 = int4(pos0 + 0, pos0 + 1, pos0 + 2, pos0 + 3);
	int4 curindex1 = int4(pos1 + 0, pos1 + 1, pos1 + 2, pos1 + 3);
	int4 con0 = connections(i0);
	int4 con1 = connections(i1);

	/* skip connections of "> 0" (assign MAX, voids the "smaller") */
	sumvectype mstv0 = mstree(i0);
	sumvectype mstv1 = mstree(i1);

	/* GPUs have vectorized cmov */
	mstv0 = amphelper::setdisabled(mstv0, con0, sumvectype(maxvec<sumtype>()));
	mstv1 = amphelper::setdisabled(mstv1, con1, sumvectype(maxvec<sumtype>()));

	/* maintain lower index in case of equality */
	cv[i] = amphelper::smaller(mstv1, mstv0, curindex1, curindex0);
	mv[i] = amphelper::smaller(mstv1, mstv0,     mstv1,     mstv0);
      }, {
	cv[i] = amphelper::smaller(mv[i1], mv[i0], cv[i1], cv[i0]);
	mv[i] = amphelper::smaller(mv[i1], mv[i0], mv[i1], mv[i0]);
      });

      /* add unassigned with lowest cost - - - - - - - - - - - - - - - - - - - - - - - - - - */
      int i = amphelper::usmallest(cv[0], mv[0]);

      /* sync-free, wave-fronts are ordered after "reducethread" */
      singlethread(0, {
	/* add next edge */
	connect(parent(i / SIMDsize)[i % SIMDsize], i, wghtmatrix, connections, lowerBound);
      });

      /* ensure "connect[]" and "parent[]" is visible to other threads/wavefronts */
      broadcast(th, false /* == memory */);

      /* reassign costs  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
      int4 iv = i;

      rangedthread(l, h, {
	int pos = (j * SIMDsize);

	/* excess connections are neutral "2" */
	int4 curindex = int4(pos + 0, pos + 1, pos + 2, pos + 3);
	int4 con = connections(j);

	/* skip connections of "> 0" (assign MAX, voids the "greater") */
	sumvectype wght = wghtmatrix(i, j);
	sumvectype mstv = mstree(j);

	/* GPUs have vectorized cmov */
	wght = amphelper::setdisabled(wght, con, sumvectype(maxvec<sumtype>()));

	/* maintain lower index in case of equality */
	parent(j) = amphelper::greater(mstv, wght, iv, parent(j));
	mstree(j) = amphelper::greater(mstv, wght, wght, mstv);
      });
    }

    /* sync-free, wave-fronts are ordered after "reducethread" */
    singlethread(0, {
      /* add last edge */
      connect(0, secondNeighbor, wghtmatrix, connections, lowerBound);
      parent(0).x = secondNeighbor;
    });

    /* ensure "connections[]" and "parent[]" is visible to other threads/wavefronts */
    broadcast(th, false /* == memory */);

    /* built shortest non-cycle sub-graph -------------------------------------------------- */
    reducethread(edgesimds, 1, {
      /* pad binary reduction "overflow" */
      mv[length] = 0x7FFF0000;
    },{
      int pos0 = (i0 * SIMDsize);
      int pos1 = (i1 * SIMDsize);

      /* excess connections are neutral "2" */
      int4 curindex0 = int4(pos0 + 0, pos0 + 1, pos0 + 2, pos0 + 3);
      int4 curindex1 = int4(pos1 + 0, pos1 + 1, pos1 + 2, pos1 + 3);
      /* -2 wraparound signflip, 16bit in 23 mantissa fixup */
      idxvectype con0 = (connections(i0) << 16) + 0x7FFD0000;
      idxvectype con1 = (connections(i1) << 16) + 0x7FFD0000;
      /*	fixed			  unfixed (doesn't fit into float)
       *
       * 0 ->	0x7FFD0000 -> 4EFFFA00    0x7FFFFFFD -> 4F000000
       * 1 ->	0x7FFE0000 -> 4EFFFC00    0x7FFFFFFE -> 4F000000
       * 2 -> 	0x7FFF0000 -> 4EFFFE00    0x7FFFFFFF -> 4F000000
       * 3 ->	0x80000000 -> CF000000    0x80000000 -> CF000000
       * 4 ->	0x80010000 -> CEFFFE00    0x80000001 -> CF000000
       * ...
       */

      /* maintain lower index in case of equality */
      cv[i] = idxvectype(amphelper::smaller(con1, con0, curindex1, curindex0));
      mv[i] = sumvectype(amphelper::smaller(con1, con0,      con1,      con0));
    }, {
      cv[i] = idxvectype(amphelper::smaller(mv[i1], mv[i0], cv[i1], cv[i0]));
      mv[i] = sumvectype(amphelper::smaller(mv[i1], mv[i0], mv[i1], mv[i0]));
    });

    /* sync-free, wave-fronts are ordered after "reducethread" */
    singlethread(0, {
      /* broadcast lowerBound to all threads */
      mv[1].x = lowerBound;
    });

    broadcast(th, true /* == tile_static */);

    /* round-to-nearest, round half towards minus infinity, prevent sum-of-squares problem */
    lowerBound = amphelper::round(mv[1].x);
    lowestSubgraph = amphelper::usmallestneg(cv[0], mv[0]);
  }

  template<typename edgtype, typename edgvectype, typename edgresview, const int tileheight, const int tilestride>
  bool computeHeldKarp(int pb, edgresview &edgematrix, sumtype bestLowerBound) {
    /* choose the group-local resources */
    amp_uav wghtgrid &wghtmatrix = *(PathMem::wghtmatrix[pb]);
    amp_uav sumarray &weights = *(PathMem::weights[pb]);
    amp_uav sumarray &mstree = *(PathMem::mstree[pb]);
    amp_uav idxarray &parent = *(PathMem::parent[pb]);
    amp_srv idxtrans &parentx = *(PathMem::parentx[pb]);
    amp_uav idxarray &connections = *(PathMem::connections[pb]);

    int numnodes   = PathMem::numnodes;
    int edgestride = PathMem::edgestride;
    int edgesimds  = PathMem::edgesimds;
    int boolstride = PathMem::boolstride;

    /* fake extent, go for maximum threads */
    Concurrency::extent<2> ee(tileheight, tilestride);
    Concurrency::tiled_extent<tileheight, tilestride> te(ee);

    /* parents should be write-only, includes read-only */
    idxview parents(parentx);
    bolview includs(numnodes, boolulongs(), &this->included[0]);

    /* unfortunately read-back is necessary */
    struct gpuio {
      sumtype currLambda;
      int currLambdaCount;
      sumtype currLowerBound;
      int currLowestSubgraph;
    } gpustate = {
      (sumtype)0.1,
      0,
      this->lowerBound,
      this->lowestSubgraph
    };

    Concurrency::array_view<struct gpuio, 1> persistant(1, &gpustate);

    /* lagrangian optimization */
    sumtype lambda = (sumtype)0.1;
    int     lambda_count = 0;
    sumtype lambda_reduction = (sumtype)::lambda_reduction;
    sumtype lambda_termination = (sumtype)::lambda_termination;

    while (lambda > lambda_termination) {
      /* run the algorithm in bursts of loops
       *
       * calculate the minimum number of iteration to get to the goal
       * without considering bestLowerBound breaks
       */
      int lambda_iterations = 0;
      sumtype lambda_test = lambda;
      while (lambda_test > lambda_termination)
	lambda_test *= lambda_reduction,
	lambda_iterations++;

      /* take the abortion rate of the seeding path into account
       * if it was very high we don't issue a large block but try
       * with its number of iteration as maximum first
       */
      if (this->seed)
	lambda_iterations = min(lambda_iterations, this->seed->lambdaSteps);
	lambda_iterations = max(lambda_iterations, 1);

      /* the loop can be outer or inner
       *
       * as the synchronize() is extreme slow (200x the parallel_for_each) and
       * the inner loop freezes on my 5870, we just issue the loop outside
       * without even looking at what's going on on the GPU
       */
//    lambda_iterations = 1;
      for (int li = 0; li < lambda_iterations; li++) {
        Concurrency::parallel_for_each(te, [=,
	  &edgematrix,
	  &wghtmatrix,
	  &weights,
	  &mstree,
	  &parent,
	  &connections
        ](tiled_index<tileheight, tilestride> th) restrict(amp) {
          /* shared memory limits (int4 + sumvectype):
           *
           *  1024x 1 (512x 4-way int + double) -> 8192 + 16384 -> 24576 ok
           *  1024x 1 (512x 4-way int + float ) -> 8192 +  8192 -> 16384 ok
           *
           *   512x 2 (256x 4-way int + double) -> 4096 +  8192 -> 12288 ok
           *   512x 2 (256x 4-way int + float ) -> 4096 +  4096 ->  8192 ok
           *
           *   256x 4 (128x 4-way int + double) -> 2048 +  4096 ->  6144 ok
           *   256x 4 (128x 4-way int + float ) -> 2048 +  2048 ->  4096 ok
           *
           *   128x 8 ( 64x 4-way int + double) -> 1024 +  2048 ->  3072 ok
           *   128x 8 ( 64x 4-way int + float ) -> 1024 +  1024 ->  2048 ok
           *
           *    64x16 ( 32x 4-way int + double) ->  512 +  1024 ->  1536 ok
           *    64x16 ( 32x 4-way int + float ) ->  512 +   512 ->  1024 ok
           *
           *    32x32 ( 16x 4-way int + double) ->  256 +   512 ->   768 ok
           *    32x32 ( 16x 4-way int + float ) ->  256 +   256 ->   512 ok
           *
           *    16x16 (  8x 4-way int + double) ->  128 +   256 ->   384 ok
           *    16x16 (  8x 4-way int + float ) ->  128 +   128 ->   256 ok
           *
           *     8x 8 (  4x 4-way int + double) ->   64 +   128 ->   192 ok
           *     8x 8 (  4x 4-way int + float ) ->   64 +    64 ->   128 ok
           */
	  /* shared reduction vars */
	  tile_static int4      cv[tilestride >> 1];
	  tile_static sumvectype mv[tilestride >> 1];

          /* shared cache requirements (2x int4 + sumvectype):
           *
           *  1024x 1 (1024x2 4-way int + 1024x1 double) -> 32768 + 32768 -> 65536 bigger
           *  1024x 1 (1024x2 4-way int + 1024x1 float ) -> 32768 + 16384 -> 49152 bigger
           *
           *   512x 2 ( 512x2 4-way int +  512x1 double) -> 16384 + 16384 -> 32768 ok
           *   512x 2 ( 512x2 4-way int +  512x1 float ) -> 16384 +  8192 -> 24576 ok
           *
           *   256x 4 ( 256x2 4-way int +  256x1 double) ->  8192 +  8192 -> 16384 ok
           *   256x 4 ( 256x2 4-way int +  256x1 float ) ->  8192 +  4096 -> 12288 ok
           *
           *   128x 8 ( 128x2 4-way int +  128x1 double) ->  4096 +  4096 ->  8192 ok
           *   128x 8 ( 128x2 4-way int +  128x1 float ) ->  4096 +  2048 ->  6144 ok
           *
           *    64x16 (  64x2 4-way int +   64x1 double) ->  2048 +  2048 ->  4096 ok
           *    64x16 (  64x2 4-way int +   64x1 float ) ->  2048 +  1024 ->  3072 ok
           *
           *    32x32 (  32x2 4-way int +   32x1 double) ->  1024 +  1024 ->  2048 ok
           *    32x32 (  32x2 4-way int +   32x1 float ) ->  1024 +   512 ->  1536 ok
           *
           *    16x16 (  16x2 4-way int +   16x1 double) ->   512 +   512 ->  1024 ok
           *    16x16 (  16x2 4-way int +   16x1 float ) ->   512 +   256 ->   768 ok
           *
           *     8x 8 (   8x2 4-way int +    8x1 double) ->   256 +   256 ->   512 ok
           *     8x 8 (   8x2 4-way int +    8x1 float ) ->   256 +   128 ->   384 ok
           *
           * combined shared requirements (2.5x int4 + 1.5x sumvectype):
           *
           *  1024x 1 -> 8192 + 16384 + 32768 + 32768 -> 24576 + 65536 -> 90112 bigger
           *  1024x 1 -> 8192 +  8192 + 32768 + 16384 -> 16384 + 49152 -> 65536 bigger
           *
           *   512x 2 -> 4096 +  8192 + 16384 + 16384 -> 12288 + 32768 -> 45056 bigger
           *   512x 2 -> 4096 +  4096 + 16384 +  8192 ->  8192 + 24576 -> 32768 ok
           *
           *   256x 4 -> 2048 +  4096 +  8192 +  8192 ->  6144 + 16384 -> 22528 ok
           *   256x 4 -> 2048 +  2048 +  8192 +  4096 ->  4096 + 12288 -> 16384 ok
           *
           *   128x 8 -> 1024 +  2048 +  4096 +  4096 ->  3072 +  8192 -> 11264 ok
           *   128x 8 -> 1024 +  1024 +  4096 +  2048 ->  2048 +  6144 ->  8192 ok
           *
           *    64x16 ->  512 +  1024 +  2048 +  2048 ->  1536 +  4096 ->  5632 ok
           *    64x16 ->  512 +   512 +  2048 +  1024 ->  1024 +  3072 ->  4096 ok
           *
           *    32x32 ->  256 +   512 +  1024 +  1024 ->   768 +  2048 ->  2816 ok
           *    32x32 ->  256 +   256 +  1024 +   512 ->   512 +  1536 ->  2048 ok
           *
           *    16x16 ->  128 +   256 +   512 +   512 ->   384 +  1024 ->  1408 ok
           *    16x16 ->  128 +   128 +   512 +   256 ->   256 +   768 ->  1024 ok
           *
           *     8x 8 ->   64 +   128 +   256 +   256 ->   192 +   512 ->   704 ok
           *     8x 8 ->   64 +    64 +   256 +   128 ->   128 +   384 ->   512 ok
           */
	  /* shared cache vars
	  tile_static sumvectype wg[tilestride];
	  tile_static int4      pt[tilestride];
	  tile_static int4      cn[tilestride];
	   */

	  /* read persistant GPU-data into registers
	   * maintain across-call coherency, don't use constant buffers
	   */
	  sumtype currLambda         = persistant(0).currLambda;
	  int     currLambdaCount    = persistant(0).currLambdaCount;
	  sumtype prevLowerBound     = persistant(0).currLowerBound;
	  int     currLowestSubgraph = persistant(0).currLowestSubgraph;
//	  sumtype bestLowerBound     = persistant(0).bestLowerBound;
//	  sumtype currLowerBound     = persistant(0).currLowerBound;
	  sumtype currLowerBound     = 0;

	  /* prepare weights (initially zero) */
	  if (!currLowestSubgraph)
	    clear(th, numnodes, edgesimds, weights);

#if 0	// dead-locks for unknown reasons on AMD 5870 (all of them, even the static)
	  tile_static int li;
	  yieldall(th);
	  singlethread(0, {
	    li = 0;
	  });
	  yieldall(th);
//	  while (currLambda > lambda_termination) {
//	  for (int li = 0; li < lambda_iterations; li++)
//	  for (int li = 0; li < 1; li++)
	  while (li < 1)
#endif
	  {
	    /* interpretes:
	     * - weights (all of it)
	     * - edgematrix (all of it)
	     *
	     * fills:
	     * - wghtmatrix (all of it)
	     * - parent (all of it)
	     * - connections (all of it)
	     */

	    computeOneTree<edgtype, edgvectype, edgresview, tileheight, tilestride>(
	      th,
	      cv,
	      mv,
	      edgematrix,
	      wghtmatrix,
	      weights,
	      mstree,
	      parent,
	      connections,
	      includs,
	      numnodes,
	      edgesimds,
	      currLowerBound,
	      currLowestSubgraph
	    );

	    /* CODEBUG: "notdone" apparently isn't calculated correctly */
#define notdone                     /* better than best, and not yet a valid path */	\
	     ((currLambda > lambda_termination) &&	/* regular loop condition */	\
	      (currLowestSubgraph > -1) &&		/* early loop termination */	\
	      (currLowerBound < bestLowerBound))	/* early loop termination */	\

	    /* upper bound for denom:
	     *  (1) * (numnodes * numnodes) + (numnodes - 1) * (-2 * -2)
	     *
	     * =>  51 =>   2805
	     * =>  76 =>   6076
	     * => 101 =>  10601
	     * => 202 =>  41608
	     * => 431 => 187481
	     */

	    /* cut early, binary parallel sum */
	    reducethread(edgesimds, notdone, {
	      /* pad binary reduction "overflow" */
	      cv[length] = 0;
	    }, {
	      /* excess connections are neutral "2" */
	      int4 d0 = (connections(i0) - 2);
	      int4 d1 = (connections(i1) - 2);

	      cv[i] = d0 * d0 + d1 * d1;
	    }, {
	      cv[i] =  cv[i0] +  cv[i1];
	    });

	    if (notdone) {
	      if (!(currLowerBound < prevLowerBound)) {
	        currLambda *= lambda_reduction;
	        currLambdaCount++;
	      }

	      /* if zero all are == 2 */
	      int denom = cv[0].x + cv[0].y + cv[0].z + cv[0].w;
	      if (denom != 0) {
	        /* readjust weights */
	        sumvectype t = currLambda * currLowerBound / denom;
	        limitedthread(j, edgesimds, {
	          weights(j) = weights(j) + t * sumvectype(connections(j) - 2);
	        });

	        /* exclude first (thread "0" wrote the first, so no race condition) */
	        singlethread(0, {
	          weights(0).x = 0;
	        });

	        prevLowerBound = currLowerBound;
	      }
	    }

	    /* no use, it's worst or it's the best
	    if (!notdone)
	      break; */

#if 0	// dead-locks for unknown reasons on AMD 5870
	    yieldall(th);
	    singlethread(0, {
	      li = li + 1;
	    });
	    yieldall(th);
#endif
	  }

#if 0	// crashes for unknown reasons on AMD 5870
	  /* flush out "parent" to write-only texture (with type-conversion) */
	  if (currLambda <= lambda_termination) {
	    limitedthread(j, edgesimds, {
	      parents.set(index<1>(j), parent(j));
	    });
	  }
#endif

	  /* write out persistant GPU-data */
	  singlethread(0, {
	    /* - "notdone" is always true apparently, bug?
	     * - "currLambdaCount + ((currLowerBound < bestLowerBound) && (currLowestSubgraph > -1) ? 1 : 0)"
	     *   crashes for unknown reasons on AMD 5870
	     */
	    persistant(0).currLambda         = currLambda;
	    persistant(0).currLambdaCount    = currLambdaCount + (/*(currLowerBound < bestLowerBound) &&*/ (currLowestSubgraph > -1) ? 1 : 0);
	    persistant(0).currLowerBound     = currLowerBound;
	    persistant(0).currLowestSubgraph = currLowestSubgraph;
	  });
        });
      }

      /* synchronize persistant GPU-data */
      persistant.synchronize();

      /* update path-data */
      this->lowerBound     = gpustate.currLowerBound;
      this->lowestSubgraph = gpustate.currLowestSubgraph;

#if 1
      // ndef NDEBUG
      {
	int reductionstride = (edgestride + AccessAlignment - 1) & (~(AccessAlignment - 1));
	int reductionsimds = reductionstride / SIMDsize;
	vector<int> conns(SIMDsize * reductionsimds);
	array_view<int4, 1> connv(reductionsimds, (int4 *)&conns[0]);
        Concurrency::extent<1> ec(edgesimds);
        Concurrency::parallel_for_each(ec, [=,
	  &parent
        ](index<1> j) restrict(amp) {
	  parents.set(j, parent(j));
        });
        copy(parentx, &this->parent[0], (unsigned int)(this->parent.size() * sizeof(idxtype)));
        copy(connections, connv);
	connv.synchronize();
        fprintf(stdout, " l %f,", lambda);
        fprintf(stdout, " lc %5d,", lambda_count);
        fprintf(stdout, " lb %f,", this->lowerBound);
        fprintf(stdout, " ls %2d,", this->lowestSubgraph);
        for (int n = 0; n < numnodes; n++)
	  fprintf(stdout, " %3d (%1d)", this->parent[n], conns[n]);
        fprintf(stdout, "\n");
	fflush(stdout);
      }
#endif // !NDEBUG

      /* update loop variable */
      lambda = gpustate.currLambda;
      lambda_count = gpustate.currLambdaCount;

      /* no use, it's worst or it's the best */
      if (!(this->lowerBound < bestLowerBound))
	break;
      if (!(this->lowestSubgraph > -1))
	break;
    }

    /* read parents back type-converted */
    if (this->lowerBound < bestLowerBound) {
      Concurrency::extent<1> ec(edgesimds);
      Concurrency::parallel_for_each(ec, [=,
	&parent
      ](index<1> j) restrict(amp) {
	parents.set(j, parent(j));
      });
      copy(parentx, &this->parent[0], (unsigned int)(this->parent.size() * sizeof(idxtype)));
    }

    /* is this a possibly shorter path? */
    this->lambdaSteps = lambda_count;
    return (this->lowerBound < bestLowerBound);
  }

  template<typename edgtype, typename edgvectype, typename edgresview>
  bool computeHeldKarp(int pb, edgresview &edgematrix, sumtype bestLowerBound) {
    /* choose the thread-local resources */
    if (!PathMem::wghtmatrix[pb]) {
      /* reduction-access can be one 4-way vector in excess over edgestride
       * as this is only read (reduction writes only to max >> 1) we can
       * set those values to the neutral value on allocation and they never
       * change
       */
      int reductionstride = (edgestride + AccessAlignment - 1) & (~(AccessAlignment - 1));
      int reductionsimds = reductionstride / SIMDsize;

      /* first use initializes static memories */
      PathMem::wghtmatrix [pb] = new wghtgrid(numnodes, edgesimds);
      PathMem::weights    [pb] = new sumarray(edgesimds);
      PathMem::parent     [pb] = new idxarray(edgesimds);
      PathMem::parentx    [pb] = new idxtrans(edgesimds, (unsigned int)(sizeof(idxtype) * 8U));
      PathMem::mstree     [pb] = new sumarray(reductionsimds);
      PathMem::connections[pb] = new idxarray(reductionsimds);

      if ((reductionstride - edgestride) == SIMDsize) {
	amp_uav sumarray &mstree = *(PathMem::mstree[pb]);
	amp_uav idxarray &connections = *(PathMem::connections[pb]);

	/* serves as warm-up as well */
	Concurrency::extent<1> ee(reductionsimds);
        Concurrency::parallel_for_each(ee, [=,
	  &mstree,
	  &connections
	](index<1> p) restrict(amp) {
	  mstree(p) = maxvec<sumtype>();
	  connections(p) = 2;
	});
      }
    }

    this->parent.resize(edgestride);
    this->lowerBound = minvec<sumtype>();
    this->lowestSubgraph = 0;

    /* choose a performant tile-distribution
     *
     * short-cut wave-fronts (the y-dimension != 0) run at about 50 cycles per y
     * striding wave-fronts (the x-dimension > 64) run at about 120 cycles per y
     * the first wave-front (the x-dimension <= 64) runs at about 1000 cycles per y
     */
    switch (edgelog2 / SIMDsize) {
      // if (edgestride > (512 * SIMDsize))		// 4096 edges max, 16 wave-fronts
      caseHK(512, 1024, 1, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (256 * SIMDsize))		// 2048 edges max, 16 wave-fronts
      caseHK(320,  512, 2, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (256 * SIMDsize))		// 1280 edges max, 15 wave-fronts
      caseHK(256,  320, 3, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (128 * SIMDsize))		// 1024 edges max, 16 wave-fronts
      caseHK(192,  256, 4, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (128 * SIMDsize))		//  768 edges max, 15 wave-fronts
      caseHK(160,  192, 5, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (128 * SIMDsize))		//  640 edges max, 15 wave-fronts
      caseHK(128,  160, 6, (pb, edgematrix, bestLowerBound));
      // if (edgestride > ( 64 * SIMDsize))		//  512 edges max, 16 wave-fronts
      caseHK( 96,  128, 8, (pb, edgematrix, bestLowerBound));
      // if (edgestride > ( 64 * SIMDsize))		//  384 edges max, 15 wave-fronts
      caseHK( 80,   96, 10, (pb, edgematrix, bestLowerBound));
      // if (edgestride > ( 64 * SIMDsize))		//  320 edges max, 15 wave-fronts
      caseHK( 64,   80, 12, (pb, edgematrix, bestLowerBound));
      // if (edgestride > ( 32 * SIMDsize))		//  256 edges max, 16 wave-fronts
      caseHK( 32,   64, 16, (pb, edgematrix, bestLowerBound));
      // if (edgestride > ( 16 * SIMDsize))		//  128 edges max, square area, smallest tilestride at maximum threads
      caseHK( 24,   32, 32, (pb, edgematrix, bestLowerBound));
      // if (edgestride > ( 12 * SIMDsize))		//   96 edges max, square area
      caseHK( 16,   24, 24, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (  8 * SIMDsize))		//   64 edges max, square area
      caseHK(  8,   16, 16, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (  4 * SIMDsize))		//   32 edges max, square area, smallest thread-group size AMD
      caseHK(  4,    8,  8, (pb, edgematrix, bestLowerBound));
      // if (edgestride > (  2 * SIMDsize))		//   16 edges max, square area, smallest thread-group size REF
      caseHK(  1,    4,  4, (pb, edgematrix, bestLowerBound));

      default:
	abort(); return false;
    }
  }

public:
  Path() { mst.lock(); curr_memory += sizeof(Path) + sizeof(idxtype) * (edgestride); peak_memory = max(peak_memory, curr_memory); mst.unlock(); }
  virtual ~Path() { mst.lock(); curr_memory -= sizeof(Path) + sizeof(idxtype) * (edgestride); num_iterations += this->lambdaSteps; mst.unlock(); }

  static void exit(int pb) {
    for (int j = 0; j < pb; j++) {
      if (PathMem::wghtmatrix [j]) delete PathMem::wghtmatrix [j];
      if (PathMem::weights    [j]) delete PathMem::weights    [j];
      if (PathMem::parent     [j]) delete PathMem::parent     [j];
      if (PathMem::parentx    [j]) delete PathMem::parentx    [j];
      if (PathMem::mstree     [j]) delete PathMem::mstree     [j];
      if (PathMem::connections[j]) delete PathMem::connections[j];
    }
  }

  template<typename edgtype, typename edgvectype, typename edgresview>
  static Path *setup(int pb, int numnodes, int edgestride, edgresview &edgematrix, sumtype bestLowerBound) {
    Path *root = new Path();

    /* round to full ulongs */
    PathMem::numnodes   =  numnodes;
    PathMem::boolstride = (edgestride + 31) & (~31);
    PathMem::edgestride =  edgestride;
    PathMem::edgesimds  =  edgestride / SIMDsize;

    /* get next 2^x which fits the number of possible edges */
    DWORD lg = 0;
    _BitScanReverse(&lg, ((edgestride << 1) - 1) | 1);
    PathMem::edgelog2 = 1 << lg;

    /* clear out exclusion-matrix */
    clear(root->included);

    /* mask out all j->j edges (specifically 0->0) */
    for (int j = 0; j < numnodes; j++) {
      int bitposj = (j + 0) * boolstride + (j + 0);
      int basebitj = bitposj & 31;

      assert(!!(root->included[bitposj >> 5] & (1 << basebitj)));

      root->included[bitposj >> 5] &= ~(1 << basebitj);
    }

    root->depth = 0;
    root->seed = NULL;
    root->computeHeldKarp<edgtype, edgvectype, edgresview>(0, edgematrix, bestLowerBound);

    return root;
  }

  template<typename edgtype, typename edgvectype, typename edgresview>
  Path *permute(int pb, int i, int j, edgresview &edgematrix, sumtype bestLowerBound) {
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

#if 0
    /* this effectively only allocates new memory for the
     * two changed rows, the others are copied references
     */
    child->included       = this->included.clone();
    child->included[i]    = this->included[i].clone();
    child->included[j]    = this->included[j].clone();
    child->included[i][j] = true;
    child->included[j][i] = true;
#else
//  child->included            = this->included;

    /* clone out exclusion-matrix */
    clone(child->included, this->included);

    int bitposi = (i + 0) * boolstride + (j + 0);
    int bitposj = (j + 0) * boolstride + (i + 0);
    int basebiti = bitposi & 31;
    int basebitj = bitposj & 31;

    assert(!!(child->included[bitposi >> 5] & (1 << basebiti)));
    assert(!!(child->included[bitposj >> 5] & (1 << basebitj)));

    child->included[bitposi >> 5] &= ~(1 << basebiti);
    child->included[bitposj >> 5] &= ~(1 << basebitj);
#endif

    child->depth = this->depth + 1;
    child->seed = this;
    if (!child->computeHeldKarp<edgtype, edgvectype, edgresview>(pb, edgematrix, bestLowerBound)) {
      delete child;
      child = NULL;
    }

    return child;
  }
};

PathMem<float4, int4>::wghtgrid *PathMem<float4, int4>::wghtmatrix[PARALLEL_BRANCHES];
PathMem<float4, int4>::sumarray *PathMem<float4, int4>::weights[PARALLEL_BRANCHES];
PathMem<float4, int4>::sumarray *PathMem<float4, int4>::mstree[PARALLEL_BRANCHES];
PathMem<float4, int4>::idxarray *PathMem<float4, int4>::parent[PARALLEL_BRANCHES];
PathMem<float4, int4>::idxtrans *PathMem<float4, int4>::parentx[PARALLEL_BRANCHES];
PathMem<float4, int4>::idxarray *PathMem<float4, int4>::connections[PARALLEL_BRANCHES];

int PathMem<float4, int4>::numnodes;
int PathMem<float4, int4>::boolstride;
int PathMem<float4, int4>::edgestride;
int PathMem<float4, int4>::edgesimds;
int PathMem<float4, int4>::edgelog2;

PathMem<double4, int4>::wghtgrid *PathMem<double4, int4>::wghtmatrix[PARALLEL_BRANCHES];
PathMem<double4, int4>::sumarray *PathMem<double4, int4>::weights[PARALLEL_BRANCHES];
PathMem<double4, int4>::sumarray *PathMem<double4, int4>::mstree[PARALLEL_BRANCHES];
PathMem<double4, int4>::idxarray *PathMem<double4, int4>::parent[PARALLEL_BRANCHES];
PathMem<double4, int4>::idxtrans *PathMem<double4, int4>::parentx[PARALLEL_BRANCHES];
PathMem<double4, int4>::idxarray *PathMem<double4, int4>::connections[PARALLEL_BRANCHES];

int PathMem<double4, int4>::numnodes;
int PathMem<double4, int4>::boolstride;
int PathMem<double4, int4>::edgestride;
int PathMem<double4, int4>::edgesimds;
int PathMem<double4, int4>::edgelog2;

/* ********************************************************************************************
 */
#include "solver/Plain-Templated.cpp"

#undef	PARALLEL_BRANCHES

}
