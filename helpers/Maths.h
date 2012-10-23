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

#ifndef	MATHS_HPP
#define	MATHS_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <cmath>

/* get the minimum/maximum value for a type */
#if	(_MSC_VER != 1700)
template<typename datatype>
static datatype maxvec();
template<>
static float maxvec<float>() { return FLT_MAX; }
template<>
static double maxvec<double>() { return DBL_MAX; }
template<>
static int maxvec<int>() { return 0x7FFFFFFF; }
template<>
static unsigned int maxvec<unsigned int>() { return 0xFFFFFFFFU; }

template<typename datatype>
static datatype minvec();
template<>
static float minvec<float>() { return FLT_MIN; }
template<>
static double minvec<double>() { return DBL_MIN; }
template<>
static int minvec<int>() { return 1; }
template<>
static unsigned int minvec<unsigned int>() { return 1U; }
#else
template<typename datatype>
static datatype maxvec() restrict(amp,cpu);
template<>
static float maxvec<float>() restrict(amp,cpu) { return FLT_MAX; }
template<>
static double maxvec<double>() restrict(amp,cpu) { return DBL_MAX; }
template<>
static int maxvec<int>() restrict(amp,cpu) { return 0x7FFFFFFF; }
template<>
static unsigned int maxvec<unsigned int>() restrict(amp,cpu) { return 0xFFFFFFFFU; }

template<typename datatype>
static datatype minvec() restrict(amp,cpu);
template<>
static float minvec<float>() restrict(amp,cpu) { return FLT_MIN; }
template<>
static double minvec<double>() restrict(amp,cpu) { return DBL_MIN; }
template<>
static int minvec<int>() restrict(amp,cpu) { return 1; }
template<>
static unsigned int minvec<unsigned int>() restrict(amp,cpu) { return 1U; }
#endif

/* round-to-nearest, round half towards minus infinity */
template<typename sumtype>
sumtype round(sumtype x) {
#if 1
  /* this is round-nearest-tie-zero, super slow */
  sumtype integer;
  sumtype fraction = modf(x, &integer);

  return integer + (fraction <= 0.5 ? 0 : 1);
#else
  /* this is round-nearest-tie-even according to standard */
  return floor(this->lowerBound + 0.5);
#endif
}

/* calculate the faculty of an integer */
static double faculty(int n) {
  double f = n;
  while (--n >= 1)
    f *= n;
  return f;
}

/* calculate a thread-group stride-length which's square (capped at 1024)
 * is divisible by the given cluster-size (wavefront-size)
 * the thread-group height is then the square (or 1024) divided by the result
 */
static int squared_divisible_by(int log2, int SIMDstride, int SIMDcluster = 64, int SIMDsize = 4) {
  if ((log2 / SIMDsize) < 4)
    log2 = 4 * SIMDsize;

  int tgs = log2 / SIMDsize;			// 91 -> 128 -> 32
  int test = tgs;
  while ((test -= 8) > SIMDstride) {		// 32 -> 24
    int tss = max(16, min(test * test, 1024));	// 24 * 24 -> 576
    int tsh = tss / test;			// 576 / 24 -> 24

    /* divisible by SIMDcluster */
    if (!((tsh * test) % SIMDcluster)) {	// 24 * 24 -> 576 % 64 -> 0
      log2 = test * SIMDsize;			// 24 * 4 => 96
    }
  }

  if ((log2 / SIMDsize) < 4)
    log2 = 4 * SIMDsize;

  return log2;
}

#endif
