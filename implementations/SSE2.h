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

#ifndef	SOLVETSP_SSE2_HPP
#define SOLVETSP_SSE2_HPP

#include <map>
#include <vector>

#include "../helpers/Maths.h"

#if	(_M_IX86_FP >= 2) || (_M_X64)
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>

/* round-to-nearest, round half towards minus infinity */
template<>
static float round<float>(float x) {
#if 1
  __m128i iinteger;
  __m128  finteger;
  __m128  fraction = _mm_setzero_ps();

  /* problem if overflows 2^31 */
  fraction = _mm_load_ss(&x);
  iinteger = _mm_cvttps_epi32(fraction);
  finteger = _mm_cvtepi32_ps(iinteger);
  fraction = _mm_sub_ps(fraction, finteger);
  fraction = _mm_cmpgt_ps(fraction, _mm_set_ps1(0.5));	// ? 0 : -1
  fraction = _mm_cvtepi32_ps(_mm_castps_si128(fraction));
  finteger = _mm_sub_ps(finteger, fraction);
  _mm_store_ss(&x, finteger);

  return x;
#elif 1
  /* this is round-nearest-tie-zero, super slow */
  sumtype integer;
  sumtype fraction = modf(x, &integer);

  return integer + (fraction <= 0.5 ? 0 : 1);
#else
  /* this is round-nearest-tie-even according to standard */
  return floor(this->lowerBound + 0.5);
#endif
}

/* round-to-nearest, round half towards minus infinity */
template<>
static double round<double>(double x) {
#if 1
  __m128i iinteger;
  __m128d finteger;
  __m128d fraction = _mm_setzero_pd();

  /* problem if overflows 2^31 */
  fraction = _mm_load_sd(&x);
  iinteger = _mm_cvttpd_epi32(fraction);
  finteger = _mm_cvtepi32_pd(iinteger);
  fraction = _mm_sub_pd(fraction, finteger);
  fraction = _mm_cmpgt_pd(fraction, _mm_set1_pd(0.5));	// ? 0 : -1
  fraction = _mm_cvtepi32_pd(_mm_castpd_si128(fraction));
  finteger = _mm_sub_pd(finteger, fraction);
  _mm_store_sd(&x, finteger);

  return x;
#elif 1
  /* this is round-nearest-tie-zero, super slow */
  sumtype integer;
  sumtype fraction = modf(x, &integer);

  return integer + (fraction <= 0.5 ? 0 : 1);
#else
  /* this is round-nearest-tie-even according to standard */
  return floor(this->lowerBound + 0.5);
#endif
}

/* --------------------------------------------------------------------------
 */

template<class T>
class SSE2Allocator {

public:
  typedef T          value_type;
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;

  typedef T*         pointer;
  typedef const T*   const_pointer;

  typedef T&         reference;
  typedef const T&   const_reference;

  SSE2Allocator()  {
  }

  // copy constructor
  SSE2Allocator(const SSE2Allocator &obj) {
  }

private:
  void operator = (const SSE2Allocator &);

public:
  template<class _Other>
  SSE2Allocator(const SSE2Allocator<_Other> &other) {
  }

  ~SSE2Allocator() {
  }

  template <class U>
  struct rebind {
    typedef SSE2Allocator<U> other;
  };

  pointer address(reference r) const {
    return &r;
  }

  const_pointer address(const_reference r) const {
    return &r;
  }

  pointer allocate(size_type n, const void * /*hint*/=0 ) {
    void *ret;
    size_t sz = n * sizeof(T);

    /* pointer alignment AND size alignment */
    ret = _aligned_malloc((sz + 15) & (~15), 16);

    return (pointer)ret;
  }

  void deallocate(pointer p, size_type n) {
    _aligned_free(p /*, n * sizeof(T)*/);
  }

  void construct(pointer p, const T& val) {
    new (p) T(val);
  }

  void destroy(pointer p) {
    p->~T();
  }

  size_type max_size() const {
    return ULONG_MAX / sizeof(T);
  }
};

template<class T>
bool operator == (const SSE2Allocator<T>& left, const SSE2Allocator<T>& right) {
  return (true);
}

template<class T>
bool operator != (const SSE2Allocator<T>& left, const SSE2Allocator<T>& right) {
  return (false);
}

/* --------------------------------------------------------------------------
 */

template<typename idxtype>
static void __forceinline duplicate(int val, __m128i &cval, __m128i &pval);

template<>
static void __forceinline duplicate<long>(int val, __m128i &cval, __m128i &pval) {
  cval = _mm_setzero_si128();
  pval = _mm_cvtsi32_si128(val);
  pval = _mm_shuffle_epi32(pval, _MM_SHUFFLE(0, 0, 0, 0));

  /* bad
  pval = _mm_set_epi32(
    val, val, val, val); */
}

template<>
static void __forceinline duplicate<short>(int val, __m128i &cval, __m128i &pval) {
  cval = _mm_setzero_si128();
  pval = _mm_cvtsi32_si128(val);
  pval = _mm_unpacklo_epi16(pval, pval);
  pval = _mm_shuffle_epi32(pval, _MM_SHUFFLE(0, 0, 0, 0));

  /* bad -> pinsrw WTF
  pval = _mm_set_epi16(
    val, val, val, val,
    val, val, val, val); */
}

template<>
static void __forceinline duplicate<char>(int val, __m128i &cval, __m128i &pval) {
  cval = _mm_setzero_si128();
  pval = _mm_cvtsi32_si128(val);
  pval = _mm_unpacklo_epi8(pval, pval);
  pval = _mm_unpacklo_epi16(pval, pval);
  pval = _mm_shuffle_epi32(pval, _MM_SHUFFLE(0, 0, 0, 0));

  /* bad
  pval = _mm_set_epi8(
    val, val, val, val,
    val, val, val, val,
    val, val, val, val,
    val, val, val, val); */
}

/* --------------------------------------------------------------------------
 */

template<typename edgtype>
static void __forceinline fetchd(const edgtype *mem, __m128d &a, __m128d &b);

template<>
static void __forceinline fetchd<uchar>(const uchar *mem, __m128d &a, __m128d &b) {
  __m128i c, d;

  c = _mm_cvtsi32_si128(*((int *)(mem + 0)));
  c = _mm_unpacklo_epi8(c, _mm_setzero_si128());
  c = _mm_unpacklo_epi16(c, _mm_setzero_si128());
  d = _mm_shuffle_epi32(c, _MM_SHUFFLE(3, 2, 3, 2));
  a = _mm_cvtepi32_pd(c);
  b = _mm_cvtepi32_pd(d);
}

template<>
static void __forceinline fetchd<ushort>(const ushort *mem, __m128d &a, __m128d &b) {
  __m128i c, d;

  c = _mm_loadu_si128((__m128i *)(mem + 0));
  c = _mm_unpacklo_epi16(c, _mm_setzero_si128());
  d = _mm_shuffle_epi32(c, _MM_SHUFFLE(3, 2, 3, 2));
  a = _mm_cvtepi32_pd(c);
  b = _mm_cvtepi32_pd(d);
}

template<>
static void __forceinline fetchd<ulong>(const ulong *mem, __m128d &a, __m128d &b) {
  __m128i c, d;

  c = _mm_loadu_si128((__m128i *)(mem + 0));
  d = _mm_shuffle_epi32(c, _MM_SHUFFLE(3, 2, 3, 2));
  a = _mm_cvtepi32_pd(c);
  b = _mm_cvtepi32_pd(d);
}

template<>
static void __forceinline fetchd<float>(const float *mem, __m128d &a, __m128d &b) {
  __m128 c, d;

  c = _mm_loadu_ps(mem + 0);
  d = _mm_movehl_ps(c, c);
  a = _mm_cvtps_pd(c);
  b = _mm_cvtps_pd(d);
}

template<>
static void __forceinline fetchd<double>(const double *mem, __m128d &a, __m128d &b) {
  a = _mm_loadu_pd(mem + 0);
  b = _mm_loadu_pd(mem + 2);
}

/* --------------------------------------------------------------------------
 */

template<typename edgtype>
static void __forceinline fetchf(const edgtype *mem, __m128 &ab);

template<>
static void __forceinline fetchf<uchar>(const uchar *mem, __m128 &ab) {
  __m128i c;

  c = _mm_cvtsi32_si128(*((int *)(mem + 0)));
  c = _mm_unpacklo_epi8(c, _mm_setzero_si128());
  c = _mm_unpacklo_epi16(c, _mm_setzero_si128());
  ab = _mm_cvtepi32_ps(c);
}

template<>
static void __forceinline fetchf<ushort>(const ushort *mem, __m128 &ab) {
  __m128i c;

  c = _mm_loadu_si128((__m128i *)(mem + 0));
  c = _mm_unpacklo_epi16(c, _mm_setzero_si128());
  ab = _mm_cvtepi32_ps(c);
}

template<>
static void __forceinline fetchf<ulong>(const ulong *mem, __m128 &ab) {
  __m128i c;

  c = _mm_loadu_si128((__m128i *)(mem + 0));
  ab = _mm_cvtepi32_ps(c);
}

template<>
static void __forceinline fetchf<float>(const float *mem, __m128 &ab) {
  ab = _mm_loadu_ps(mem + 0);
}

template<>
static void __forceinline fetchf<double>(const double *mem, __m128 &ab) {
  abort();
}

/* --------------------------------------------------------------------------
 */

template<typename sumtype>
static void __forceinline cached(sumtype *mem, __m128d a, __m128d b);

template<>
static void __forceinline cached<double>(double *mem, __m128d a, __m128d b) {
  _mm_store_pd(mem + 0, a);
  _mm_store_pd(mem + 2, b);
}

template<>
static void __forceinline cached<float>(float *mem, __m128d a, __m128d b) {
  abort();
}

/* --------------------------------------------------------------------------
 */

template<typename sumtype>
static void __forceinline cachef(sumtype *mem, __m128 ab);

template<>
static void __forceinline cachef<float>(float *mem, __m128 ab) {
  _mm_store_ps(mem + 0, ab);
}

template<>
static void __forceinline cachef<double>(double *mem, __m128 ab) {
  abort();
}

/* --------------------------------------------------------------------------
 * vertical duplication
 */

template<typename sumtype>
static void __forceinline loadvd(const sumtype *mem, __m128d &a, __m128d &b);

template<>
static void __forceinline loadvd<double>(const double *mem, __m128d &a, __m128d &b) {
  a = _mm_load_sd(mem + 0);
  b = _mm_movedup_pd(a);
  a = b;
}

template<>
static void __forceinline loadvd<float>(const float *mem, __m128d &a, __m128d &b) {
  abort();
}

template<typename sumtype>
static void __forceinline loadwd(const sumtype *mem, __m128d &a, __m128d &b);

template<>
static void __forceinline loadwd<double>(const double *mem, __m128d &a, __m128d &b) {
  a = _mm_load_pd(mem + 0);
  b = _mm_load_pd(mem + 2);
}

template<>
static void __forceinline loadwd<float>(const float *mem, __m128d &a, __m128d &b) {
  abort();
}

template<typename sumtype>
static void __forceinline savewd(sumtype *mem, __m128d a, __m128d b);

template<>
static void __forceinline savewd<double>(double *mem, __m128d a, __m128d b) {
  _mm_store_pd(mem + 0, a);
  _mm_store_pd(mem + 2, b);
}

template<>
static void __forceinline savewd<float>(float *mem, __m128d a, __m128d b) {
  abort();
}

/* --------------------------------------------------------------------------
 * horizontal
 */

template<typename sumtype>
static void __forceinline loadvf(const sumtype *mem, __m128 &ab);

template<>
static void __forceinline loadvf<float>(const float *mem, __m128 &ab) {
  ab = _mm_load_ss(mem + 0);
  ab = _mm_shuffle_ps(ab, ab, _MM_SHUFFLE(0, 0, 0, 0));
}

template<>
static void __forceinline loadvf<double>(const double *mem, __m128 &ab) {
  abort();
}

template<typename sumtype>
static void __forceinline loadwf(const sumtype *mem, __m128 &ab);

template<>
static void __forceinline loadwf<float>(const float *mem, __m128 &ab) {
  ab = _mm_load_ps(mem + 0);
}

template<>
static void __forceinline loadwf<double>(const double *mem, __m128 &ab) {
  abort();
}

template<typename sumtype>
static void __forceinline savewf(sumtype *mem, __m128 ab);

template<>
static void __forceinline savewf<float>(float *mem, __m128 ab) {
  _mm_store_ps(mem + 0, ab);
}

template<>
static void __forceinline savewf<double>(double *mem, __m128 ab) {
  abort();
}

/* --------------------------------------------------------------------------
 * horizontal index
 */

template<typename idxtype>
static void __forceinline loadws(const idxtype *mem, __m128i &i);

template<>
static void __forceinline loadws<short>(const short *mem, __m128i &i) {
  i = _mm_loadu_si128((__m128i *)mem + 0);
}

template<typename idxtype>
static void __forceinline savews(idxtype *mem, __m128i i);

template<>
static void __forceinline savews<short>(short *mem, __m128i i) {
  _mm_storeu_si128((__m128i *)mem + 0, i);
}

/* ##########################################################################
 * add
 */

template<typename sumtype, typename edgtype>
static void __forceinline weightedadd(__m128d &edgewght01, __m128d &edgewght23, int i, int j, int edgestride, __m128i bitfield, sumtype *weights, sumtype *wghtmatrix, const edgtype *edgematrix) {
  __m128d bitfield01;
  __m128d bitfield23;
  __m128d vertwght01, horzwght01;
  __m128d vertwght23, horzwght23;

  // 8000 0000 8000 0000 8000 0000 0000 0000
  bitfield01 = _mm_castsi128_pd(_mm_unpacklo_epi32(_mm_setzero_si128(), bitfield));
  bitfield23 = _mm_castsi128_pd(_mm_unpackhi_epi32(_mm_setzero_si128(), bitfield));
  // -     DBL_MAX       +     DBL_MAX
  // -     DBL_MAX       -     DBL_MAX
  bitfield01 = _mm_or_pd(bitfield01, _mm_set1_pd(DBL_MAX));
  bitfield23 = _mm_or_pd(bitfield23, _mm_set1_pd(DBL_MAX));

  loadvd(&weights   [0]                        + (i + 0), vertwght01, vertwght23);
  loadwd(&weights   [0]                        + (j + 0), horzwght01, horzwght23);
  fetchd(&edgematrix[0] + (i + 0) * edgestride + (j + 0), edgewght01, edgewght23);

  /* wghtmatrix[(i + 0) * edgestride + (j + 0)] = edgematrix[(i + 0) * edgestride + (j + 0)] + weights[(i + 0)] + weights[(j + 0)];
   * wghtmatrix[(i + 0) * edgestride + (j + 1)] = edgematrix[(i + 0) * edgestride + (j + 1)] + weights[(i + 0)] + weights[(j + 1)];
   * wghtmatrix[(i + 0) * edgestride + (j + 2)] = edgematrix[(i + 0) * edgestride + (j + 2)] + weights[(i + 0)] + weights[(j + 2)];
   * wghtmatrix[(i + 0) * edgestride + (j + 3)] = edgematrix[(i + 0) * edgestride + (j + 3)] + weights[(i + 0)] + weights[(j + 3)]; */
  edgewght01 = _mm_add_pd(edgewght01, _mm_add_pd(vertwght01, horzwght01));
  edgewght23 = _mm_add_pd(edgewght23, _mm_add_pd(vertwght23, horzwght23));

  /* if (this->excluded[i * edgestride + j])
    *   wghtmatrix[i * edgestride + j] = (sizeof(sumtype) == sizeof(double) ? DBL_MAX : FLT_MAX); */
  edgewght01 = _mm_max_pd(edgewght01, bitfield01);
  edgewght23 = _mm_max_pd(edgewght23, bitfield23);

  cached(&wghtmatrix[0] + (i + 0) * edgestride + (j + 0), edgewght01, edgewght23);
}

/* -------------------------------------------------------------------------- */

template<typename sumtype, typename edgtype>
static void __forceinline weightedadd(__m128 &edgewght0123, int i, int j, int edgestride, __m128i bitfield, sumtype *weights, sumtype *wghtmatrix, const edgtype *edgematrix) {
  __m128 bitfield0123;
  __m128 vertwght0123, horzwght0123;

  // 8000 0000 8000 0000 8000 0000 0000 0000
  bitfield0123 = _mm_castsi128_ps(bitfield);
  // - FLT_MAX - FLT_MAX - FLT_MAX + FLT_MAX
  bitfield0123 = _mm_or_ps(bitfield0123, _mm_set_ps1(FLT_MAX));

  loadvf(&weights   [0]                        + (i + 0), vertwght0123);
  loadwf(&weights   [0]                        + (j + 0), horzwght0123);
  fetchf(&edgematrix[0] + (i + 0) * edgestride + (j + 0), edgewght0123);

  /* wghtmatrix[(i + 0) * edgestride + (j + 0)] = edgematrix[(i + 0) * edgestride + (j + 0)] + weights[(i + 0)] + weights[(j + 0)];
   * wghtmatrix[(i + 0) * edgestride + (j + 1)] = edgematrix[(i + 0) * edgestride + (j + 1)] + weights[(i + 0)] + weights[(j + 1)];
   * wghtmatrix[(i + 0) * edgestride + (j + 2)] = edgematrix[(i + 0) * edgestride + (j + 2)] + weights[(i + 0)] + weights[(j + 2)];
   * wghtmatrix[(i + 0) * edgestride + (j + 3)] = edgematrix[(i + 0) * edgestride + (j + 3)] + weights[(i + 0)] + weights[(j + 3)]; */
  edgewght0123 = _mm_add_ps(edgewght0123, _mm_add_ps(vertwght0123, horzwght0123));

  /* if (this->excluded[i * edgestride + j])
    *   wghtmatrix[i * edgestride + j] = (sizeof(sumtype) == sizeof(double) ? DBL_MAX : FLT_MAX); */
  edgewght0123 = _mm_max_ps(edgewght0123, bitfield0123);

  cachef(&wghtmatrix[0] + (i + 0) * edgestride + (j + 0), edgewght0123);
}

/* ##########################################################################
 * ordered minimum
 *
 * TODO: check if the non-inline performs worst, or
 *       better (shorter code for all other threads)
 */

class minima {

public:
  minima(bool d) {
    indxsecnd0123   = _mm_setzero_si128(),
    indxfirst0123   = _mm_setzero_si128();

    if (d) {
      dvalsecnd01   = _mm_set_pd(DBL_MAX, DBL_MAX),
      dvalsecnd23   = _mm_set_pd(DBL_MAX, DBL_MAX),
      dvalfirst01   = _mm_set_pd(DBL_MAX, DBL_MAX),
      dvalfirst23   = _mm_set_pd(DBL_MAX, DBL_MAX);
    }
    else {
      fvalsecnd0123 = _mm_set_ps(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX),
      fvalfirst0123 = _mm_set_ps(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);
    }
  }

  /* index of smallest first/second */
  __m128i indxsecnd0123,
	  indxfirst0123;
  /* value of smallest first/second */
  union {
    struct {
      __m128d dvalsecnd01, dvalsecnd23,
	      dvalfirst01, dvalfirst23;
    };

    struct {
      __m128  fvalsecnd0123,
	      fvalfirst0123;
    };
  };

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   * reduction of vectorized collection
   */
  template<typename sumtype>
  void getBest(int &firstNeighbor, int &secndNeighbor);

  template<>
  void getBest<double>(int &firstNeighbor, int &secndNeighbor) {
    /* get the two cheapest edges from row 0 */
    firstNeighbor = indxfirst0123.m128i_i32[0];
    secndNeighbor = indxsecnd0123.m128i_i32[0];

    double firstVal = dvalfirst01.m128d_f64[0];
    double secndVal = dvalsecnd01.m128d_f64[0];

    /* reduction */
    for (int j = 1; j < 2; j++) {
      /* NF NS
	*       OF OS
	*/
      if (firstVal > dvalsecnd01.m128d_f64[j]) {
	firstNeighbor = indxfirst0123.m128i_i32[j];
	secndNeighbor = indxsecnd0123.m128i_i32[j];

	firstVal = dvalfirst01.m128d_f64[j];
	secndVal = dvalsecnd01.m128d_f64[j];
      }
      /*       NF NS
	* OF OS
	*/
      else if (secndVal > dvalfirst01.m128d_f64[j]) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (firstVal > dvalfirst01.m128d_f64[j]) {
	  secndVal = firstVal;
	  secndNeighbor = firstNeighbor;

	  firstVal = dvalfirst01.m128d_f64[j];
	  firstNeighbor = indxfirst0123.m128i_i32[j];
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  secndVal = dvalfirst01.m128d_f64[j];
	  secndNeighbor = indxfirst0123.m128i_i32[j];
	}
      }
    }

    /* reduction */
    for (int j = 0; j < 2; j++) {
      /* NF NS
	*       OF OS
	*/
      if (firstVal > dvalsecnd23.m128d_f64[j]) {
	firstNeighbor = indxfirst0123.m128i_i32[2 + j];
	secndNeighbor = indxsecnd0123.m128i_i32[2 + j];

	firstVal = dvalfirst23.m128d_f64[j];
	secndVal = dvalsecnd23.m128d_f64[j];
      }
      /*       NF NS
	* OF OS
	*/
      else if (secndVal > dvalfirst23.m128d_f64[j]) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (firstVal > dvalfirst23.m128d_f64[j]) {
	  secndVal = firstVal;
	  secndNeighbor = firstNeighbor;

	  firstVal = dvalfirst23.m128d_f64[j];
	  firstNeighbor = indxfirst0123.m128i_i32[2 + j];
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  secndVal = dvalfirst23.m128d_f64[j];
	  secndNeighbor = indxfirst0123.m128i_i32[2 + j];
	}
      }
    }
  }

  /* -------------------------------------------------------------------------- */

  template<>
  void getBest<float>(int &firstNeighbor, int &secndNeighbor) {
    /* get the two cheapest edges from row 0 */
    firstNeighbor = indxfirst0123.m128i_i32[0];
    secndNeighbor = indxsecnd0123.m128i_i32[0];

    /* get the two cheapest edges from row 0 */
    float firstVal = fvalfirst0123.m128_f32[0];
    float secndVal = fvalsecnd0123.m128_f32[0];

    /* reduction */
    for (int j = 1; j < 4; j++) {
      /* NF NS
	*       OF OS
	*/
      if (firstVal > fvalsecnd0123.m128_f32[j]) {
	firstNeighbor = indxfirst0123.m128i_i32[j];
	secndNeighbor = indxsecnd0123.m128i_i32[j];

	firstVal = fvalfirst0123.m128_f32[j];
	secndVal = fvalsecnd0123.m128_f32[j];
      }
      /*       NF NS
	* OF OS
	*/
      else if (secndVal > fvalfirst0123.m128_f32[j]) {
	/* NF    NS     | NF       NS
	  *    OF    OS  |    OF OS
	  */
	if (firstVal > fvalfirst0123.m128_f32[j]) {
	  secndVal = firstVal;
	  secndNeighbor = firstNeighbor;

	  firstVal = fvalfirst0123.m128_f32[j];
	  firstNeighbor = indxfirst0123.m128i_i32[j];
	}

	/*    NF NS     |    NF    NS
	  * OF       OS  | OF    OS
	  */
	else {
	  secndVal = fvalfirst0123.m128_f32[j];
	  secndNeighbor = indxfirst0123.m128i_i32[j];
	}
      }
    }

    assert(firstNeighbor != 0);
    assert(secndNeighbor != 0);
    assert(firstNeighbor != secndNeighbor);
  }

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   * vectorized collection
   */

  template<typename sumtype>
  void __forceinline orderedmin(__m128d edgewght01, __m128d edgewght23, int j, int numnodes) {
    __m128i oidxfirst0123 = indxfirst0123;
    __m128i indexcurr0123;
    __m128i indexmask0123;

    __m128d dorgfirst01 = dvalfirst01;
    __m128d dorgfirst23 = dvalfirst23;
    __m128d maskfirst01,
            maskfirst23;

/*  __m128d im01, im23;*/

    // j + 3, j + 2, j + 1, j + 0
    indexcurr0123 = _mm_cvtsi32_si128(j);
    indexcurr0123 = _mm_shuffle_epi32(indexcurr0123, _MM_SHUFFLE(0, 0, 0, 0));
    indexcurr0123 = _mm_add_epi32(indexcurr0123, _mm_set_epi32(3, 2, 1, 0));

    /* exclude j<=0 / j>=numnodes
    indexmask0123 = _mm_and_si128(
      _mm_cmpgt_epi32(indexcurr0123, _mm_setzero_si128()),
      _mm_cmplt_epi32(indexcurr0123, _mm_set1_epi32(numnodes)));
    im01 = _mm_castsi128_pd(_mm_unpacklo_epi32(indexmask0123, indexmask0123));
    im23 = _mm_castsi128_pd(_mm_unpackhi_epi32(indexmask0123, indexmask0123));
    im01 = _mm_andnot_pd(im01, _mm_set1_pd(DBL_MAX));
    im23 = _mm_andnot_pd(im23, _mm_set1_pd(DBL_MAX));
    edgewght01 = _mm_max_pd(edgewght01, im01);
    edgewght23 = _mm_max_pd(edgewght23, im23); */

    /* exclude j<=0
    indexmask0123 = _mm_cmpgt_epi32(indexcurr0123, _mm_setzero_si128());
    indexmask0123 = _mm_slli_epi32(indexmask0123, 31);
    maskfirst01 = _mm_castsi128_pd(_mm_unpacklo_epi32(indexmask0123, indexmask0123));
    maskfirst01 = _mm_or_pd(maskfirst01, _mm_set1_pd(DBL_MAX));
    edgewght01 = _mm_max_pd(edgewght01, maskfirst01); */

    /* done already by excluding all j->j edges (0->0 too) */
    assert((j > 0) || (edgewght01.m128d_f64[0] == DBL_MAX));

    // secndNeighbor = j; smallest j
    maskfirst01 = _mm_cmpgt_pd(dvalsecnd01, edgewght01);
    maskfirst23 = _mm_cmpgt_pd(dvalsecnd23, edgewght23);
    dvalsecnd01 = _mm_min_pd(dvalsecnd01, edgewght01);
    dvalsecnd23 = _mm_min_pd(dvalsecnd23, edgewght23);

    indexmask0123 = _mm_packs_epi32(_mm_castpd_si128(maskfirst01), _mm_castpd_si128(maskfirst23));
    indexmask0123 = _mm_and_si128(indexmask0123, indexcurr0123);
    indxsecnd0123 = _mm_max_epi16(indxsecnd0123, indexmask0123);

    // firstNeighbor = j; smallest j
    maskfirst01 = _mm_cmpgt_pd(dvalfirst01, edgewght01);
    maskfirst23 = _mm_cmpgt_pd(dvalfirst23, edgewght23);
    dvalfirst01 = _mm_min_pd(dvalfirst01, edgewght01);
    dvalfirst23 = _mm_min_pd(dvalfirst23, edgewght23);

    indexmask0123 = _mm_packs_epi32(_mm_castpd_si128(maskfirst01), _mm_castpd_si128(maskfirst23));
    indexcurr0123 = _mm_and_si128(indexcurr0123, indexmask0123);
    indxfirst0123 = _mm_max_epi16(indxfirst0123, indexcurr0123);

    // secndNeighbor = firstNeighbor;
    dorgfirst01 = _mm_and_pd(dorgfirst01, maskfirst01);
    dorgfirst23 = _mm_and_pd(dorgfirst23, maskfirst23);
    maskfirst01 = _mm_andnot_pd(maskfirst01, dvalsecnd01);
    maskfirst23 = _mm_andnot_pd(maskfirst23, dvalsecnd23);
    dvalsecnd01 = _mm_or_pd(maskfirst01, dorgfirst01);
    dvalsecnd23 = _mm_or_pd(maskfirst23, dorgfirst23);

    oidxfirst0123 = _mm_and_si128(oidxfirst0123, indexmask0123);
    indexmask0123 = _mm_andnot_si128(indexmask0123, indxsecnd0123);
    indxsecnd0123 = _mm_or_si128(indexmask0123, oidxfirst0123);
  }

  /* -------------------------------------------------------------------------- */

  template<typename sumtype>
  void __forceinline orderedmin(__m128 edgewght0123, int j, int numnodes) {
    __m128i oidxfirst0123 = indxfirst0123;
    __m128i indexcurr0123;
    __m128i indexmask0123;

    __m128  dorgfirst0123 = fvalfirst0123;
    __m128  maskfirst0123;

    // j + 3, j + 2, j + 1, j + 0
    indexcurr0123 = _mm_cvtsi32_si128(j);
    indexcurr0123 = _mm_shuffle_epi32(indexcurr0123, _MM_SHUFFLE(0, 0, 0, 0));
    indexcurr0123 = _mm_add_epi32(indexcurr0123, _mm_set_epi32(3, 2, 1, 0));

    /* exclude j<=0 / j>=numnodes
    indexmask0123 = _mm_and_si128(
      _mm_cmpgt_epi32(indexcurr0123, _mm_setzero_si128()),
      _mm_cmplt_epi32(indexcurr0123, _mm_set1_epi32(numnodes)));
    maskfirst0123 = _mm_castsi128_ps(indexmask0123);
    maskfirst0123 = _mm_andnot_ps(maskfirst0123, _mm_set_ps1(FLT_MAX));
    edgewght0123 = _mm_max_ps(edgewght0123, maskfirst0123); */

    /* exclude j<=0
    indexmask0123 = _mm_cmpgt_epi32(indexcurr0123, _mm_setzero_si128());
    maskfirst0123 = _mm_castsi128_ps(_mm_slli_epi32(indexmask0123, 31));
    maskfirst0123 = _mm_or_ps(maskfirst0123, _mm_set_ps1(FLT_MAX));
    edgewght0123 = _mm_max_ps(edgewght0123, maskfirst0123); */

    /* done already by excluding all j->j edges (0->0 too) */
    assert((j > 0) || (edgewght0123.m128_f32[0] == FLT_MAX));

    // secndNeighbor = j; smallest j
    maskfirst0123 = _mm_cmpgt_ps(fvalsecnd0123, edgewght0123);
    fvalsecnd0123 = _mm_min_ps(fvalsecnd0123, edgewght0123);

    indexmask0123 = _mm_castps_si128(maskfirst0123);
    indexmask0123 = _mm_and_si128(indexmask0123, indexcurr0123);
    indxsecnd0123 = _mm_max_epi16(indxsecnd0123, indexmask0123);

    // firstNeighbor = j; smallest j
    maskfirst0123 = _mm_cmpgt_ps(fvalfirst0123, edgewght0123);
    fvalfirst0123 = _mm_min_ps(fvalfirst0123, edgewght0123);

    indexmask0123 = _mm_castps_si128(maskfirst0123);
    indexcurr0123 = _mm_and_si128(indexcurr0123, indexmask0123);
    indxfirst0123 = _mm_max_epi16(indxfirst0123, indexcurr0123);

    // secndNeighbor = firstNeighbor;
    dorgfirst0123 = _mm_and_ps(dorgfirst0123, maskfirst0123);
    maskfirst0123 = _mm_andnot_ps(maskfirst0123, fvalsecnd0123);
    fvalsecnd0123 = _mm_or_ps(maskfirst0123, dorgfirst0123);

    oidxfirst0123 = _mm_and_si128(oidxfirst0123, indexmask0123);
    indexmask0123 = _mm_andnot_si128(indexmask0123, indxsecnd0123);
    indxsecnd0123 = _mm_or_si128(indexmask0123, oidxfirst0123);

//  fvalsecnd0123 = _mm_max_ps(fvalsecnd0123, fvalfirst0123);
//  fvalfirst0123 = _mm_min_ps(fvalsecnd0123, fvalfirst0123);
  }
};

/* ##########################################################################
 * min
 */

void __forceinline weightedmin(int i, int j, int edgestride, __m128i cnum0123, __m128i curidx0123, short *parent, double *mstree, const double *wghtmatrix) {
  __m128i lowidx0123;
  __m128d cmsk01, cmsk23;
  __m128d mtxval01, mtxval23;
  __m128d mstval01, mstval23;
  __m128d lowmsk01, lowmsk23;

  // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
  cnum0123 = _mm_unpacklo_epi16(cnum0123, cnum0123);
  // 8000 0000 8000 0000 8000 0000 0000 0000
  cnum0123 = _mm_slli_epi32(cnum0123, 31);
  // 8000 0000 0000 0000 0000 0000 0000 0000
  // 8000 0000 0000 0000 8000 0000 0000 0000
  cmsk01 = _mm_castsi128_pd(_mm_unpacklo_epi32(_mm_setzero_si128(), cnum0123));
  cmsk23 = _mm_castsi128_pd(_mm_unpackhi_epi32(_mm_setzero_si128(), cnum0123));
  // -     DBL_MAX       +     DBL_MAX
  // -     DBL_MAX       -     DBL_MAX
  cmsk01 = _mm_or_pd(cmsk01, _mm_set1_pd(DBL_MAX));
  cmsk23 = _mm_or_pd(cmsk23, _mm_set1_pd(DBL_MAX));

  loadws(&parent    [0]                        + (j + 0), lowidx0123);
  loadwd(&mstree    [0]                        + (j + 0), mstval01, mstval23);
  loadwd(&wghtmatrix[0] + (i + 0) * edgestride + (j + 0), mtxval01, mtxval23);

  mtxval01 = _mm_max_pd(mtxval01, cmsk01);
  mtxval23 = _mm_max_pd(mtxval23, cmsk23);
  lowmsk01 = _mm_cmpgt_pd(mstval01, mtxval01);
  lowmsk23 = _mm_cmpgt_pd(mstval23, mtxval23);
  mstval01 = _mm_min_pd(mstval01, mtxval01);
  mstval23 = _mm_min_pd(mstval23, mtxval23);

  // FFFF FFFF FFFF FFFF 0000 0000 0000 0000
  // FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF ->
  // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
  cnum0123 = _mm_castps_si128(_mm_shuffle_ps(_mm_castpd_ps(lowmsk01), _mm_castpd_ps(lowmsk23), _MM_SHUFFLE(2, 0, 2, 0)));
  // 7FFF FFFF 7FFF FFFF 7FFF FFFF 0000 0000
  cnum0123 = _mm_srli_epi32(cnum0123, 1);
  // 0000 0000 0000 0000 7FFF 7FFF 7FFF 0000
  cnum0123 = _mm_packs_epi32(cnum0123, _mm_setzero_si128());

  lowidx0123 = _mm_or_si128(
    _mm_andnot_si128(cnum0123, lowidx0123),
    _mm_and_si128(cnum0123, curidx0123)
  );

  savews(&parent    [0]                        + (j + 0), lowidx0123);
  savewd(&mstree    [0]                        + (j + 0), mstval01, mstval23);
}

void __forceinline weightedmin(int i, int j, int edgestride, __m128i cnum0123, __m128i curidx0123, short *parent, float *mstree, const float *wghtmatrix) {
  __m128i lowidx0123;
  __m128  cmsk0123;
  __m128  mtxval0123;
  __m128  mstval0123;
  __m128  lowmsk0123;

  // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
  cnum0123 = _mm_unpacklo_epi16(cnum0123, cnum0123);
  // 8000 0000 8000 0000 8000 0000 0000 0000
  cmsk0123 = _mm_castsi128_ps(_mm_slli_epi32(cnum0123, 31));
  // - FLT_MAX - FLT_MAX - FLT_MAX + FLT_MAX
  cmsk0123 = _mm_or_ps(cmsk0123, _mm_set_ps1(FLT_MAX));

  loadws(&parent    [0]                        + (j + 0), lowidx0123);
  loadwf(&mstree    [0]                        + (j + 0), mstval0123);
  loadwf(&wghtmatrix[0] + (i + 0) * edgestride + (j + 0), mtxval0123);

  mtxval0123 = _mm_max_ps(mtxval0123, cmsk0123);
  lowmsk0123 = _mm_cmpgt_ps(mstval0123, mtxval0123);
  mstval0123 = _mm_min_ps(mstval0123, mtxval0123);

  // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
  // 7FFF FFFF 7FFF FFFF 7FFF FFFF 0000 0000
  cnum0123 = _mm_srli_epi32(_mm_castps_si128(lowmsk0123), 1);
  // 0000 0000 0000 0000 7FFF 7FFF 7FFF 0000
  cnum0123 = _mm_packs_epi32(cnum0123, _mm_setzero_si128());

  lowidx0123 = _mm_or_si128(
    _mm_andnot_si128(cnum0123, lowidx0123),
    _mm_and_si128(cnum0123, curidx0123)
  );

  savews(&parent    [0]                        + (j + 0), lowidx0123);
  savewf(&mstree    [0]                        + (j + 0), mstval0123);
}

/* ##########################################################################
 * absolute minimum
 *
 * TODO: check if the non-inline performs worst, or
 *       better (shorter code for all other threads)
 */

class minimum {
public:
  minimum(bool d, int numnodes) {
    hbound0123 = _mm_setzero_si128();
    lbound0123 = _mm_cvtsi32_si128(numnodes);
    lbound0123 = _mm_shuffle_epi32(lbound0123, _MM_SHUFFLE(0, 0, 0, 0));

    lowidx0123 = _mm_setzero_si128();
    if (d) {
      lowval01 = _mm_set1_pd(DBL_MAX);
      lowval23 = _mm_set1_pd(DBL_MAX);
    }
    else {
      lowval0123 = _mm_set_ps1(FLT_MAX);
    }
  }

  __m128i lbound0123,
          hbound0123;
  __m128i lowidx0123,
          curidx0123;
  union {
    struct {
      __m128d lowval01, lowval23,
	      mstval01, mstval23,
	      lowmsk01, lowmsk23;
    };

    struct {
      __m128  lowval0123,
	      mstval0123,
	      lowmsk0123;
    };
  };


  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  */
  void __forceinline getBounds(int &l, int &h) {
    l = _mm_cvtsi128_si32(lbound0123) + 0;
    h = _mm_cvtsi128_si32(hbound0123) + 4;
  }

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   * reduction of vectorized collection
   */
  template<typename sumtype>
  int getBest(int &l, int &h);

  template<>
  int getBest<double>(int &l, int &h) {
    int candidate;
    int best = _mm_cvtsi128_si32(lowidx0123);

    curidx0123 = _mm_shuffle_epi32(lowidx0123, _MM_SHUFFLE(0, 3, 2, 1));
    mstval01 = _mm_shuffle_pd(lowval01, lowval01, _MM_SHUFFLE(1, 1, 1, 1));
    if (_mm_ucomige_sd(lowval01, mstval01)) {
      candidate = _mm_cvtsi128_si32(curidx0123);
      if (_mm_ucomieq_sd(lowval01, mstval01))
	candidate = (candidate < best ? candidate : best);
      best = candidate;
      lowval01 = _mm_move_sd(lowval01, mstval01);
    }

    curidx0123 = _mm_shuffle_epi32(curidx0123, _MM_SHUFFLE(0, 3, 2, 1));
    if (_mm_ucomige_sd(lowval01, lowval23)) {
      candidate = _mm_cvtsi128_si32(curidx0123);
      if (_mm_ucomieq_sd(lowval01, lowval23))
	candidate = (candidate < best ? candidate : best);
      best = candidate;
      lowval01 = _mm_move_sd(lowval01, lowval23);
    }

    curidx0123 = _mm_shuffle_epi32(curidx0123, _MM_SHUFFLE(0, 3, 2, 1));
    mstval23 = _mm_shuffle_pd(lowval23, lowval23, _MM_SHUFFLE(0, 3, 2, 1));
    if (_mm_ucomige_sd(lowval01, mstval23)) {
      candidate = _mm_cvtsi128_si32(curidx0123);
      if (_mm_ucomieq_sd(lowval01, mstval23))
	candidate = (candidate < best ? candidate : best);
      best = candidate;
//    lowval01 = _mm_move_sd(lowval01, mstval23);
    }

    getBounds(l, h);

    return best;
  }

  template<>
  int getBest<float>(int &l, int &h) {
    int candidate;
    int best = _mm_cvtsi128_si32(lowidx0123);

    curidx0123 = _mm_shuffle_epi32(lowidx0123, _MM_SHUFFLE(0, 3, 2, 1));
    mstval0123 = _mm_shuffle_ps(lowval0123, lowval0123, _MM_SHUFFLE(0, 3, 2, 1));
    if (_mm_ucomige_ss(lowval0123, mstval0123)) {
      candidate = _mm_cvtsi128_si32(curidx0123);
      if (_mm_ucomieq_ss(lowval0123, mstval0123))
	candidate = (candidate < best ? candidate : best);
      best = candidate;
      lowval0123 = _mm_move_ss(lowval0123, mstval0123);
    }

    curidx0123 = _mm_shuffle_epi32(curidx0123, _MM_SHUFFLE(0, 3, 2, 1));
    mstval0123 = _mm_shuffle_ps(mstval0123, mstval0123, _MM_SHUFFLE(0, 3, 2, 1));
    if (_mm_ucomige_ss(lowval0123, mstval0123)) {
      candidate = _mm_cvtsi128_si32(curidx0123);
      if (_mm_ucomieq_ss(lowval0123, mstval0123))
	candidate = (candidate < best ? candidate : best);
      best = candidate;
      lowval0123 = _mm_move_ss(lowval0123, mstval0123);
    }

    curidx0123 = _mm_shuffle_epi32(curidx0123, _MM_SHUFFLE(0, 3, 2, 1));
    mstval0123 = _mm_shuffle_ps(mstval0123, mstval0123, _MM_SHUFFLE(0, 3, 2, 1));
    if (_mm_ucomige_ss(lowval0123, mstval0123)) {
      candidate = _mm_cvtsi128_si32(curidx0123);
      if (_mm_ucomieq_ss(lowval0123, mstval0123))
	candidate = (candidate < best ? candidate : best);
      best = candidate;
//    lowval0123 = _mm_move_ss(lowval0123, mstval0123);
    }

    getBounds(l, h);

    return best;
  }

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   */
  void __forceinline setIndex(int i) {
    curidx0123 = _mm_cvtsi32_si128(i);
    curidx0123 = _mm_shuffle_epi32(curidx0123, _MM_SHUFFLE(0, 0, 0, 0));
    curidx0123 = _mm_add_epi32(curidx0123, _mm_set_epi32(3, 2, 1, 0));

    lbound0123 = _mm_min_epi16(lbound0123, curidx0123);
    hbound0123 = _mm_max_epi16(hbound0123, curidx0123);
  }

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   * vectorized collection
   */

  void __forceinline unorderedmin(double *mstree, int i, __m128i cnum0123) {
    __m128d cmsk01, cmsk23;

    setIndex(i);

    // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
    cnum0123 = _mm_unpacklo_epi16(cnum0123, cnum0123);
    // 8000 0000 8000 0000 8000 0000 0000 0000
    cnum0123 = _mm_slli_epi32(cnum0123, 31);
    // 8000 0000 0000 0000 0000 0000 0000 0000
    // 8000 0000 0000 0000 8000 0000 0000 0000
    cmsk01 = _mm_castsi128_pd(_mm_unpacklo_epi32(_mm_setzero_si128(), cnum0123));
    cmsk23 = _mm_castsi128_pd(_mm_unpackhi_epi32(_mm_setzero_si128(), cnum0123));
    // -     DBL_MAX       +     DBL_MAX
    // -     DBL_MAX       -     DBL_MAX
    cmsk01 = _mm_or_pd(cmsk01, _mm_set1_pd(DBL_MAX));
    cmsk23 = _mm_or_pd(cmsk23, _mm_set1_pd(DBL_MAX));

    mstval01 = _mm_load_pd((double *)mstree + i + 0);
    mstval23 = _mm_load_pd((double *)mstree + i + 2);
    mstval01 = _mm_max_pd(mstval01, cmsk01);
    mstval23 = _mm_max_pd(mstval23, cmsk23);

    // i = j; smallest j
    lowmsk01 = _mm_cmpge_pd(mstval01, lowval01);
    lowmsk23 = _mm_cmpge_pd(mstval23, lowval23);
    lowval01 = _mm_min_pd(lowval01, mstval01);
    lowval23 = _mm_min_pd(lowval23, mstval23);

    // FFFF FFFF FFFF FFFF 0000 0000 0000 0000
    // FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF ->
    // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
    cnum0123 = _mm_castps_si128(_mm_shuffle_ps(_mm_castpd_ps(lowmsk01), _mm_castpd_ps(lowmsk23), _MM_SHUFFLE(2, 0, 2, 0)));
    cnum0123  = _mm_xor_si128(cnum0123, curidx0123);		// neg
    lowidx0123 = _mm_max_epi16(lowidx0123, cnum0123);
  }

  /* -------------------------------------------------------------------------- */

  void __forceinline unorderedmin(float *mstree, int i, __m128i cnum0123) {
    __m128  cmsk0123;

    setIndex(i);

    // FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000
    cnum0123 = _mm_unpacklo_epi16(cnum0123, cnum0123);
    // 8000 0000 8000 0000 8000 0000 0000 0000
    cmsk0123 = _mm_castsi128_ps(_mm_slli_epi32(cnum0123, 31));
    // - FLT_MAX - FLT_MAX - FLT_MAX + FLT_MAX
    cmsk0123 = _mm_or_ps(cmsk0123, _mm_set_ps1(FLT_MAX));

    mstval0123 = _mm_load_ps((float *)mstree + i + 0);
    mstval0123 = _mm_max_ps(mstval0123, cmsk0123);

    // i = j; smallest j
    lowmsk0123 = _mm_cmpge_ps(mstval0123, lowval0123);
    lowval0123 = _mm_min_ps(lowval0123, mstval0123);
    lowmsk0123 = _mm_xor_ps(lowmsk0123, _mm_castsi128_ps(curidx0123));	// neg
    lowidx0123 = _mm_max_epi16(lowidx0123, _mm_castps_si128(lowmsk0123));
  }
};

/* ##########################################################################
 * minimum value above 2
 */

void __forceinline above2min(__m128i &lnum0123, __m128i &lidx0123, int j, __m128i cnum0123) {
  __m128i cidx0123;
  __m128i lmsk0123;

  cidx0123 = _mm_cvtsi32_si128(j);
  cidx0123 = _mm_shufflelo_epi16(cidx0123, _MM_SHUFFLE(0, 0, 0, 0));
  cidx0123 = _mm_add_epi16(cidx0123, _mm_set_epi16(0, 0, 0, 0, 3, 2, 1, 0));

  // ---- ---- ---- ---- 8000 8031 8154 7FFE
  cnum0123 = _mm_add_epi16(cnum0123, _mm_set1_epi16(0x7FFD));

  // connections[j] < connections[lg]; smallest j
  lmsk0123 = _mm_cmplt_epi16(cnum0123, lnum0123);
  lnum0123 = _mm_min_epi16(lnum0123, cnum0123);
  lmsk0123 = _mm_and_si128(lmsk0123, cidx0123);
  lidx0123 = _mm_max_epi16(lidx0123, lmsk0123);

  // 8000 0003 8031 0002 8154 0001 7FFE 0000
//cnum0123 = _mm_unpacklo_epi16(cnum0123, cidx0123);
//lidx0123 = _mm_min_epi32(cidx0123, lidx0123);	// SSE4
}

int __forceinline above2min(__m128i lnum0123, __m128i lidx0123) {
  __m128i cnum0123 = _mm_shufflelo_epi16(lnum0123, _MM_SHUFFLE(1, 0, 3, 2));
  __m128i cidx0123 = _mm_shufflelo_epi16(lidx0123, _MM_SHUFFLE(1, 0, 3, 2));

  // ---- ---- ---- ---- 8154 0001 7FFE 0000
  // ---- ---- ---- ---- ---- ---- 8154 0001
  lidx0123 = _mm_unpacklo_epi16(lidx0123, lnum0123);
  cidx0123 = _mm_unpacklo_epi16(cidx0123, cnum0123);
  lnum0123 = _mm_shufflelo_epi16(lidx0123, _MM_SHUFFLE(1, 0, 3, 2));
  cnum0123 = _mm_shufflelo_epi16(cidx0123, _MM_SHUFFLE(1, 0, 3, 2));

  int l0 = _mm_cvtsi128_si32(lidx0123);
  int l1 = _mm_cvtsi128_si32(lnum0123);
  int l2 = _mm_cvtsi128_si32(cidx0123);
  int l3 = _mm_cvtsi128_si32(cnum0123);
  int lg;

  lg =  l0;
  lg = (l1 < lg ? l1 : lg);
  lg = (l2 < lg ? l2 : lg);
  lg = (l3 < lg ? l3 : lg);
  lg = (-1 < lg ? -1 : lg);
  lg = (short)(lg);

  return lg;
}

/* ##########################################################################
 * squares-sum
 */
template<typename idxtype>
void __forceinline sumsquares(int j, __m128i &inom0123, idxtype *connections) {
  __m128i cnum0123;
  __m128i dsqr01;
  __m128i dsqr23;

  // ---- ---- ---- ---- 0003 0034 0156 0001
  cnum0123 = _mm_loadu_si128((__m128i *)&connections[j]);
  cnum0123 = _mm_sub_epi16(cnum0123, _mm_set1_epi16(2));
  dsqr01 = _mm_mullo_epi16(cnum0123, cnum0123);
  dsqr23 = _mm_mulhi_epi16(cnum0123, cnum0123);
  cnum0123 = _mm_unpacklo_epi16(dsqr01, dsqr23);
  inom0123 = _mm_add_epi32(inom0123, cnum0123);
}

void __forceinline sumsquares(__m128d &dnom01, __m128d &dnom23, __m128i inom0123) {
  __m128i cnum0123;

  cnum0123 = _mm_shuffle_epi32(inom0123, _MM_SHUFFLE(1, 0, 3, 2));
  cnum0123 = _mm_add_epi32(cnum0123, inom0123);
  inom0123 = _mm_shuffle_epi32(cnum0123, _MM_SHUFFLE(2, 3, 0, 1));
  inom0123 = _mm_add_epi32(inom0123, cnum0123);

  dnom01 = _mm_cvtepi32_pd(inom0123);
  dnom23 = _mm_cvtepi32_pd(inom0123);
}

void __forceinline sumsquares(__m128 &fnom0123, __m128i inom0123) {
  __m128i cnum0123;

  cnum0123 = _mm_shuffle_epi32(inom0123, _MM_SHUFFLE(1, 0, 3, 2));
  cnum0123 = _mm_add_epi32(cnum0123, inom0123);
  inom0123 = _mm_shuffle_epi32(cnum0123, _MM_SHUFFLE(2, 3, 0, 1));
  inom0123 = _mm_add_epi32(inom0123, cnum0123);

  fnom0123 = _mm_cvtepi32_ps(inom0123);
}

template<typename sumtype, typename idxtype>
void __forceinline mulsquares(int j, __m128d t01, __m128d t23, sumtype *weights, idxtype *connections) {
  __m128i cnum0123;
  __m128i bnum0123;
  __m128d tnum01;
  __m128d tnum23;
  __m128d weight01;
  __m128d weight23;

  loadwd(&weights[0] + (j + 0), weight01, weight23);

  // ---- ---- ---- ---- 0003 0034 0156 0001
  cnum0123 = _mm_loadu_si128((__m128i *)&connections[j]);
  cnum0123 = _mm_unpacklo_epi16(cnum0123, _mm_setzero_si128());
  cnum0123 = _mm_sub_epi32(cnum0123, _mm_set1_epi32(2));
  bnum0123 = _mm_shuffle_epi32(cnum0123, _MM_SHUFFLE(1, 0, 3, 2));
  tnum01 = _mm_cvtepi32_pd(cnum0123);
  tnum23 = _mm_cvtepi32_pd(bnum0123);
  tnum01 = _mm_mul_pd(tnum01, t01);
  tnum23 = _mm_mul_pd(tnum23, t23);
  weight01 = _mm_add_pd(weight01, tnum01);
  weight23 = _mm_add_pd(weight23, tnum23);

  savewd(&weights[0] + (j + 0), weight01, weight23);
}

template<typename sumtype, typename idxtype>
void __forceinline mulsquares(int j, __m128 t0123, sumtype *weights, idxtype *connections) {
  __m128i cnum0123;
  __m128  tnum0123;
  __m128  weight;

  loadwf(&weights[0] + (j + 0), weight);

  // ---- ---- ---- ---- 0003 0034 0156 0001
  cnum0123 = _mm_loadu_si128((__m128i *)&connections[j]);
  cnum0123 = _mm_unpacklo_epi16(cnum0123, _mm_setzero_si128());
  cnum0123 = _mm_sub_epi32(cnum0123, _mm_set1_epi32(2));
  tnum0123 = _mm_cvtepi32_ps(cnum0123);
  tnum0123 = _mm_mul_ps(tnum0123, t0123);
  weight = _mm_add_ps(weight, tnum0123);

  savewf(&weights[0] + (j + 0), weight);
}

#endif
#endif
