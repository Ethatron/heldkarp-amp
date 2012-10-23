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

#ifndef	PARSE_TSP_HPP
#define	PARSE_TSP_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <float.h>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

enum TSPPrimitive {
  TSPP_Auto,		// solve as integers or floating-points
  TSPP_Char,		// solve as byte integers (find base first)
  TSPP_Short,		// solve as short integers (find base first)
  TSPP_Long,		// solve as long integers (find base first)
  TSPP_Float,		// solve as floats
  TSPP_Double		// solve as floats
};

enum TSPType {
  TSPT_Symmetric,	// Symmetric TSP
  TSPT_Asymmetric,	// Asymmetric TSP
  TSPT_Unknown		// Unknown
};

enum TSPDistance {
  TSPD_Geographic2D,	// 2D on sphere surface, int or float
  TSPD_Pseudo2D,	// 2D on ?, int or float
  TSPD_Euclidian2D,	// 2D on plane, int or float
  TSPD_Euclidian3D,	// 3D in volume, int or float
  TSPD_Ceil2D,		// 2D on plane, int or float
  TSPD_Explicit2D,	// 2D on plane, int or float
  TSPD_Unknown		// Unknown
};

enum TSPFormat {
  TSPF_FullMatrix,
  TSPF_UpperRow,
  TSPF_LowerRow,
  TSPF_UpperDiagRow,
  TSPF_LowerDiagRow,
  TSPF_UpperCol,
  TSPF_LowerCol,
  TSPF_UpperDiagCol,
  TSPF_LowerDiagCol,
  TSPF_List		// Regular
};

typedef	unsigned char	uchar;
typedef	unsigned short	ushort;
typedef	unsigned long	ulong;

extern char   TSPCharBase;
extern short  TSPShortBase;
extern long   TSPLongBase;
extern float  TSPFloatBase;

extern vector< pair<char  , char  > > TSPChars;
extern vector< pair<short , short > > TSPShorts;
extern vector< pair<long  , long  > > TSPLongs;
extern vector< pair<float , float > > TSPFloats;
extern vector< pair<double, double> > TSPDoubles;

bool HeadTSP(const char *tspname, char *name, enum TSPType &type, enum TSPDistance &dist, int &dimension);
bool ReadTSP(const char *tspname, char *name, enum TSPType &type, enum TSPFormat &frmt, enum TSPDistance &dist, int &dimension);
bool MinimizeTSP(const char *tspname, char *name, enum TSPType &type, enum TSPFormat &frmt, enum TSPDistance &dist, int &dimension);
bool PrintTSP(const char *tspname, char *name, enum TSPType &type, enum TSPFormat &frmt, enum TSPDistance &dist, int &dimension, vector< short > &route);

#define	DUMP_BEST_ALWAYS

/* allow dumping mid-calc */
extern const char *dump_tspname;
extern char *dump_name;
extern enum TSPType dump_type;
extern enum TSPFormat dump_frmt;
extern enum TSPDistance dump_dist;
extern int dump_dimension;

void DumpTSP(vector< short > &route);

#endif // PARSE_TSP_HPP
