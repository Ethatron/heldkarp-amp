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

#include "SolveTSP.h"

#if	defined(SOLVE_TSP_with_AMP_CMP_and_Crossfire)
#include "implementations/AMP-CMP-OptCFX.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CMP_OptMax)
#include "implementations/AMP-CMP-OptMax.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CMP_Opt)
#include "implementations/AMP-CMP-Opt.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CMP)
#include "implementations/AMP-CMP.cpp"

#elif	defined(SOLVE_TSP_with_AMP_CM_and_Crossfire)
#include "implementations/AMP-CM-OptCFX.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CM_OptMax)
#include "implementations/AMP-CM-OptMax.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CM_Opt)
#include "implementations/AMP-CM-Opt.cpp"
#elif	defined(SOLVE_TSP_with_AMP_CM)
#include "implementations/AMP-CM.cpp"

#elif	defined(SOLVE_TSP_with_AMP)
#include "implementations/AMP.cpp"
#endif

#if	defined(SOLVE_TSP_with_SSE2_and_CR_CM)
#include "implementations/SSE2-ConcRT-CM.cpp"
#elif	defined(SOLVE_TSP_with_SSE2_and_CR)
#include "implementations/SSE2-ConcRT.cpp"
#elif	defined(SOLVE_TSP_with_SSE2)
#include "implementations/SSE2.cpp"
#endif

#if	defined(SOLVE_TSP_with_CPU)
#include "implementations/CPU.cpp"
#endif

/* ------------------------------------------------------------------------
 * receive data-set and built edge-lists
 */

void SolveTSP(const vector< pair<char, char> > &dataset, vector< short > &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist) {
  const int SIMDsize = hwSIMDsize(hw);

  /* calculate number of edges */
  size_t numnodes = (frmt == TSPF_List ? dataset.size() : (size_t)sqrt((double)dataset.size()));
  size_t edgestride = (numnodes + (SIMDsize - 1)) & (~(SIMDsize - 1));
  size_t numedges = numnodes * edgestride;
  vector< uchar > edges(numedges);

  route.resize(numnodes);
  edges.assign(numedges, 0);

  /* build edges */
  for (size_t nodei = 0; (nodei + 1) < numnodes; nodei++) {
    for (size_t nodej = (nodei + 1); nodej < numnodes; nodej++) {
      uchar edistance;

      if (frmt == TSPF_List) {
	short data1x = dataset[nodei].first;
	short data1y = dataset[nodei].second;
	short data2x = dataset[nodej].first;
	short data2y = dataset[nodej].second;

	/* geographic distance (approx. fit) */
	if (dist == TSPD_Geographic2D)
	  edistance = Geographic<short, uchar, char>(data1x, data1y, data2x, data2y, TSPCharBase);
	/* euclidean distance (perfect fit) */
	else if (dist == TSPD_Pseudo2D)
	  edistance = Pseudo<short, uchar, char>(data1x, data1y, data2x, data2y, TSPCharBase);
	else if (dist == TSPD_Ceil2D)
	  edistance = Ceil<short, uchar, char>(data1x, data1y, data2x, data2y, TSPCharBase);
	else
	  edistance = Euclidean<short, uchar, char>(data1x, data1y, data2x, data2y, TSPCharBase);
      }
      else
	edistance = (uchar)dataset[nodei * numnodes + nodej].first;

      size_t i = nodei;
      size_t j = nodej;

      edges[(i * edgestride) + j] = edistance;
      edges[(j * edgestride) + i] = edistance;

//    printf("edge[%d][%d] %f\n", y, x, edges[(i * edgestride) + j]);
//    printf("edge[%d][%d] %f\n", x, y, edges[(j * edgestride) + i]);
    }
  }

  SolveTSP(edges, route, hw);
}

void SolveTSP(const vector< pair<short, short> > &dataset, vector< short > &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist) {
  const int SIMDsize = hwSIMDsize(hw);

  /* calculate number of edges */
  size_t numnodes = (frmt == TSPF_List ? dataset.size() : (size_t)sqrt((double)dataset.size()));
  size_t edgestride = (numnodes + (SIMDsize - 1)) & (~(SIMDsize - 1));
  size_t numedges = numnodes * edgestride;
  vector< ushort > edges(numedges);

  route.resize(numnodes);
  edges.assign(numedges, 0);

  /* build edges */
  for (size_t nodei = 0; (nodei + 1) < numnodes; nodei++) {
    for (size_t nodej = (nodei + 1); nodej < numnodes; nodej++) {
      ushort edistance;

      if (frmt == TSPF_List) {
	long data1x = dataset[nodei].first;
	long data1y = dataset[nodei].second;
	long data2x = dataset[nodej].first;
	long data2y = dataset[nodej].second;

	/* geographic distance (approx. fit) */
	if (dist == TSPD_Geographic2D)
	  edistance = Geographic<long, ushort, short>(data1x, data1y, data2x, data2y, TSPShortBase);
	/* euclidean distance (perfect fit) */
	else if (dist == TSPD_Pseudo2D)
	  edistance = Pseudo<long, ushort, short>(data1x, data1y, data2x, data2y, TSPShortBase);
	else if (dist == TSPD_Ceil2D)
	  edistance = Ceil<long, ushort, short>(data1x, data1y, data2x, data2y, TSPShortBase);
	else
	  edistance = Euclidean<long, ushort, short>(data1x, data1y, data2x, data2y, TSPShortBase);
      }
      else
	edistance = (ushort)dataset[nodei * numnodes + nodej].first;

      size_t i = nodei;
      size_t j = nodej;

      edges[(i * edgestride) + j] = edistance;
      edges[(j * edgestride) + i] = edistance;

//    printf("edge[%d][%d] %f\n", y, x, edges[(i * edgestride) + j]);
//    printf("edge[%d][%d] %f\n", x, y, edges[(j * edgestride) + i]);
    }
  }

  SolveTSP(edges, route, hw);
}

void SolveTSP(const vector< pair<long , long> > &dataset, vector< short > &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist) {
  const int SIMDsize = hwSIMDsize(hw);

  /* calculate number of edges */
  size_t numnodes = (frmt == TSPF_List ? dataset.size() : (size_t)sqrt((double)dataset.size()));
  size_t edgestride = (numnodes + (SIMDsize - 1)) & (~(SIMDsize - 1));
  size_t numedges = numnodes * edgestride;
  vector< ulong > edges(numedges);

  route.resize(numnodes);
  edges.assign(numedges, 0);

  /* build edges */
  for (size_t nodei = 0; (nodei + 1) < numnodes; nodei++) {
    for (size_t nodej = (nodei + 1); nodej < numnodes; nodej++) {
      ulong edistance;

      if (frmt == TSPF_List) {
	long long data1x = dataset[nodei].first;
	long long data1y = dataset[nodei].second;
	long long data2x = dataset[nodej].first;
	long long data2y = dataset[nodej].second;

	/* geographic distance (approx. fit) */
	if (dist == TSPD_Geographic2D)
	  edistance = Geographic<long long, ulong, long>(data1x, data1y, data2x, data2y, TSPLongBase);
	/* euclidean distance (perfect fit) */
	else if (dist == TSPD_Pseudo2D)
	  edistance = Pseudo<long long, ulong, long>(data1x, data1y, data2x, data2y, TSPLongBase);
	else if (dist == TSPD_Ceil2D)
	  edistance = Ceil<long long, ulong, long>(data1x, data1y, data2x, data2y, TSPLongBase);
	else
	  edistance = Euclidean<long long, ulong, long>(data1x, data1y, data2x, data2y, TSPLongBase);
      }
      else
	edistance = (ulong)dataset[nodei * numnodes + nodej].first;

      size_t i = nodei;
      size_t j = nodej;

      edges[(i * edgestride) + j] = edistance;
      edges[(j * edgestride) + i] = edistance;

//    printf("edge[%d][%d] %f\n", y, x, edges[(i * edgestride) + j]);
//    printf("edge[%d][%d] %f\n", x, y, edges[(j * edgestride) + i]);
    }
  }

  SolveTSP(edges, route, hw);
}

void SolveTSP(const vector< pair<float, float> > &dataset, vector< short > &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist) {
  const int SIMDsize = hwSIMDsize(hw);

  /* calculate number of edges */
  size_t numnodes = (frmt == TSPF_List ? dataset.size() : (size_t)sqrt((double)dataset.size()));
  size_t edgestride = (numnodes + (SIMDsize - 1)) & (~(SIMDsize - 1));
  size_t numedges = numnodes * edgestride;
  vector< float > edges(numedges);

  route.resize(numnodes);
  edges.assign(numedges, 0);

  /* build edges */
  for (size_t nodei = 0; (nodei + 1) < numnodes; nodei++) {
    for (size_t nodej = (nodei + 1); nodej < numnodes; nodej++) {
      float edistance;

      if (frmt == TSPF_List) {
	double data1x = dataset[nodei].first;
	double data1y = dataset[nodei].second;
	double data2x = dataset[nodej].first;
	double data2y = dataset[nodej].second;

	/* geographic distance (approx. fit) */
	if (dist == TSPD_Geographic2D)
	  edistance = Geographic<double, float, float>(data1x, data1y, data2x, data2y, 1.0f);
	/* euclidean distance (perfect fit) */
	else if (dist == TSPD_Pseudo2D)
	  edistance = Pseudo<double, float, float>(data1x, data1y, data2x, data2y, 1.0f);
	else if (dist == TSPD_Ceil2D)
	  edistance = Ceil<double, float, float>(data1x, data1y, data2x, data2y, 1.0f);
	else
	  edistance = Euclidean<double, float, float>(data1x, data1y, data2x, data2y, 1.0f);
      }
      else
	edistance = (float)dataset[nodei * numnodes + nodej].first;

      size_t i = nodei;
      size_t j = nodej;

      edges[(i * edgestride) + j] = edistance;
      edges[(j * edgestride) + i] = edistance;

//    printf("edge[%d][%d] %f\n", y, x, edges[(i * edgestride) + j]);
//    printf("edge[%d][%d] %f\n", x, y, edges[(j * edgestride) + i]);
    }
  }

  SolveTSP(edges, route, hw);
}

void SolveTSP(const vector< pair<double, double> > &dataset, vector< short > &route, enum TSPHardware hw, enum TSPFormat frmt, enum TSPDistance dist) {
  const int SIMDsize = hwSIMDsize(hw);

  /* calculate number of edges */
  size_t numnodes = (frmt == TSPF_List ? dataset.size() : (size_t)sqrt((double)dataset.size()));
  size_t edgestride = (numnodes + (SIMDsize - 1)) & (~(SIMDsize - 1));
  size_t numedges = numnodes * edgestride;
  vector< double > edges(numedges);

  route.resize(numnodes);
  edges.assign(numedges, 0);

  /* build edges */
  for (size_t nodei = 0; (nodei + 1) < numnodes; nodei++) {
    for (size_t nodej = (nodei + 1); nodej < numnodes; nodej++) {
      double edistance;

      if (frmt == TSPF_List) {
	double data1x = dataset[nodei].first;
	double data1y = dataset[nodei].second;
	double data2x = dataset[nodej].first;
	double data2y = dataset[nodej].second;

	/* geographic distance (approx. fit) */
	if (dist == TSPD_Geographic2D)
	  edistance = Geographic<double, double, double>(data1x, data1y, data2x, data2y, 1.0);
	/* euclidean distance (perfect fit) */
	else if (dist == TSPD_Pseudo2D)
	  edistance = Pseudo<double, double, double>(data1x, data1y, data2x, data2y, 1.0);
	else if (dist == TSPD_Ceil2D)
	  edistance = Ceil<double, double, double>(data1x, data1y, data2x, data2y, 1.0);
	else
	  edistance = Euclidean<double, double, double>(data1x, data1y, data2x, data2y, 1.0);
      }
      else
	edistance = (double)dataset[nodei * numnodes + nodej].first;

      size_t i = nodei;
      size_t j = nodej;

      edges[(i * edgestride) + j] = edistance;
      edges[(j * edgestride) + i] = edistance;

//    printf("edge[%d][%d] %f\n", y, x, edges[(i * edgestride) + j]);
//    printf("edge[%d][%d] %f\n", x, y, edges[(j * edgestride) + i]);
    }
  }

  SolveTSP(edges, route, hw);
}