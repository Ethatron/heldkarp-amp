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

#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <string.h>
#include <setjmp.h>
#include <stdlib.h>
#include <io.h>
#include <sys/stat.h>

#include "ParseTSP.h"
#include "SolveTSP.h"

/* inputs */
double lambda_reduction = 0.9;
double lambda_termination = 1e-06;
size_t memory_limit = -1;
int thread_limit = 0;

/* outputs */
vector< short > route;
size_t peak_memory = 0, curr_memory = 0, glob_memory = 0;
int num_iterations = 0;
critical_section mst;

int main(int argc, const char *argv[]) {
  const char *inname = NULL, *outname = NULL;
  struct stat check;
  TSPHardware hw = TSPH_CPU_REF;
  TSPPrimitive sp = TSPP_Auto;

  _umask(0777);

#if 0
  unsigned int control_word_x87;
  unsigned int control_word_sse;

  // guarantee round-nearest (which tie mode is used?) */
  if (__control87_2(0, 0, &control_word_x87, &control_word_sse)) {
    __control87_2(_RC_NEAR, _MCW_RC, &control_word_x87, &control_word_sse);
  }
#endif

  for (int c = 1; c < argc; c++) {
    /**/ if (!strcmp(argv[c], "-char"  ) || !strcmp(argv[c], "-c")) {
      sp = TSPP_Char;
    }
    else if (!strcmp(argv[c], "-short" ) || !strcmp(argv[c], "-s")) {
      sp = TSPP_Short;
    }
    else if (!strcmp(argv[c], "-long"  ) || !strcmp(argv[c], "-l")) {
      sp = TSPP_Long;
    }
    else if (!strcmp(argv[c], "-float" ) || !strcmp(argv[c], "-f")) {
      sp = TSPP_Float;
    }
    else if (!strcmp(argv[c], "-double") || !strcmp(argv[c], "-d")) {
      sp = TSPP_Double;
    }

#if	defined(SOLVE_TSP_with_CPU)
    else if (!strcmp(argv[c], "-cpu-ref")) {
      hw = TSPH_CPU_REF;
    }
#endif

#if	defined(SOLVE_TSP_with_SSE2)
    else if (!strcmp(argv[c], "-cpu-vpu")) {
      hw = TSPH_CPU_VPU;
    }
#endif

#if	defined(SOLVE_TSP_with_AMP)
    else if (!strcmp(argv[c], "-amp-ref")) {
      hw = TSPH_AMP_REF;
    }
    else if (!strcmp(argv[c], "-amp-warp")) {
      hw = TSPH_AMP_WRP;
    }
    else if (!strcmp(argv[c], "-amp-gpu")) {
      hw = TSPH_AMP_GPU;
    }
#endif

    else if (!strcmp(argv[c], "-parallel-devices")) {
      thread_limit = (int)atoi(argv[++c]);
    }
    else if (!strcmp(argv[c], "-memlimit")) {
      memory_limit = (size_t)atoi(argv[++c]) * 1024 * 1024;
    }
    else if (!strcmp(argv[c], "-lambda-reduction")) {
      lambda_reduction = (double)atof(argv[++c]);
    }
    else if (!strcmp(argv[c], "-lambda-termination")) {
      lambda_termination = (double)atof(argv[++c]);
    }
    else if (!inname ) {
      inname  = argv[c];
    }
    else if (!outname) {
      outname = argv[c];
    }
  }

  /* -------------------------------------------------------------------------------------------- */
  if (!inname /*|| !outname*/ || stat(inname, &check)) {
    fprintf(stderr,
      "Usage:\n"
      " SolveTSP\n"
      "  [-auto, -a]\n"
      "   try to find a fixed-point representation and solve with smallest integer\n"
      "   otherwise use floats\n"
      "  [-char, -c]\n"
      "   try to find a 8bit fixed-point representation and solve with char integers\n"
      "  [-short, -s]\n"
      "   try to find a 16bit fixed-point representation and solve with short integers\n"
      "  [-long, -l]\n"
      "   try to find a 32bit fixed-point representation and solve with long integers\n"
      "  [-float, -f]\n"
      "   use floats to solve\n"
      "  [-double, -d]\n"
      "   use doubles to solve\n"
      "\n"
#if	defined(SOLVE_TSP_with_CPU)
      "  [-cpu-ref]\n"
      "   use the CPU to solve\n"
#endif
#if	defined(SOLVE_TSP_with_SSE2)
      "  [-cpu-vpu]\n"
      "   use the vector units of the CPU to solve\n"
#endif
#if	defined(SOLVE_TSP_with_AMP)
      "  [-amp-ref]\n"
      "   use AMP's reference implementation to solve\n"
      "  [-amp-warp]\n"
      "   use AMP's fast software implementation to solve\n"
      "  [-amp-gpu]\n"
      "   use AMP's GPU accelerated implementation to solve\n"
#endif
      "  [-parallel-devices] <limit>\n"
      "   to compute on, equals cores for CPU, and cards for GPU, 0 is unlimited\n"
      "\n"
      "  [-memlimit] <MBytes>\n"
      "   to the amount of usable memory, start dropping paths afterwards\n"
      "  [-lambda-reduction] <float>\n"
      "   successive lambda reduction quantity (0,1), 0.9 is default (0.85 is quick)\n"
      "  [-lambda-termination] <float>\n"
      "   termination threshold for lambda reduction, 1e-06 is default\n"
      "\n"
      "  <srcfile>\n"
      "  <dstfile>\n");

    return -1;
  }

  char setname[256];
  TSPType settype;
  TSPFormat setformat;
  TSPDistance setmetric;
  int setentries;

#if	(_MSC_VER >= 1700)
  /* set default accelerator before anything else happens */
  if (hw == TSPH_AMP_REF) {
    if (0/*WAVEFRONT_SIZE > 4*/)
      ;
    else {
      accelerator direct3d_ref(accelerator::direct3d_ref);
      accelerator::set_default(direct3d_ref.device_path);
    }
  }
  else if (hw == TSPH_AMP_WRP) {
    if (0/*WAVEFRONT_SIZE > 4*/)
      ;
    else {
      accelerator direct3d_warp(accelerator::direct3d_warp);
      accelerator::set_default(direct3d_warp.device_path);
    }
  }

#if	defined(AMP_PROFILE)
  ProfileStart(hw, "test.csv");
#endif
#endif

  /* read and process */
  if (ReadTSP(inname, setname, settype, setformat, setmetric, setentries)) {
//    try {
      dump_tspname = outname;
      dump_name = setname;
      dump_type = settype;
      dump_frmt = setformat;
      dump_dist = setmetric;
      dump_dimension = setentries;

    /**/ if (setmetric == TSPD_Euclidian3D) {
      fprintf(stderr, "no support for 3D data yet\n");
    }
    else if (settype == TSPT_Unknown) {
      fprintf(stderr, "no support for unknown TSP\n");
    }
    else if (settype == TSPT_Asymmetric) {
      fprintf(stderr, "no support for asymmetric TSP yet\n");
    }
    else if (settype == TSPT_Symmetric) {
      if (sp == TSPP_Double) {
	SolveTSP(TSPDoubles, route, hw, setformat, setmetric);
      }
      else if (MinimizeTSP(inname, setname, settype, setformat, setmetric, setentries)) {
	if (sp == TSPP_Auto) {
	  /**/ if (TSPCharBase)
	    sp = TSPP_Char;
	  else if (TSPShortBase)
	    sp = TSPP_Short;
	  else if (TSPLongBase)
	    sp = TSPP_Long;
	  else if (TSPFloatBase)
	    sp = TSPP_Float;
	  else
	    sp = TSPP_Double;
	}

	if (setmetric == TSPD_Geographic2D)
	  fprintf(stderr, "no perfect support for geographic distances yet\n");

	/**/ if (hw == TSPH_CPU_REF)
	  fprintf(stderr, "using regular (OoO) CPU for solve\n");
	else if (hw == TSPH_CPU_VPU)
	  fprintf(stderr, "using SSE2 vector-units for solve\n");
	else if (hw == TSPH_AMP_REF)
	  fprintf(stderr, "using reference AMP for solve\n");
	else if (hw == TSPH_AMP_WRP)
	  fprintf(stderr, "using fast software AMP for solve\n");
	else if (hw == TSPH_AMP_GPU)
	  fprintf(stderr, "using GPU accelerated AMP for solve\n");

	/**/ if (sp == TSPP_Char) {
	  if (TSPCharBase) {
	    fprintf(stderr, "using chars for solve\n");
	    SolveTSP(TSPChars, route, hw, setformat, setmetric);
	  }
	  else
	    fprintf(stderr, "data doesn't fit into a char\n");
	}
	else if (sp == TSPP_Short) {
	  if (TSPShortBase) {
	    fprintf(stderr, "using shorts for solve\n");
	    SolveTSP(TSPShorts, route, hw, setformat, setmetric);
	  }
	  else
	    fprintf(stderr, "data doesn't fit into a short\n");
	}
	else if (sp == TSPP_Long) {
	  if (TSPLongBase) {
	    fprintf(stderr, "using longs for solve\n");
	    SolveTSP(TSPLongs, route, hw, setformat, setmetric);
	  }
	  else
	    fprintf(stderr, "data doesn't fit into a long\n");
	}
	else if (sp == TSPP_Float) {
	  if (TSPFloatBase) {
	    fprintf(stderr, "using floats for solve\n");
	    SolveTSP(TSPFloats, route, hw, setformat, setmetric);
	  }
	  else
	    fprintf(stderr, "data doesn't fit into a float\n");
	}
	else {
	  if (1) {
	    fprintf(stderr, "using doubles for solve\n");
	    SolveTSP(TSPDoubles, route, hw, setformat, setmetric);
	  }
	  else
	    fprintf(stderr, "data doesn't fit into a double\n");
	}
      }

      if (!route.size())
        fprintf(stderr, "failed to calculate solution!\n");
      else if (route.size() < (size_t)setentries)
        fprintf(stderr, "calculated solution couldn't connect all locations\n");
      else if (route.size() > (size_t)setentries)
        fprintf(stderr, "calculated solution connected some locations multiple times\n");
      else {
	/* symmetric TSP: !(n-1) / 2 */
	fprintf(stderr, "peak memory: %d bytes                                             \n", peak_memory);
	fprintf(stderr, "static memory: %d bytes                                           \n", glob_memory);
	fprintf(stderr, "number of iterations: %d (of %g)\n", num_iterations, faculty(route.size() - 1) / 2);

	PrintTSP(outname, setname, settype, setformat, setmetric, setentries, route);
      }
    }
    else {
      fprintf(stderr, "unsupported solution-type requested\n");
    }

#if 0
    } catch (exception e) {
      fprintf(stderr, "caught an exception:\n%s\n", e.what());
    }
#endif
  }
  else {
    fprintf(stderr, "can't parse the given data-file\n");
  }

#if	(_MSC_VER >= 1700) && defined(AMP_PROFILE)
  ProfileExit();
#endif

  return 0;
}
