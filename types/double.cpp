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

#include "../SolveTSP.h"

#if	defined(SOLVE_TSP_with_AMP_CMP_and_Crossfire) ||	\
	defined(SOLVE_TSP_with_AMP_CMP_OptMax) ||		\
	defined(SOLVE_TSP_with_AMP_CMP_Opt) ||			\
	defined(SOLVE_TSP_with_AMP_CMP) ||			\
	defined(SOLVE_TSP_with_AMP_CM_and_Crossfire) ||		\
	defined(SOLVE_TSP_with_AMP_CM_OptMax) ||		\
	defined(SOLVE_TSP_with_AMP_CM_Opt) ||			\
	defined(SOLVE_TSP_with_AMP_CM) ||			\
	defined(SOLVE_TSP_with_AMP)

#include <queue>
#include <array>  // TR1

#if	defined(SOLVE_TSP_with_AMP_CMP_and_Crossfire)
#include "../implementations/AMP-CMP-OptCFX.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CMP_OptMax)
#include "../implementations/AMP-CMP-OptMax.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CMP_Opt)
#include "../implementations/AMP-CMP-Opt.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CMP)
#include "../implementations/AMP-CMP.cpp"

#elif	defined(SOLVE_TSP_with_AMP_CM_and_Crossfire)
#include "../implementations/AMP-CM-OptCFX.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CM_OptMax)
#include "../implementations/AMP-CM-OptMax.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CM_Opt)
#include "../implementations/AMP-CM-Opt.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CM)
#include "../implementations/AMP-CM.cpp"

#elif	defined(SOLVE_TSP_with_AMP)
#include "../implementations/AMP.cpp"
#endif
#endif

#if	defined(SOLVE_TSP_with_SSE2_and_CR_CM)
#include "../implementations/SSE2-ConcRT-CM.cpp"
#elif	defined(SOLVE_TSP_with_SSE2_and_CR)
#include "../implementations/SSE2-ConcRT.cpp"
#elif	defined(SOLVE_TSP_with_SSE2)
#include "../implementations/SSE2.cpp"
#endif

#if	defined(SOLVE_TSP_with_CPU)
#include "../implementations/CPU.cpp"
#endif

/* ------------------------------------------------------------------------
 * receive edge-lists and built solution
 *
 * Visual Studio & AMP has problems with build time and cl crashing
 * we had to split this in 5 files for each type
 */

void SolveTSP(const vector< double > &edgematrix, vector< short > &route, enum TSPHardware hw) {
  const int SIMDsize = hwSIMDsize(hw);
  int
    num = (int)route.size(),
    stride = (int)edgematrix.size() / num;
  
#if !(SOLVE_TSP_dtyp & 16)
  defDT("double");
#endif

  /* ------------------------------------------------------------------------------- */
#if	defined(SOLVE_TSP_with_AMP) && (SOLVE_TSP_dtyp & 16)
  if (isAMP(hw)) {
    /* double-accumulator for double-types */
    Concurrency::array<double4, 2> edgeview(
      num,
      stride / SIMDsize,
      (double4 *)&edgematrix[0]
    );

    tsp_amp_implementation::Solution<double, short, double4, int4> s(num, stride);
    s.solve<double, double4, Concurrency::array<double4, 2> >(edgeview, route);

    return;
  }
#endif

  /* ------------------------------------------------------------------------------- */
#if	defined(SOLVE_TSP_with_SSE2) && (SOLVE_TSP_dtyp & 16)
  if (isVPU(hw)) {
    /* double-accumulator for double-types */
    tsp_vpu_implementation::Solution<double, short> s(num, stride);
    s.solve<double>(edgematrix, route);

    return;
  }
#endif

  /* ------------------------------------------------------------------------------- */
#if	defined(SOLVE_TSP_with_CPU) && (SOLVE_TSP_dtyp & 16)
  if (isCPU(hw)) {
    /* double-accumulator for double-types */
    tsp_cpu_implementation::Solution<double, short> s(num, stride);
    s.solve<double>(edgematrix, route);

    return;
  }
#endif
}
