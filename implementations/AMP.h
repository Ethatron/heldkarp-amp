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

#ifndef	SOLVETSP_AMP_HPP
#define SOLVETSP_AMP_HPP

#include <amp.h>
#include <amp_graphics.h>
#include <amp_short_vectors.h>

/* if there are problems with the results it's most likely
 * the synchronization isn't perfect still, enable "4" and
 * see if the results are still problematic
 */
//efine	WAVEFRONT_SIZE	4	// Warp
//efine	WAVEFRONT_SIZE	32	// nVidia
#define	WAVEFRONT_SIZE	64	// AMD

using namespace Concurrency;
using namespace Concurrency::graphics;

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

namespace amphelper {

/* round-to-nearest, round half towards minus infinity */
static float round(float x) restrict(amp,cpu) {
  float integer = (float)(int)x;
  float fraction = x - integer;

  return integer + (fraction <= 0.5 ? 0 : 1);
}

/* round-to-nearest, round half towards minus infinity */
static double round(double x) restrict(amp,cpu) {
  double integer = (double)(int)x;
  double fraction = x - integer;

  return integer + (fraction <= 0.5 ? 0 : 1);
}

/* horizontal add */
static int hadd(int4 &v) restrict(amp,cpu) {
  int4 d = v;
  d.xz += d.yw;
  d.x  += d.z;
  return d.x;
}

/* horizontal multiply */
static int hmul(int4 &v) restrict(amp,cpu) {
  int4 d = v;
  d.xz *= d.yw;
  d.x  *= d.z;
  return d.x;
}

/* horizontal multiply */
static int2 hmul(int2 &v0, int2 &v1) restrict(amp,cpu) {
  return int2(
    v0.x * v0.y,
    v1.x * v1.y
  );
}

/* horizontal multiply */
static int2 hmul(int4 &v0, int4 &v1) restrict(amp,cpu) {
  int4 dh;
  dh.xz = v0.xz * v0.yw;
  dh.yw = v1.xz * v1.yw;
  dh.xy = dh.xy * dh.zw;
  return dh.xy;
}

/* --------------------------------------------------------------------------
 */

#if 0
template<typename sumtype, typename sumvectype, typename chkvectype>
static sumvectype setenabled(const sumvectype &left, const chkvectype &right, const sumtype &mv) restrict(amp,cpu) {
  return sumvectype(
    right.x ? left.x : mv,
    right.y ? left.y : mv,
    right.z ? left.z : mv,
    right.w ? left.w : mv
  );
}

template<typename sumtype, typename sumvectype, typename chkvectype>
static sumvectype setdisabled(const sumvectype &left, const chkvectype &right, const sumtype &mv) restrict(amp,cpu) {
  return sumvectype(
    right.x ? mv : left.x,
    right.y ? mv : left.y,
    right.z ? mv : left.z,
    right.w ? mv : left.w
  );
}
#endif

template<typename sumvectype, typename chkvectype>
static sumvectype setenabled(const sumvectype &left, const chkvectype &right, const sumvectype &mv) restrict(amp,cpu) {
  return sumvectype(
    right.x ? left.x : mv.x,
    right.y ? left.y : mv.y,
    right.z ? left.z : mv.z,
    right.w ? left.w : mv.w
  );
}

template<typename sumvectype, typename chkvectype>
static sumvectype setdisabled(const sumvectype &left, const chkvectype &right, const sumvectype &mv) restrict(amp,cpu) {
  return sumvectype(
    right.x ? mv.x : left.x,
    right.y ? mv.y : left.y,
    right.z ? mv.z : left.z,
    right.w ? mv.w : left.w
  );
}

template<>
static float setenabled(const float &left, const int &right, const float &mv) restrict(amp,cpu) {
  return (right ? left : mv);
}

template<>
static float setdisabled(const float &left, const int &right, const float &mv) restrict(amp,cpu) {
  return (right ? mv : left);
}

template<>
static double setenabled(const double &left, const int &right, const double &mv) restrict(amp,cpu) {
  return (right ? left : mv);
}

template<>
static double setdisabled(const double &left, const int &right, const double &mv) restrict(amp,cpu) {
  return (right ? mv : left);
}

template<typename smtype, typename astype>
static astype smaller(const smtype &left, const smtype &right, const astype &assignleft, const astype &assignright) restrict(amp,cpu) {
  return astype(
    left.x < right.x ? assignleft.x : assignright.x,
    left.y < right.y ? assignleft.y : assignright.y,
    left.z < right.z ? assignleft.z : assignright.z,
    left.w < right.w ? assignleft.w : assignright.w
  );
}

template<typename smtype, typename astype>
static astype greater(const smtype &left, const smtype &right, const astype &assignleft, const astype &assignright) restrict(amp,cpu) {
  return astype(
    left.x > right.x ? assignleft.x : assignright.x,
    left.y > right.y ? assignleft.y : assignright.y,
    left.z > right.z ? assignleft.z : assignright.z,
    left.w > right.w ? assignleft.w : assignright.w
  );
}

template<>
static int smaller<int, int>(const int &left, const int &right, const int &assignleft, const int &assignright) restrict(amp,cpu) {
  return (left < right ? assignleft : assignright);
}

template<>
static int greater<int, int>(const int &left, const int &right, const int &assignleft, const int &assignright) restrict(amp,cpu) {
  return (left > right ? assignleft : assignright);
}

template<>
static int smaller<float, int>(const float &left, const float &right, const int &assignleft, const int &assignright) restrict(amp,cpu) {
  return (left < right ? assignleft : assignright);
}

template<>
static int greater<float, int>(const float &left, const float &right, const int &assignleft, const int &assignright) restrict(amp,cpu) {
  return (left > right ? assignleft : assignright);
}

template<>
static int smaller<double, int>(const double &left, const double &right, const int &assignleft, const int &assignright) restrict(amp,cpu) {
  return (left < right ? assignleft : assignright);
}

template<>
static int greater<double, int>(const double &left, const double &right, const int &assignleft, const int &assignright) restrict(amp,cpu) {
  return (left > right ? assignleft : assignright);
}

template<>
static float smaller<float, float>(const float &left, const float &right, const float &assignleft, const float &assignright) restrict(amp,cpu) {
  return (left < right ? assignleft : assignright);
}

template<>
static float greater<float, float>(const float &left, const float &right, const float &assignleft, const float &assignright) restrict(amp,cpu) {
  return (left > right ? assignleft : assignright);
}

template<>
static double smaller<double, double>(const double &left, const double &right, const double &assignleft, const double &assignright) restrict(amp,cpu) {
  return (left < right ? assignleft : assignright);
}

template<>
static double greater<double, double>(const double &left, const double &right, const double &assignleft, const double &assignright) restrict(amp,cpu) {
  return (left > right ? assignleft : assignright);
}

template<typename smtype, typename astype>
static astype smallereq(const smtype &left, const smtype &right, const astype &assignleft, const astype &assignright) restrict(amp,cpu) {
  return astype(
    (left.x < right.x) || ((left.x == right.x) && (assignleft.x < assignright.x)) ? assignleft.x : assignright.x,
    (left.y < right.y) || ((left.y == right.y) && (assignleft.y < assignright.y)) ? assignleft.y : assignright.y,
    (left.z < right.z) || ((left.z == right.z) && (assignleft.z < assignright.z)) ? assignleft.z : assignright.z,
    (left.w < right.w) || ((left.w == right.w) && (assignleft.w < assignright.w)) ? assignleft.w : assignright.w
  );
}

template<typename smtype, typename astype>
static astype greatereq(const smtype &left, const smtype &right, const astype &assignleft, const astype &assignright) restrict(amp,cpu) {
  return astype(
    (left.x > right.x) || ((left.x == right.x) && (assignleft.x > assignright.x)) ? assignleft.x : assignright.x,
    (left.y > right.y) || ((left.y == right.y) && (assignleft.y > assignright.y)) ? assignleft.y : assignright.y,
    (left.z > right.z) || ((left.z == right.z) && (assignleft.z > assignright.z)) ? assignleft.z : assignright.z,
    (left.w > right.w) || ((left.w == right.w) && (assignleft.w > assignright.w)) ? assignleft.w : assignright.w
  );
}

/* --------------------------------------------------------------------------
 */

template<typename smtype, typename astype, const int tilestride>
struct ampminima {
  /* divide into 4/32/64 buckets (wavefront size) */
  static const int blcksize = ((tilestride + WAVEFRONT_SIZE - 1) / WAVEFRONT_SIZE);

  astype firstN[WAVEFRONT_SIZE];
  astype secndN[WAVEFRONT_SIZE];
  smtype firstVal[WAVEFRONT_SIZE];
  smtype secndVal[WAVEFRONT_SIZE];

  static const int occupied() {
    return WAVEFRONT_SIZE * 2 * (sizeof(smtype) + sizeof(astype));
  }

  void init(int w, smtype def) restrict(amp,cpu) {
    firstN[w] = 0;
    secndN[w] = 0;
    firstVal[w] = def;
    secndVal[w] = def;
  }

  void orderedmin(int w, const smtype &wght, const astype &curindex) restrict(amp,cpu) {
    secndN  [w] = amphelper::smaller(wght, secndVal[w],    curindex, secndN  [w]);
    secndVal[w] = amphelper::smaller(wght, secndVal[w],        wght, secndVal[w]);

    secndN  [w] = amphelper::smaller(wght, firstVal[w], firstN  [w], secndN  [w]);
    secndVal[w] = amphelper::smaller(wght, firstVal[w], firstVal[w], secndVal[w]);

    firstN  [w] = amphelper::smaller(wght, firstVal[w],    curindex, firstN  [w]);
    firstVal[w] = amphelper::smaller(wght, firstVal[w],        wght, firstVal[w]);
  }

  void orderedred2(int limit, int w) restrict(amp,cpu) {
    int l = min(WAVEFRONT_SIZE, limit);
    for (int j = 2; j < l; j += 2) {
      /* assign to bucket 0/1 */
      orderedmin(w, secndVal[w + j], secndN[w + j]);
      orderedmin(w, firstVal[w + j], firstN[w + j]);
    }
  }

  void orderedred1(int limit) restrict(amp,cpu) {
    if (1 < WAVEFRONT_SIZE) {
      /* read from bucket 1, assign to bucket 0 */
      orderedmin(0, secndVal[0 + 1], secndN[0 + 1]);
      orderedmin(0, firstVal[0 + 1], firstN[0 + 1]);
    }
  }

  template<typename sctype>
  void orderedmallest(int &firstNeighbor, int &secndNeighbor) restrict(amp,cpu) {
    /* get the two cheapest edges from row 0 */
    firstNeighbor = firstN[0].x;
    secndNeighbor = secndN[0].x;

    /* prevent writing back to tile_shared */
    sctype fV_l_ = firstVal[0].x;
    sctype sV_l_ = secndVal[0].x;

    /* reduction */
    {
      /* NF NS
	*       OF OS
	*/
      if (fV_l_ > secndVal[0].y) {
	firstNeighbor = firstN[0].y;
	secndNeighbor = secndN[0].y;

	fV_l_ = firstVal[0].y;
	sV_l_ = secndVal[0].y;
      }
      /*       NF NS
	* OF OS
	*/
      else if (sV_l_ > firstVal[0].y) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (fV_l_ > firstVal[0].y) {
	  sV_l_ = fV_l_;
	  secndNeighbor = firstNeighbor;

	  fV_l_ = firstVal[0].y;
	  firstNeighbor = firstN[0].y;
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  sV_l_ = firstVal[0].y;
	  secndNeighbor = firstN[0].y;
	}
      }
    }

    /* reduction */
    {
      /* NF NS
	*       OF OS
	*/
      if (fV_l_ > secndVal[0].z) {
	firstNeighbor = firstN[0].z;
	secndNeighbor = secndN[0].z;

	fV_l_ = firstVal[0].z;
	sV_l_ = secndVal[0].z;
      }
      /*       NF NS
	* OF OS
	*/
      else if (sV_l_ > firstVal[0].z) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (fV_l_ > firstVal[0].z) {
	  sV_l_ = fV_l_;
	  secndNeighbor = firstNeighbor;

	  fV_l_ = firstVal[0].z;
	  firstNeighbor = firstN[0].z;
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  sV_l_ = firstVal[0].z;
	  secndNeighbor = firstN[0].z;
	}
      }
    }

    /* reduction */
    {
      /* NF NS
	*       OF OS
	*/
      if (fV_l_ > secndVal[0].w) {
	firstNeighbor = firstN[0].w;
	secndNeighbor = secndN[0].w;

	fV_l_ = firstVal[0].w;
	sV_l_ = secndVal[0].w;
      }
      /*       NF NS
	* OF OS
	*/
      else if (sV_l_ > firstVal[0].w) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (fV_l_ > firstVal[0].w) {
	  sV_l_ = fV_l_;
	  secndNeighbor = firstNeighbor;

	  fV_l_ = firstVal[0].w;
	  firstNeighbor = firstN[0].w;
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  sV_l_ = firstVal[0].w;
	  secndNeighbor = firstN[0].w;
	}
      }
    }
  }
};

/* --------------------------------------------------------------------------
 */

template<typename smtype, typename astype>
int usmallest(const smtype &index, const astype &value) restrict(amp,cpu) {
  smtype lg;
  astype cg;

#if 0
  /* don't maintain lower index in case of equality */
  lg.x = (value.x > value.y ? index.y : index.x);
  lg.y = (value.z > value.w ? index.w : index.z);
  cg.x = (value.x > value.y ? value.y : value.x);
  cg.y = (value.z > value.w ? value.w : value.z);
  lg.x = (cg.x > cg.y ? lg.y : lg.x);
#else
  /* maintain lower index in case of equality */
  lg.x = (value.x >= value.y ? (value.x == value.y ? (index.y < index.x ? index.y : index.x) : index.y) : index.x);
  cg.x = (value.x >= value.y ?                                                                 value.y  : value.x);
  lg.y = (value.z >= value.w ? (value.z == value.w ? (index.w < index.z ? index.w : index.z) : index.w) : index.z);
  cg.y = (value.z >= value.w ?                                                                 value.w  : value.z);
  lg.x = (cg.x >= cg.y ? (cg.x == cg.y ? (lg.y < lg.x ? lg.y : lg.x) : lg.y) : lg.x);
#endif

  return lg.x;
}

template<typename smtype, typename astype>
int usmallestneg(const smtype &index, const astype &value) restrict(amp,cpu) {
  smtype lg;
  astype cg;

#if 0
  /* don't maintain lower index in case of equality */
  lg.x = (value.x > value.y ? index.y : index.x);
  lg.z = (value.z > value.w ? index.w : index.z);
  cg.x = (value.x > value.y ? value.y : value.x);
  cg.z = (value.z > value.w ? value.w : value.z);
  lg.x = (cg.x > cg.z ? lg.z : lg.x);
  cg.x = (cg.x > cg.z ? cg.z : cg.x);
  lg.x = (cg.x > 0    ?   -1 : lg.x);
#else
  /* maintain lower index in case of equality */
  lg.x = (value.x >= value.y ? (value.x == value.y ? (index.y < index.x ? index.y : index.x) : index.y) : index.x);
  cg.x = (value.x >= value.y ?                                                                 value.y  : value.x);
  lg.z = (value.z >= value.w ? (value.z == value.w ? (index.w < index.z ? index.w : index.z) : index.w) : index.z);
  cg.z = (value.z >= value.w ?                                                                 value.w  : value.z);
  lg.x = (cg.x >= cg.z ? (cg.x == cg.z ? (lg.z < lg.x ? lg.z : lg.x) : lg.z) : lg.x);
  cg.x = (cg.x >= cg.z ?                                               cg.z  : cg.x);
  lg.x = (cg.x > 0    ?   -1 : lg.x);
#endif

  return lg.x;
}

}

#endif
