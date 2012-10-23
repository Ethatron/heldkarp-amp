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

#ifndef	SOLVETSP_AMP_CM_OPT_HPP
#define SOLVETSP_AMP_CM_OPT_HPP

#include <amp.h>
#include <amp_graphics.h>
#include <amp_short_vectors.h>

using namespace Concurrency;
using namespace Concurrency::graphics;

template<typename idxvectype, typename wghtgrid, typename sumarray, typename idxarray>
class tiled_views {

public:
  /* constants to work with */
  const int numnodes;
  const int edgesimds;
  const int rdctsimds;

  /* memory buffers for spilling */
  wghtgrid &wghtmatrix;
  sumarray &weights;
  sumarray &mstree;
#if 0 // ndef NDEBUG
  idxarray &parent;
#endif
  idxarray &connections;

  /* per-thread local 1:1 relationships */
  idxvectype parent_local;

  /* the initializer of "parent_local" prevents
   * it to lock up, even though we can't use this
   * instance of "parent_local" because that
   * again would lock up
   */
  tiled_views(
    const int nm,
    const int es,
    const int rs,
    wghtgrid &wm,
    sumarray &w,
    sumarray &m,
#if 0 // ndef NDEBUG
    idxarray &p,
#endif
    idxarray &c
  ) restrict(amp,cpu) :
    numnodes(nm),
    edgesimds(es),
    rdctsimds(rs),
    wghtmatrix(wm),
    weights(w),
    mstree(m),
#if 0 // ndef NDEBUG
    parent(p),
#endif
    connections(c),
    parent_local(0) {
  }
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * this becomes a possible tile_static muxer once the inner while of the
 * parallel_for_each works
 */

template<typename sumtype, typename idxtype,
	 typename sumvectype, typename idxvectype,
	 typename wghtgrid, typename sumarray, typename idxarray,
	 const int tileheight, const int tilestride, const int SIMDsize = 4, const int sharedsize = 32768>
class tiled_cache {

public:
  /* all i/o done by the algorithm:
   *
   *   n - numnodes	fe. 51
   *   m - edgesimds	fe. 52/4
   *   o - redcsimds	fe. 56/4
   *
   *   r/ w - uav rad/write
   *  lr/lw - local var read/write
   *  tr/tw - texture read/write
   *
   *   r numnodes * weights(j).x			 r 1n
   *   r numnodes * edgesimds * weights(j)		 r 4mn
   *  tr numnodes * edgesimds * edgematrix(i,j)		tr Xmn
   *   w numnodes * edgesimds * wghtmatrix(i,j)		 w 4mn
   *   r edgesimds * wghtmatrix(0,j)			 r 4m		find min
   *   w edgesimds * connections(j)			 w 4o		init
   *  lw edgesimds * parent(j)				lw 4o
   *   r edgesimds * wghtmatrix(i,j)			 r 4o		init
   *   w edgesimds * mstree(j)				 w 4o
   *   r numnodes * redcsimds * connections(j)		 r 4o(n-2)	search
   *   r numnodes * redcsimds * mstree(j)		 r 4o(n-2)
   *   r numnodes * wghtmatrix(i,j).x			 r 1n		connect
   *   r numnodes * 2 * connections(j).x		 r 2n
   *   w numnodes * 2 * connections(j).x		 w 2n
   *  lr numnodes * parent(j).x				lr 1n
   *  lw numnodes * parent(j).x				lw 1n
   *   r numnodes * edgesimds * connections(j)		 r 4m(n-2)	adjust
   *   r numnodes * edgesimds * wghtmatrix(i,j)		 r 4m(n-2)
   *   r numnodes * edgesimds * mstree(j)		 r 4m(n-2)
   *  lr numnodes * edgesimds * parent(j)		lr 4m(n-2)
   *   w numnodes * edgesimds * mstree(j)		 w 4m(n-2)
   *  lw numnodes * edgesimds * parent(j)		lw 4m(n-2)
   *   r redcsimds * connections(j)			 r 4o		search
   *   r redcsimds * connections(j)			 r 4o		denom
   *   r edgesimds * connections(j)			 r 4m		muladd
   *   r edgesimds * weights(j)				 r 4m
   *   w edgesimds * weights(j)				 w 4m
   *  lr edgesimds * parent(j)				lr 4m		spill
   *   w edgesimds * parent(j)				 w 4m
   *
   * tr	Xnm
   *  r	4m 4o 1n 4m(n-2) 1n 4mn 4m 4o(n-2) 2n 4m(n-2) 4o 4o 4m 4o(n-2) 4m(n-2)
   *  w 4mn 4m 4o 2n 4o 4m(n-2) 4m
   *
   * summary:
   *
   *   edgematrix			r Xnm
   *   wghtmatrix	w 4mn		r 4m 4o 1n 4m(n-2)
   *   weights		w 4m		r 1n 4mn 4m
   *   connections	w 4o 2n		r 4o(n-2) 4m(n-2) 2n 4o 4o 4m
   *   mstree		w 4o 4m(n-2)	r 4o(n-2) 4m(n-2)
   *   parent		w 4m
   *
   * priorities:
   *
   *  -) parent - just the spill-to-cpu at the end
   *  -) edgematrix - normally too big to fit into LDS, for tiny sets it may fit
   *  0) wghtmatrix - normally too big to fit into LDS, for tiny sets it may fit
   *  1) weights - not that much i/o
   *  2) mstree - most writes, moderate reads
   *  3) connections - by far the most i/o
   *
   * approach:
   *
   * - allocate the two reduction-arrays, we can't do without (if we spill we could,
   *   but better not)
   * - then try to allocate other arrays in priority-order, letting unallocated memory
   *   fall through to be possibly used by lower priority arrays
   * - this whole thing is basically a compile-time dynamic allocator over the
   *   the group-shared / LDS memory block
   */

  static const int sumvecmatrix = tilestride * sizeof(sumvectype) * (tilestride * SIMDsize);
  static const int sumvecstride = tilestride * sizeof(sumvectype);
  static const int idxvecstride = tilestride * sizeof(idxvectype);

#define	SYMMETRIC_BANK0(len, off)	(              (off))
#define	SYMMETRIC_BANK1(len, off)	(              (off))

//efine	SYMMETRIC_BANK0(len, off)	(              (off))
//efine	SYMMETRIC_BANK1(len, off)	(((len) - 1) - (off))

  /* ----------------------------------------------------------------------------------- */
  static const int ampminsize = WAVEFRONT_SIZE * 2 * (sizeof(sumvectype) + sizeof(idxvectype));
  static const int othersize = ampminsize + (2 * sizeof(int) + sizeof(sumtype));
  /* tile_static: int l, int h, sumtype mstLength */

  /* store/fetch, reduction temporary i/o ---------------------------------------------- */
  static const int sumvecreduction = sumvecstride >> 1;
  static const int idxvecreduction = idxvecstride >> 1;
  static const int reductionsize = sumvecreduction + idxvecreduction;
  static const int assignablesizeA = sharedsize - reductionsize - othersize;

  /* LDS-layout (tilestride is 16 in this example):
   *
   *  +---idx---+ +---idx---+ +---idx---+ +---idx---+ +---idx---+ +---idx---+ +---idx---+ +---idx---+
   *  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
   *
   *  +---sum---+ +---sum---+ +---sum---+ +---sum---+ +---sum---+ +---sum---+ +---sum---+ +---sum---+
   *  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
   */
  idxvectype cv[tilestride >> 1];
  sumvectype mv[tilestride >> 1];

  /* reduce bank-conflicts
   *
   * inverting the parallel access to the value vs. the index,
   * the indices start at 0, the values start at tilestride - 1
   */
  idxvectype &cr(int offs) restrict(amp,cpu) { return cv[SYMMETRIC_BANK0(tilestride >> 1, offs)]; }
  sumvectype &mr(int offs) restrict(amp,cpu) { return mv[SYMMETRIC_BANK1(tilestride >> 1, offs)]; }

  /* if we can get "connections[]" & "mstree[]" we can use those for minima() ---------- */
  static const int idxvecminima = idxvecstride;
  static const int sumvecminima = sumvecstride;
  static const int assignablesizeB =
    ((assignablesizeA + ampminsize - idxvecminima - sumvecminima) < 0 ? assignablesizeA : assignablesizeA + ampminsize);
  /* if VC doesn't eliminate this because of zero usage, we'll loose a vector of space */
  idxvectype fscombinedN[(assignablesizeB != assignablesizeA ? 1 : WAVEFRONT_SIZE)][2];
  sumvectype fscombinedV[(assignablesizeB != assignablesizeA ? 1 : WAVEFRONT_SIZE)][2];

  static bool slowminima() restrict(amp,cpu) { return assignablesizeB == assignablesizeA; }
  static bool fastminima() restrict(amp,cpu) { return assignablesizeB != assignablesizeA; }

  /* LDS-layout (tilestride is 16 in this example):
   *
   *  +---con---+ +---con---+ +---con---+ +---con---+ +---con---+ +---con---+ +---con---+ +---con---+
   *  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
   *  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
   *
   *  +---mst---+ +---mst---+ +---mst---+ +---mst---+ +---mst---+ +---mst---+ +---mst---+ +---mst---+
   *  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
   *  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
   */

  /* reduce bank-conflicts by having first/second stay together instead
   * of having (tilestride >> 1) between them
   *
   * and inverting the parallel access to the value vs. the index,
   * the indices start at 0, the values start at tilestride - 1
   */
  idxvectype &firstN(int offs) restrict(amp,cpu) {
    if (slowminima())
      return fscombinedN[                            (offs << 0) ][0 ];
    else
      return connctcache[SYMMETRIC_BANK0(tilestride, (offs << 1) + 0)];
  }

  idxvectype &secndN(int offs) restrict(amp,cpu) {
    if (slowminima())
      return fscombinedN[                            (offs << 0) ][1 ];
    else
      return connctcache[SYMMETRIC_BANK0(tilestride, (offs << 1) + 1)];
  }

  sumvectype &firstV(int offs) restrict(amp,cpu) {
    if (slowminima())
      return fscombinedV[                            (offs << 0) ][0 ];
    else
      return mstche     [SYMMETRIC_BANK1(tilestride, (offs << 1) + 0)];
  }

  sumvectype &secndV(int offs) restrict(amp,cpu) {
    if (slowminima())
      return fscombinedV[                            (offs << 0) ][1 ];
    else
      return mstche     [SYMMETRIC_BANK1(tilestride, (offs << 1) + 1)];
  }

  /* store/fetch, "connections[]" i/o -------------------------------------------------- */
  static const int idxvecconnection = idxvecstride;
  static const int assignablesizeC =
    ((assignablesizeB - idxvecconnection) < 0 ? assignablesizeB : assignablesizeB - idxvecconnection);
  /* if VC doesn't eliminate this because of zero usage, we'll loose a vector of space */
  idxvectype connctcache[(assignablesizeC == assignablesizeB ? 1 : tilestride)];

  static bool spillconnections() restrict(amp,cpu) { return assignablesizeC == assignablesizeB; }
  static bool cacheconnections() restrict(amp,cpu) { return assignablesizeC != assignablesizeB; }

  /* reduce bank-conflicts
   *
   * inverting the parallel access to the mstree vs. the connections,
   * the connections start at 0, the mstree starts at tilestride - 1
   */
  idxvectype &connections(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offs) restrict(amp,cpu) {
    idxarray &connections = tv.connections;

    /* there has been no space assigned to us, spill to memory */
    if (spillconnections())
      return connections(SYMMETRIC_BANK0(tilestride, offs));
    else
      return connctcache[SYMMETRIC_BANK0(tilestride, offs)];
  }

  /* store/fetch, "mstree[]" i/o ------------------------------------------------------- */
  static const int sumvecmstree = sumvecstride;
  static const int assignablesizeD =
    ((assignablesizeC - sumvecmstree) < 0 ? assignablesizeC : assignablesizeC - sumvecmstree);
  /* if VC doesn't eliminate this because of zero usage, we'll loose a vector of space */
  sumvectype mstche[(assignablesizeD == assignablesizeC ? 1 : tilestride)];

  static bool spillmstree() restrict(amp,cpu) { return assignablesizeD == assignablesizeC; }
  static bool cachemstree() restrict(amp,cpu) { return assignablesizeD != assignablesizeC; }

  /* reduce bank-conflicts
   *
   * inverting the parallel access to the mstree vs. the connections,
   * the connections start at 0, the mstree starts at tilestride - 1
   */
  sumvectype &mstree(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offs) restrict(amp,cpu) {
    sumarray &mstree = tv.mstree;

    /* there has been no space assigned to us, spill to memory */
    if (spillmstree())
      return mstree(SYMMETRIC_BANK1(tilestride, offs));
    else
      return mstche[SYMMETRIC_BANK1(tilestride, offs)];
  }

  /* store/fetch, "weights[]" i/o ------------------------------------------------------ */
  static const int sumvecweight = sumvecstride;
  static const int assignablesizeE =
    ((assignablesizeD - sumvecweight) < 0 ? assignablesizeD : assignablesizeD - sumvecweight);
  /* if VC doesn't eliminate this because of zero usage, we'll loose a vector of space */
  sumvectype wgcache[(assignablesizeE == assignablesizeD ? 1 : tilestride)];

  static bool spillweights() restrict(amp,cpu) { return assignablesizeE == assignablesizeD; }
  static bool cacheweights() restrict(amp,cpu) { return assignablesizeE != assignablesizeD; }

  void weighto(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offs, sumvectype &o) restrict(amp,cpu) {
    sumarray &weights = tv.weights;

    /* it has to be written to memory eventually */
    if (spillweights())
      ;
    else
      weights(offs) = o;
  }

  void weighto(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offs) restrict(amp,cpu) {
    sumarray &weights = tv.weights;

    /* it has to be written to memory eventually */
    if (spillweights())
      ;
    else
      weights(offs) = wgcache[offs];
  }

  void weighti(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offs) restrict(amp,cpu) {
    sumarray &weights = tv.weights;

    /* it has to be read from memory eventually */
    if (spillweights())
      ;
    else
      wgcache[offs] = weights(offs);
  }

  sumvectype &weights(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offs) restrict(amp,cpu) {
    sumarray &weights = tv.weights;

    /* there has been no space assigned to us, spill to memory */
    if (spillweights())
      return weights(offs);
    else
      return wgcache[offs];
  }

  /* store/fetch, "weightmatrix[]" i/o ------------------------------------------------- */
  static const int sumvecweightmatrix = sumvecmatrix;
  static const int sumvecweightmtxrw0 = sumvecstride;
  static const int assignablesizeF =
    ((assignablesizeE - sumvecweightmatrix) < 0 ? assignablesizeE : assignablesizeE - sumvecweightmatrix);
  /* if VC doesn't eliminate this because of zero usage, we'll loose a vector of space */
  sumvectype wgmtxcache
    [(assignablesizeF == assignablesizeE ? 1 : tilestride * SIMDsize)]
    [(assignablesizeF == assignablesizeE ? 1 : tilestride)];

  static bool spillweightmatrix() restrict(amp,cpu) { return assignablesizeF == assignablesizeE; }
  static bool cacheweightmatrix() restrict(amp,cpu) { return assignablesizeF != assignablesizeE; }

  /* if we can't cache all of it try to cache "row[0]" in mstree */
  static bool spillweightmtxrw0() restrict(amp,cpu) { return spillweightmatrix() && spillmstree(); }
  static bool cacheweightmtxrw0() restrict(amp,cpu) { return cacheweightmatrix() || cachemstree(); }

  void wghtmatrix(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offsr, int offsc, sumvectype &o) restrict(amp,cpu) {
    wghtgrid &wghtmatrix = tv.wghtmatrix;
    sumvectype *wgrw0cache = &mstche[0];

    /* there has been no space assigned to us, spill to memory */
    if (!spillweightmatrix())
      wgmtxcache[offsr][offsc] = o;
    else
      wghtmatrix(offsr, offsc) = o;

    /* there is space in mstree which we can use to cache */
    if (spillweightmatrix() && !spillweightmtxrw0() && (offsr == 0))
      wgrw0cache       [offsc] = o;
  }

  sumvectype &wghtmatrix(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offsr, int offsc) restrict(amp,cpu) {
    wghtgrid &wghtmatrix = tv.wghtmatrix;

    /* there has been no space assigned to us, spill to memory */
    if (!spillweightmatrix())
      return wgmtxcache[offsr][offsc];
    else
      return wghtmatrix(offsr, offsc);
  }

  sumvectype &wghtmtxrw0(tiled_views<idxvectype, wghtgrid, sumarray, idxarray> &tv, int offsr, int offsc) restrict(amp,cpu) {
    wghtgrid &wghtmatrix = tv.wghtmatrix;
    sumvectype *wgrw0cache = &mstche[0];

    /* there has been no space assigned to us, spill to memory */
    if (!spillweightmatrix())
      return wgmtxcache[0][offsc];
    else if (!spillweightmtxrw0())
      return wgrw0cache   [offsc];
    else
      return wghtmatrix(0, offsc);
  }

  /* query state-of cache -------------------------------------------------------------- */
  static const int assignablesizeL = assignablesizeF;

  static int occupied  () restrict(amp,cpu) { return (sharedsize - assignablesizeL); }
  static int assignable() restrict(amp,cpu) { return               assignablesizeL ; }
  static int occupieds () restrict(amp,cpu) { return reductionsize + othersize - (assignablesizeB - assignablesizeA); }
  static int occupiedd () restrict(amp,cpu) { return occupied() - occupieds(); }

public:
  /* query state-of cache -------------------------------------------------------------- */
  static void stats() {
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  8,    8> thread_shared____8;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, 16,   16> thread_shared___16;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, 32,   32> thread_shared___32;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, 16,   64> thread_shared___64;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, 12,   80> thread_shared___80;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, 10,   96> thread_shared___96;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  8,  128> thread_shared__128;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  6,  160> thread_shared__160;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  5,  192> thread_shared__192;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  4,  256> thread_shared__256;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  3,  320> thread_shared__320;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  2,  512> thread_shared__512;
    static tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray,  1, 1024> thread_shared_1024;

    /* - float --------------------------------------------   - double --------------------------------------------
     *
     * variables: 12 used			              variables: 16 used
     * memory: 32756 free                                     memory: 32752 free
     * stride | dynmic | con mst wgt mtx | static | min rw0   stride | dynmic | con mst wgt mtx | static | min rw0
     * -------+--------+-----------------+--------+--------   -------+--------+-----------------+--------+--------
     *      8 |   4480 |   1   1   1   1 |    140 |   0   1        8 |   8832 |   1   1   1   1 |    208 |   0   1
     *     16 |  17152 |   1   1   1   1 |    268 |   0   1       16 |   1280 |   1   1   1   0 |    400 |   0   1
     *     32 |   1536 |   1   1   1   0 |    524 |   0   1       32 |   2560 |   1   1   1   0 |    784 |   0   1
     *     64 |   3072 |   1   1   1   0 |   1036 |   0   1       64 |   5120 |   1   1   1   0 |   1552 |   0   1
     *     80 |   3840 |   1   1   1   0 |   1292 |   0   1       80 |   6400 |   1   1   1   0 |   1936 |   0   1
     *     96 |   4608 |   1   1   1   0 |   1548 |   0   1       96 |   7680 |   1   1   1   0 |   2320 |   0   1
     *    128 |   6144 |   1   1   1   0 |   2060 |   0   1      128 |  10240 |   1   1   1   0 |   3088 |   0   1
     *    160 |   7680 |   1   1   1   0 |   2572 |   0   1      160 |  12800 |   1   1   1   0 |   3856 |   0   1
     *    192 |   9216 |   1   1   1   0 |   3084 |   0   1      192 |  15360 |   1   1   1   0 |   4624 |   0   1
     *    256 |  12288 |   1   1   1   0 |   4108 |   0   1      256 |  20480 |   1   1   1   0 |   6160 |   0   1
     *    320 |  15360 |   1   1   1   0 |   5132 |   0   1      320 |  15360 |   1   1   0   0 |   7696 |   0   1
     *    512 |  16384 |   1   1   0   0 |   8204 |   0   1      512 |   8192 |   1   0   0   0 |  18448 |   1   0
     *   1024 |      0 |   0   0   0   0 |  20492 |   1   0     1024 |      0 |   0   0   0   0 |  30736 |   1   0
     */

    printf("stats:\n");
    printf(" memory: %d free\n", 32768 - (2 * sizeof(int) + sizeof(sumtype)));

    printf(" stride | dynmic | con mst wgt mtx | static | min rw0\n");
    printf(" -------+--------+-----------------+--------+--------\n");
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",    8, thread_shared____8.occupiedd(), thread_shared____8.cacheconnections(), thread_shared____8.cachemstree(), thread_shared____8.cacheweights(), thread_shared____8.cacheweightmatrix(), thread_shared____8.occupieds(), thread_shared____8.slowminima(), thread_shared____8.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",   16, thread_shared___16.occupiedd(), thread_shared___16.cacheconnections(), thread_shared___16.cachemstree(), thread_shared___16.cacheweights(), thread_shared___16.cacheweightmatrix(), thread_shared___16.occupieds(), thread_shared___16.slowminima(), thread_shared___16.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",   32, thread_shared___32.occupiedd(), thread_shared___32.cacheconnections(), thread_shared___32.cachemstree(), thread_shared___32.cacheweights(), thread_shared___32.cacheweightmatrix(), thread_shared___32.occupieds(), thread_shared___32.slowminima(), thread_shared___32.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",   64, thread_shared___64.occupiedd(), thread_shared___64.cacheconnections(), thread_shared___64.cachemstree(), thread_shared___64.cacheweights(), thread_shared___64.cacheweightmatrix(), thread_shared___64.occupieds(), thread_shared___64.slowminima(), thread_shared___64.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",   80, thread_shared___80.occupiedd(), thread_shared___80.cacheconnections(), thread_shared___80.cachemstree(), thread_shared___80.cacheweights(), thread_shared___80.cacheweightmatrix(), thread_shared___80.occupieds(), thread_shared___80.slowminima(), thread_shared___80.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",   96, thread_shared___96.occupiedd(), thread_shared___96.cacheconnections(), thread_shared___96.cachemstree(), thread_shared___96.cacheweights(), thread_shared___96.cacheweightmatrix(), thread_shared___96.occupieds(), thread_shared___96.slowminima(), thread_shared___96.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",  128, thread_shared__128.occupiedd(), thread_shared__128.cacheconnections(), thread_shared__128.cachemstree(), thread_shared__128.cacheweights(), thread_shared__128.cacheweightmatrix(), thread_shared__128.occupieds(), thread_shared__128.slowminima(), thread_shared__128.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",  160, thread_shared__160.occupiedd(), thread_shared__160.cacheconnections(), thread_shared__160.cachemstree(), thread_shared__160.cacheweights(), thread_shared__160.cacheweightmatrix(), thread_shared__160.occupieds(), thread_shared__160.slowminima(), thread_shared__160.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",  192, thread_shared__192.occupiedd(), thread_shared__192.cacheconnections(), thread_shared__192.cachemstree(), thread_shared__192.cacheweights(), thread_shared__192.cacheweightmatrix(), thread_shared__192.occupieds(), thread_shared__192.slowminima(), thread_shared__192.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",  256, thread_shared__256.occupiedd(), thread_shared__256.cacheconnections(), thread_shared__256.cachemstree(), thread_shared__256.cacheweights(), thread_shared__256.cacheweightmatrix(), thread_shared__256.occupieds(), thread_shared__256.slowminima(), thread_shared__256.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",  320, thread_shared__320.occupiedd(), thread_shared__320.cacheconnections(), thread_shared__320.cachemstree(), thread_shared__320.cacheweights(), thread_shared__320.cacheweightmatrix(), thread_shared__320.occupieds(), thread_shared__320.slowminima(), thread_shared__320.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n",  512, thread_shared__512.occupiedd(), thread_shared__512.cacheconnections(), thread_shared__512.cachemstree(), thread_shared__512.cacheweights(), thread_shared__512.cacheweightmatrix(), thread_shared__512.occupieds(), thread_shared__512.slowminima(), thread_shared__512.cacheweightmtxrw0());
    printf(" %6d | %6d | %3d %3d %3d %3d | %6d | %3d %3d\n", 1024, thread_shared_1024.occupiedd(), thread_shared_1024.cacheconnections(), thread_shared_1024.cachemstree(), thread_shared_1024.cacheweights(), thread_shared_1024.cacheweightmatrix(), thread_shared_1024.occupieds(), thread_shared_1024.slowminima(), thread_shared_1024.cacheweightmtxrw0());
  }
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

namespace amphelper {

/* --------------------------------------------------------------------------
 */

template<typename sumtype, typename idxtype,
	 typename sumvectype, typename idxvectype,
	 typename wghtgrid, typename sumarray, typename idxarray,
	 const int tileheight, const int tilestride>
struct ampminima_adaptive {
  /* divide into 4/32/64 buckets (wavefront size) */
  static const int blcksize = ((tilestride + WAVEFRONT_SIZE - 1) / WAVEFRONT_SIZE);

//idxvectype firstN[WAVEFRONT_SIZE];
//idxvectype secndN[WAVEFRONT_SIZE];
//sumvectype firstVal[WAVEFRONT_SIZE];
//sumvectype secndVal[WAVEFRONT_SIZE];

  static const int occupied() {
    return WAVEFRONT_SIZE * 2 * (sizeof(sumvectype) + sizeof(idxvectype));
  }

  void init(
    tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, tileheight, tilestride> &ts,
    int w, sumvectype def
  ) restrict(amp,cpu) {
//  ts.firstN(w) = 0;
//  ts.secndN(w) = 0;
//  ts.firstV(w) = def;
//  ts.secndV(w) = def;
  }

  void orderedset(
    tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, tileheight, tilestride> &ts,
    int w,
    /* don't use references, will conflict in the reduction-iteration */
    const sumvectype wght0, const idxvectype curindex0,
    const sumvectype wght1, const idxvectype curindex1
  ) restrict(amp,cpu) {
    ts.secndN(w) = amphelper::smaller(wght1, wght0, curindex0, curindex1);
    ts.secndV(w) = amphelper::smaller(wght1, wght0,     wght0,     wght1);

    ts.firstN(w) = amphelper::smaller(wght1, wght0, curindex1, curindex0);
    ts.firstV(w) = amphelper::smaller(wght1, wght0,     wght1,     wght0);
  }

  void orderedmin(
    tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, tileheight, tilestride> &ts,
    int w,
    /* don't use references, will conflict in the reduction-iteration */
    const sumvectype wght, const idxvectype curindex
  ) restrict(amp,cpu) {
    ts.secndN(w) = amphelper::smaller(wght, ts.secndV(w),     curindex, ts.secndN(w));
    ts.secndV(w) = amphelper::smaller(wght, ts.secndV(w),         wght, ts.secndV(w));

    ts.secndN(w) = amphelper::smaller(wght, ts.firstV(w), ts.firstN(w), ts.secndN(w));
    ts.secndV(w) = amphelper::smaller(wght, ts.firstV(w), ts.firstV(w), ts.secndV(w));

    ts.firstN(w) = amphelper::smaller(wght, ts.firstV(w),     curindex, ts.firstN(w));
    ts.firstV(w) = amphelper::smaller(wght, ts.firstV(w),         wght, ts.firstV(w));
  }

  void slow_orderedred2(
    tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, tileheight, tilestride> &ts,
    int limit, int w
  ) restrict(amp,cpu) {
    int l = min(WAVEFRONT_SIZE, limit);
    for (int j = 2; j < l; j += 2) {
      /* assign to bucket 0/1 */
      orderedmin(ts, w, ts.secndV(w + j), ts.secndN(w + j));
      orderedmin(ts, w, ts.firstV(w + j), ts.firstN(w + j));
    }
  }

  void slow_orderedred1(
    tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, tileheight, tilestride> &ts,
    int limit
  ) restrict(amp,cpu) {
    if (1 < WAVEFRONT_SIZE) {
      /* read from bucket 1, assign to bucket 0 */
      orderedmin(ts, 0, ts.secndV(0 + 1), ts.secndN(0 + 1));
      orderedmin(ts, 0, ts.firstV(0 + 1), ts.firstN(0 + 1));
    }
  }

  template<typename sctype>
  void orderedmallest(
    tiled_cache<sumtype, int, sumvectype, idxvectype, wghtgrid, sumarray, idxarray, tileheight, tilestride> &ts,
    int &firstNeighbor, int &secndNeighbor
  ) restrict(amp,cpu) {
    /* get the two cheapest edges from row 0 */
    firstNeighbor = ts.firstN(0).x;
    secndNeighbor = ts.secndN(0).x;

    /* prevent writing back to tile_shared */
    sctype fV_l_ = ts.firstV(0).x;
    sctype sV_l_ = ts.secndV(0).x;

    /* reduction */
    {
      /* NF NS
	*       OF OS
	*/
      if (fV_l_ > ts.secndV(0).y) {
	firstNeighbor = ts.firstN(0).y;
	secndNeighbor = ts.secndN(0).y;

	fV_l_ = ts.firstV(0).y;
	sV_l_ = ts.secndV(0).y;
      }
      /*       NF NS
	* OF OS
	*/
      else if (sV_l_ > ts.firstV(0).y) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (fV_l_ > ts.firstV(0).y) {
	  sV_l_ = fV_l_;
	  secndNeighbor = firstNeighbor;

	  fV_l_ = ts.firstV(0).y;
	  firstNeighbor = ts.firstN(0).y;
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  sV_l_ = ts.firstV(0).y;
	  secndNeighbor = ts.firstN(0).y;
	}
      }
    }

    /* reduction */
    {
      /* NF NS
	*       OF OS
	*/
      if (fV_l_ > ts.secndV(0).z) {
	firstNeighbor = ts.firstN(0).z;
	secndNeighbor = ts.secndN(0).z;

	fV_l_ = ts.firstV(0).z;
	sV_l_ = ts.secndV(0).z;
      }
      /*       NF NS
	* OF OS
	*/
      else if (sV_l_ > ts.firstV(0).z) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (fV_l_ > ts.firstV(0).z) {
	  sV_l_ = fV_l_;
	  secndNeighbor = firstNeighbor;

	  fV_l_ = ts.firstV(0).z;
	  firstNeighbor = ts.firstN(0).z;
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  sV_l_ = ts.firstV(0).z;
	  secndNeighbor = ts.firstN(0).z;
	}
      }
    }

    /* reduction */
    {
      /* NF NS
	*       OF OS
	*/
      if (fV_l_ > ts.secndV(0).w) {
	firstNeighbor = ts.firstN(0).w;
	secndNeighbor = ts.secndN(0).w;

	fV_l_ = ts.firstV(0).w;
	sV_l_ = ts.secndV(0).w;
      }
      /*       NF NS
	* OF OS
	*/
      else if (sV_l_ > ts.firstV(0).w) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (fV_l_ > ts.firstV(0).w) {
	  sV_l_ = fV_l_;
	  secndNeighbor = firstNeighbor;

	  fV_l_ = ts.firstV(0).w;
	  firstNeighbor = ts.firstN(0).w;
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  sV_l_ = ts.firstV(0).w;
	  secndNeighbor = ts.firstN(0).w;
	}
      }
    }
  }
};

}

#endif
