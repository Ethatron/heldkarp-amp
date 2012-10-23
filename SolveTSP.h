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

#ifndef	SOLVE_TSP_HPP
#define	SOLVE_TSP_HPP

#include "ParseTSP.h"
#include "helpers/Distances.h"
#include "helpers/Profile.h"

#define	SOLVE_TSP_from	256		// min. 0, inclusive, in SIMD-units (divide by 4)
#define	SOLVE_TSP_to	256		// max. 1024, inclusive, in SIMD-units (divide by 4)
#define	SOLVE_TSP_dtyp	(2)		// 1 | 2 | 4 | 8 | 16 -> char | short | long | float | double

/* --------------------------------------------------------------------------------------------------------------------------------------- */

/* C++ AMP implementation for CrossFire/SLI, uses all available accelerators, parallel calculation a a 3D-matrix */
#undef 	SOLVE_TSP_with_AMP_CMP_and_Crossfire
/* C++ AMP implementation sacrificing a bit of speed for memory, parallel calculation a a 3D-matrix, optimize the hell x4 out of it */
#undef	SOLVE_TSP_with_AMP_CMP_OptMax
/* C++ AMP implementation sacrificing a bit of speed for memory, parallel calculation a a 3D-matrix, optimize the hell out of it */
#define	SOLVE_TSP_with_AMP_CMP_Opt
/* C++ AMP implementation sacrificing a bit of speed for memory, parallel calculation a a 3D-matrix */
#define	SOLVE_TSP_with_AMP_CMP

/* C++ AMP implementation for CrossFire/SLI, uses all available accelerators */
#undef 	SOLVE_TSP_with_AMP_CM_and_Crossfire
/* C++ AMP implementation sacrificing a bit of speed for memory, optimize the hell x4 out of it */
#define	SOLVE_TSP_with_AMP_CM_OptMax
/* C++ AMP implementation sacrificing a bit of speed for memory, optimize the hell out of it */
#define	SOLVE_TSP_with_AMP_CM_Opt
/* C++ AMP implementation sacrificing a bit of speed for memory */
#define	SOLVE_TSP_with_AMP_CM
/* C++ AMP implementation, this is the just for verification of above */
#define	SOLVE_TSP_with_AMP

/* SSE2 + Concurrency Runtime implementation sacrificing a bit of speed for memory */
#define	SOLVE_TSP_with_SSE2_and_CR_CM
/* SSE2 + Concurrency Runtime implementation, with sanity checks all over the place, this is the just for verification of above */
#define	SOLVE_TSP_with_SSE2_and_CR
/* SSE2 implementation, initial vectorized code, this is just for verification of above */
#define	SOLVE_TSP_with_SSE2

/* x86/x64 implementation, initial global arrays, this is just for verification of above */
#define	SOLVE_TSP_with_CPU

/* only available from SSE2 on ------------------------------- */
#if	(_M_IX86_FP < 2) && (!_M_X64)
#undef	SOLVE_TSP_with_SSE2_and_CR_CM
#undef	SOLVE_TSP_with_SSE2_and_CR
#undef	SOLVE_TSP_with_SSE2
#endif

/* only available from VS2012 on ----------------------------- */
#if	(_MSC_VER < 1700)
#undef	SOLVE_TSP_with_AMP_CMP_and_Crossfire
#undef	SOLVE_TSP_with_AMP_CMP_OptMax
#undef	SOLVE_TSP_with_AMP_CMP_Opt
#undef	SOLVE_TSP_with_AMP_CMP
#undef	SOLVE_TSP_with_AMP_CM_and_Crossfire
#undef	SOLVE_TSP_with_AMP_CM_OptMax
#undef	SOLVE_TSP_with_AMP_CM_Opt
#undef	SOLVE_TSP_with_AMP_CM
#undef	SOLVE_TSP_with_AMP
#else
#include <amp.h>
#include <amp_graphics.h>
#include <amp_short_vectors.h>

using namespace Concurrency;
using namespace Concurrency::graphics;
#endif

/* make sure we can use at least one ------------------------- */
#if	!defined(SOLVE_TSP_with_AMP_CMP_and_Crossfire) &&	\
	!defined(SOLVE_TSP_with_AMP_CMP_OptMax) &&		\
	!defined(SOLVE_TSP_with_AMP_CMP_Opt) &&			\
	!defined(SOLVE_TSP_with_AMP_CMP) &&			\
	!defined(SOLVE_TSP_with_AMP_CM_and_Crossfire) &&	\
	!defined(SOLVE_TSP_with_AMP_CM_OptMax) &&		\
	!defined(SOLVE_TSP_with_AMP_CM_Opt) &&			\
	!defined(SOLVE_TSP_with_AMP_CM) &&			\
	!defined(SOLVE_TSP_with_AMP) &&				\
	!defined(SOLVE_TSP_with_SSE2_and_CR_CM) &&		\
	!defined(SOLVE_TSP_with_SSE2_and_CR) &&			\
	!defined(SOLVE_TSP_with_SSE2) &&			\
	!defined(SOLVE_TSP_with_CPU)
#error	 "at least one supported implementation must be selected"
#endif

#if	defined(SOLVE_TSP_with_AMP_CMP_and_Crossfire)
#define tsp_amp_implementation	tsp_amp_ccrcmp_optcfx
#elif	defined(SOLVE_TSP_with_AMP_CMP_OptMax)
#define tsp_amp_implementation	tsp_amp_ccrcmp_optmax
#elif	defined(SOLVE_TSP_with_AMP_CMP_Opt)
#define tsp_amp_implementation	tsp_amp_ccrcmp_opt
#elif	defined(SOLVE_TSP_with_AMP_CMP)
#define tsp_amp_implementation	tsp_amp_ccrcmp

#elif	defined(SOLVE_TSP_with_AMP_CM_and_Crossfire)
#define tsp_amp_implementation	tsp_amp_ccrcm_optcfx
#elif	defined(SOLVE_TSP_with_AMP_CM_OptMax)
#define tsp_amp_implementation	tsp_amp_ccrcm_optmax
#elif	defined(SOLVE_TSP_with_AMP_CM_Opt)
#define tsp_amp_implementation	tsp_amp_ccrcm_opt
#elif	defined(SOLVE_TSP_with_AMP_CM)
#define tsp_amp_implementation	tsp_amp_ccrcm

#elif	defined(SOLVE_TSP_with_AMP)
#define tsp_amp_implementation	tsp_amp_ccr
#else
#define tsp_amp_implementation	tsp_void
#endif

#if	defined(SOLVE_TSP_with_SSE2_and_CR_CM)
#define tsp_vpu_implementation	tsp_vpuccr_cm
#elif	defined(SOLVE_TSP_with_SSE2_and_CR)
#define tsp_vpu_implementation	tsp_vpuccr
#elif	defined(SOLVE_TSP_with_SSE2)
#define tsp_vpu_implementation	tsp_vpu
#else
#define tsp_vpu_implementation	tsp_void
#endif

#if	defined(SOLVE_TSP_with_CPU)
#define tsp_cpu_implementation	tsp_cpu
#else
#define tsp_cpu_implementation	tsp_void
#endif

namespace tsp_void {
  const int SIMDsize		= 1;
  const int AccessAlignment	= 1;
  const int MemoryAlignment	= 1;
}

/* --------------------------------------------------------------------------------------------------------------------------------------- */

enum TSPHardware {
  TSPH_CPU_REF = 0,	// unaccelerated CPU
  TSPH_CPU_VPU = 1,	// SSE accelerated CPU
  TSPH_AMP_REF = 2,	// reference AMP
  TSPH_AMP_WRP = 3,	// fast software AMP
  TSPH_AMP_GPU = 4	// GPU accelerated AMP
};

#define isCPU(hw)	(hw <= TSPH_CPU_VPU)
#define isVPU(hw)	(hw == TSPH_CPU_VPU)
#define isAMP(hw)	(hw >= TSPH_AMP_REF)
#define hwSIMDsize(hw)	(					\
  (hw == TSPH_CPU_REF ? tsp_cpu_implementation::SIMDsize :	\
  (hw == TSPH_CPU_VPU ? tsp_vpu_implementation::SIMDsize :	\
  (hw >= TSPH_AMP_REF ? tsp_amp_implementation::SIMDsize :	\
  1))))

/* core functions, takes an adjacency weight matrix, returns a solution */
void SolveTSP(const vector< uchar  > &edgematrix, vector< short > &route, enum TSPHardware hw);
void SolveTSP(const vector< ushort > &edgematrix, vector< short > &route, enum TSPHardware hw);
void SolveTSP(const vector< ulong  > &edgematrix, vector< short > &route, enum TSPHardware hw);
void SolveTSP(const vector< float  > &edgematrix, vector< short > &route, enum TSPHardware hw);
void SolveTSP(const vector< double > &edgematrix, vector< short > &route, enum TSPHardware hw);

/* API functions, takes a vector of type "TSPFormat", builds the adjacency weight matrix, returns a solution */
void SolveTSP(const vector< pair<char  , char  > > &dataset, vector<short> &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist);
void SolveTSP(const vector< pair<short , short > > &dataset, vector<short> &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist);
void SolveTSP(const vector< pair<long  , long  > > &dataset, vector<short> &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist);
void SolveTSP(const vector< pair<float , float > > &dataset, vector<short> &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist);
void SolveTSP(const vector< pair<double, double> > &dataset, vector<short> &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist);

/* --------------------------------------------------------------------------------------------------------------------------------------- */

/* global parameters driving the solver */
extern double lambda_reduction;		// while(...) l = l * lambda_reduction		def.: 0.9
extern double lambda_termination;	// while(l > lambda_termination) ...		def.: 1e-6
extern int thread_limit;		// clamp number of threads			def.: 0 (max threads)
extern size_t memory_limit;		// clamp memory, throw solutions away above	def.: -1 (all mem)

/* global observations of the solver */
extern size_t peak_memory;
extern size_t curr_memory;
extern size_t glob_memory;
extern int num_iterations;
extern critical_section mst;

/* --------------------------------------------------------------------------------------------------------------------------------------- */

#define	defDT(dt)			fprintf(stderr, "SolveTSP(.h) has not been compiled for datatype: %s\n", dt), exit(0)

#if	defined(SOLVE_TSP_with_AMP_CMP)
#define	caseHKn(txf, tx, ty, parm)	case tx: fprintf(stderr, "SolveTSP(.h) has been compiled for solutions in [%d,%d], the given file has [%d]\n", SOLVE_TSP_from * SIMDsize, SOLVE_TSP_to * SIMDsize, tx * SIMDsize); exit(0); return;
#define	caseHKy(txf, tx, ty, parm)	case tx: computeHeldKarp<edgtype, edgvectype, edgresview, ty, tx> parm ; return;
#else
#define	caseHKn(txf, tx, ty, parm)	case tx: fprintf(stderr, "SolveTSP(.h) has been compiled for solutions in [%d,%d], the given file has [%d]\n", SOLVE_TSP_from * SIMDsize, SOLVE_TSP_to * SIMDsize, tx * SIMDsize); exit(0); return false;
#define	caseHKy(txf, tx, ty, parm)	case tx: return computeHeldKarp<edgtype, edgvectype, edgresview, ty, tx> parm ;
#endif

// damn you preprocessor :^P
#if (4 >= SOLVE_TSP_from) && (4 <= SOLVE_TSP_to)
#define	caseHK4		caseHKy
#else
#define	caseHK4		caseHKn
#endif

#if (8 >= SOLVE_TSP_from) && (8 <= SOLVE_TSP_to)
#define	caseHK8		caseHKy
#else
#define	caseHK8		caseHKn
#endif

#if (16 >= SOLVE_TSP_from) && (16 <= SOLVE_TSP_to)
#define	caseHK16	caseHKy
#else
#define	caseHK16	caseHKn
#endif

#if (24 >= SOLVE_TSP_from) && (24 <= SOLVE_TSP_to)
#define	caseHK24	caseHKy
#else
#define	caseHK24	caseHKn
#endif

#if (32 >= SOLVE_TSP_from) && (32 <= SOLVE_TSP_to)
#define	caseHK32	caseHKy
#else
#define	caseHK32	caseHKn
#endif

#if (64 >= SOLVE_TSP_from) && (64 <= SOLVE_TSP_to)
#define	caseHK64	caseHKy
#else
#define	caseHK64	caseHKn
#endif

#if (80 >= SOLVE_TSP_from) && (80 <= SOLVE_TSP_to)
#define	caseHK80	caseHKy
#else
#define	caseHK80	caseHKn
#endif

#if (96 >= SOLVE_TSP_from) && (96 <= SOLVE_TSP_to)
#define	caseHK96	caseHKy
#else
#define	caseHK96	caseHKn
#endif

#if (128 >= SOLVE_TSP_from) && (128 <= SOLVE_TSP_to)
#define	caseHK128	caseHKy
#else
#define	caseHK128	caseHKn
#endif

#if (160 >= SOLVE_TSP_from) && (160 <= SOLVE_TSP_to)
#define	caseHK160	caseHKy
#else
#define	caseHK160	caseHKn
#endif

#if (192 >= SOLVE_TSP_from) && (192 <= SOLVE_TSP_to)
#define	caseHK192	caseHKy
#else
#define	caseHK192	caseHKn
#endif

#if (256 >= SOLVE_TSP_from) && (256 <= SOLVE_TSP_to)
#define	caseHK256	caseHKy
#else
#define	caseHK256	caseHKn
#endif

#if (320 >= SOLVE_TSP_from) && (320 <= SOLVE_TSP_to)
#define	caseHK320	caseHKy
#else
#define	caseHK320	caseHKn
#endif

#if (512 >= SOLVE_TSP_from) && (512 <= SOLVE_TSP_to)
#define	caseHK512	caseHKy
#else
#define	caseHK512	caseHKn
#endif

#if (1024 >= SOLVE_TSP_from) && (1024 <= SOLVE_TSP_to)
#define	caseHK1024	caseHKy
#else
#define	caseHK1024	caseHKn
#endif

#define	caseHK(txf, tx, ty, parm)	\
      caseHK ## tx (txf, tx, ty, parm)

#ifndef NDEBUG
#define	report(str, ...)	printf(str, __VA_ARGS__)
#endif // !NDEBUG

/* turned off for the moment */
#undef	report
#define	report(str, ...)	0

#endif // SOLVE_TSP_HPP
