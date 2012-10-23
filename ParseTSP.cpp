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

#include "ParseTSP.h"
#include "helpers/Distances.h"

#include <set>

char  TSPCharBase;
short TSPShortBase;
long  TSPLongBase;
float TSPFloatBase;

vector< pair<char  , char  > > TSPChars;
vector< pair<short , short > > TSPShorts;
vector< pair<long  , long  > > TSPLongs;
vector< pair<float , float > > TSPFloats;
vector< pair<double, double> > TSPDoubles;

static void parseword(FILE *in, char *cbuf) {
  char c;
  while (1) {
    do
    c = fgetc(in);
    while (c == ':' || c == ' ' || c == '\t' || c == '\n' || c == '\r');
    if (c == '#') {
      do
      c = fgetc(in);
      while (c != '\n');
    }
    else
      break;
  }
  *cbuf++ = c;
  c = fgetc(in);
  while (c != ':' && c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '#') {
    *cbuf++ = c;
    c = fgetc(in);
  }
  fseek(in, -1, SEEK_CUR);
  *cbuf = '\0';
}

static void parsecomment(FILE *in, char *cbuf) {
  char c;
  while (1) {
    do
    c = fgetc(in);
    while (c == ':' || c == ' ' || c == '\t' || c == '\n' || c == '\r');
    if (c == '#') {
      do
      c = fgetc(in);
      while (c != '\n');
    }
    else
      break;
  }
  *cbuf++ = c;
  c = fgetc(in);
  while (c != '\t' && c != '\n' && c != '\r') {
    *cbuf++ = c;
    c = fgetc(in);
  }
  fseek(in, -1, SEEK_CUR);
  *cbuf = '\0';
}

bool HeadTSP(const char *tspname, char *name, enum TSPType &type, enum TSPDistance &dist, int &dimension) {
  char cbuf[256];
  bool valid = false;

  type = TSPT_Unknown;
  dist = TSPD_Unknown;
  dimension = 0;

  FILE *in = fopen(tspname, "rb");
  if (!in)
    return valid;

  do {
    parseword(in, cbuf);

    if (!_stricmp("NAME", cbuf)) {
      parseword(in, name);
      continue;
    }

    if (!_stricmp("COMMENT", cbuf)) {
      parsecomment(in, cbuf);
      continue;
    }

    if (!_stricmp("TYPE", cbuf)) {
      parseword(in, cbuf);

      if (!_stricmp("TSP", cbuf))
	type = TSPT_Symmetric;
      else if (!_stricmp("ATSP", cbuf))
	type = TSPT_Asymmetric;

      continue;
    }

    if (!_stricmp("DIMENSION", cbuf)) {
      parseword(in, cbuf);
      dimension = atoi(cbuf);
      continue;
    }

    if (!_stricmp("EDGE_WEIGHT_TYPE", cbuf)) {
      parseword(in, cbuf);

      if (!_stricmp("GEO", cbuf))
	dist = TSPD_Geographic2D;
      else if (!_stricmp("EUC_2D", cbuf))
	dist = TSPD_Euclidian2D;
      else if (!_stricmp("EUC_3D", cbuf))
	dist = TSPD_Euclidian3D;
      else if (!_stricmp("CEIL_2D", cbuf))
	dist = TSPD_Ceil2D;

      continue;
    }

    if (!_stricmp("DISPLAY_DATA_TYPE", cbuf)) {
      parseword(in, cbuf);
      continue;
    }

    if (!_stricmp("NODE_COORD_SECTION", cbuf)) {
      valid = true;
      break;
    }

    valid = false;
    break;
  } while(0);

  fclose(in);
  return valid;
}

bool ReadTSP(const char *tspname, char *name, enum TSPType &type, enum TSPFormat &frmt, enum TSPDistance &dist, int &dimension) {
  char cbuf[256];
  bool valid = false;

  type = TSPT_Unknown;
  frmt = TSPF_List;
  dist = TSPD_Unknown;
  dimension = 0;

  FILE *in = fopen(tspname, "rb");
  if (!in)
    return valid;

  do {
    parseword(in, cbuf);

    if (!_stricmp("NAME", cbuf)) {
      parseword(in, name);
      fprintf(stderr, "data-set: %s\n", name);
      continue;
    }

    if (!_stricmp("COMMENT", cbuf)) {
      parsecomment(in, cbuf);
      fprintf(stderr, "comment: %s\n", cbuf);
      continue;
    }

    if (!_stricmp("TYPE", cbuf)) {
      parseword(in, cbuf);

      if (!_stricmp("TSP", cbuf))
	type = TSPT_Symmetric;
      else if (!_stricmp("ATSP", cbuf))
	type = TSPT_Asymmetric;

      fprintf(stderr, "type: %s\n", cbuf);
      continue;
    }

    if (!_stricmp("DIMENSION", cbuf)) {
      parseword(in, cbuf);
      dimension = atoi(cbuf);
      fprintf(stderr, "dimension: %d\n", dimension);
      continue;
    }

    if (!_stricmp("EDGE_WEIGHT_TYPE", cbuf)) {
      parseword(in, cbuf);

      if (!_stricmp("GEO", cbuf))
	dist = TSPD_Geographic2D;
      else if (!_stricmp("ATT", cbuf))
	dist = TSPD_Pseudo2D;
      else if (!_stricmp("EUC_2D", cbuf))
	dist = TSPD_Euclidian2D;
      else if (!_stricmp("EUC_3D", cbuf))
	dist = TSPD_Euclidian3D;
      else if (!_stricmp("CEIL_2D", cbuf))
	dist = TSPD_Ceil2D;
      else if (!_stricmp("EXPLICIT", cbuf))
	dist = TSPD_Explicit2D;

      continue;
    }

    if (!_stricmp("EDGE_WEIGHT_FORMAT", cbuf)) {
      parseword(in, cbuf);

      if (!_stricmp("FULL_MATRIX", cbuf))
	frmt = TSPF_FullMatrix;
      else if (!_stricmp("UPPER_ROW", cbuf))
	frmt = TSPF_UpperRow;
      else if (!_stricmp("LOWER_ROW", cbuf))
	frmt = TSPF_LowerRow;
      else if (!_stricmp("UPPER_DIAG_ROW", cbuf))
	frmt = TSPF_UpperDiagRow;
      else if (!_stricmp("LOWER_DIAG_ROW", cbuf))
	frmt = TSPF_LowerDiagRow;
      else if (!_stricmp("UPPER_COL", cbuf))
	frmt = TSPF_UpperCol;
      else if (!_stricmp("LOWER_COL", cbuf))
	frmt = TSPF_LowerCol;
      else if (!_stricmp("UPPER_DIAG_COL", cbuf))
	frmt = TSPF_UpperDiagCol;
      else if (!_stricmp("LOWER_DIAG_COL", cbuf))
	frmt = TSPF_LowerDiagCol;

      continue;
    }

    if (!_stricmp("DISPLAY_DATA_TYPE", cbuf)) {
      parseword(in, cbuf);
      continue;
    }

    if ((!_stricmp("NODE_COORD_SECTION", cbuf) && (frmt == TSPF_List)) ||
        (!_stricmp("EDGE_WEIGHT_SECTION", cbuf) && (frmt != TSPF_List))) {
      valid = true;
      break;
    }

    /* can be parsed as well like "NODE_COORD_SECTION" */
    if (!_stricmp("DISPLAY_DATA_SECTION", cbuf)) {
      valid = true;
      break;
    }

    fprintf(stdout, "unknown attribute: %s\n", cbuf);
    valid = false;
    break;
  } while(1);

  TSPDoubles.clear();
  if (valid) {
    switch (dist) {
      case TSPD_Geographic2D:
	fprintf(stderr, "distances: 2D geographic\n");
	break;
      case TSPD_Pseudo2D:
	fprintf(stderr, "distances: 2D pseudo-euclidean\n");
	break;
      case TSPD_Euclidian2D:
	fprintf(stderr, "distances: 2D euclidean\n");
	break;
      case TSPD_Euclidian3D:
	fprintf(stderr, "distances: 3D euclidean\n");
	fprintf(stderr, "unsupported data-rank of > 2, sorry\n");
	valid = false;
	break;
      case TSPD_Ceil2D:
	fprintf(stderr, "distances: 2D euclidean ceiled\n");
	break;
      case TSPD_Explicit2D:
	fprintf(stderr, "distances: 2D custom\n");
	break;
    }

    int incl = 1;
    switch (frmt) {
      case TSPF_FullMatrix:
	TSPDoubles.resize(dimension * dimension);
	for (int d = 0; d < dimension * dimension; d++) {
	  parseword(in, cbuf);
	  double xy = atof(cbuf);

	  TSPDoubles[d] = pair<double, double>(xy, -1.0);
	}

	fprintf(stderr, "read matrix entries: %d\n", TSPDoubles.size());
	break;

      case TSPF_UpperDiagRow:
	incl = 0;
      case TSPF_UpperRow:
	TSPDoubles.resize(dimension * dimension);
	TSPDoubles.assign(dimension * dimension, pair<double, double>(0.0, 0.0));
	for (int d = 0; d < (dimension - incl); d++) {
	  for (int e = d + incl; e < dimension; e++) {
	    parseword(in, cbuf);
	    double xy = atof(cbuf);

	    TSPDoubles[d * dimension + e] = pair<double, double>(xy, xy);
	    TSPDoubles[e * dimension + d] = pair<double, double>(xy, xy);
	  }
	}

	fprintf(stderr, "read upper entries: %d\n", (TSPDoubles.size() - (dimension)) / 2 + ((1 - incl) * dimension));
	break;

      case TSPF_LowerDiagRow:
	incl = 0;
      case TSPF_LowerRow:
	TSPDoubles.resize(dimension * dimension);
	TSPDoubles.assign(dimension * dimension, pair<double, double>(0.0, 0.0));
	for (int d = incl; d < dimension; d++) {
	  for (int e = 0; e < (d + 1); e++) {
	    parseword(in, cbuf);
	    double xy = atof(cbuf);

	    TSPDoubles[d * dimension + e] = pair<double, double>(xy, xy);
	    TSPDoubles[e * dimension + d] = pair<double, double>(xy, xy);
	  }
	}

	fprintf(stderr, "read lower entries: %d\n", (TSPDoubles.size() - (dimension)) / 2 + ((1 - incl) * dimension));
	break;

      case TSPF_UpperCol:
      case TSPF_LowerCol:
      case TSPF_UpperDiagCol:
      case TSPF_LowerDiagCol:
	fprintf(stderr, "unsupported data-arrangement, sorry\n");
	valid = false;
	break;

      default:
	TSPDoubles.resize(dimension);
	for (int d = 0; d < dimension; d++) {
	  parseword(in, cbuf);
	  int pos = atoi(cbuf);

	  parseword(in, cbuf);
	  double x = atof(cbuf);

	  parseword(in, cbuf);
	  double y = atof(cbuf);

	  /* even though order doesn't matter, we insert in-order */
	  if ((pos >= 1) && (pos <= dimension))
	    TSPDoubles[pos - 1] = pair<double, double>(x, y);
	}

	fprintf(stderr, "read pairs: %d\n", TSPDoubles.size());
	break;
    }
  }

  fclose(in);
  return valid;
}

bool MinimizeTSP(const char *tspname, char *name, enum TSPType &type, enum TSPFormat &frmt, enum TSPDistance &dist, int &dimension) {
  const size_t setsize = TSPDoubles.size();

  TSPCharBase  = 0;
  TSPShortBase = 0;
  TSPLongBase  = 0;
  TSPFloatBase = 0;

  TSPChars.clear();
  TSPShorts.clear();
  TSPLongs.clear();
  TSPFloats.clear();
  if (setsize > 0) {
    TSPChars.resize(setsize);
    TSPShorts.resize(setsize);
    TSPLongs.resize(setsize);
    TSPFloats.resize(setsize);

    fprintf(stderr, "datatype minimization:\n");

    bool flt_valid = true;
    bool gdc_valid = true;
    set<int> gdc_set;

    /* get all smallest divisors multiple-of-2 (2^e*m) */
    for (size_t d = 0; d < setsize; d++) {
      double x = TSPDoubles[d].first;
      double y = TSPDoubles[d].second;

      double ix = floor(x) - (x < 0 ? -1 : 0);
      double iy = floor(y) - (y < 0 ? -1 : 0);

      ix = x - ix;
      iy = y - iy;
      if (!ix)
	ix = 1.0f;
      if (!iy)
	iy = 1.0f;

      {
	double magx = floor(x) - (double)floorf((float)x);
	double magy = floor(y) - (double)floorf((float)y);
	double diffx = fabs((double)((float)ix) - (ix));
	double diffy = fabs((double)((float)iy) - (iy));

	/* natural number preserved, ulps below 1 */
	flt_valid = flt_valid && (magx == 0) && (diffx <= 3.0e-008);
	flt_valid = flt_valid && (magy == 0) && (diffy <= 3.0e-008);
      }

      {
	int iix;
	int iiy;

	/* search base-2 divider below mantissa size (2^23) */
	int log2x = 1;
	for (log2x = 1; log2x < 23; log2x++) {
	  iix = (int)(1.0 * log2x / ix);
	  double cix = (1.0 * log2x / iix);
	  if (cix == ix)
	    break;
	}

	/* search base-2 divider below mantissa size (2^23) */
	int log2y = 1;
	for (log2y = 1; log2y < 23; log2y++) {
	  iiy = (int)(1.0 * log2y / iy);
	  double ciy = (1.0 * log2y / iiy);
	  if (ciy == iy)
	    break;
	}

	/* register base-2 dividers */
	if ((log2x < 23) && (log2y < 23)) {
	  gdc_set.insert(abs(iix));
	  gdc_set.insert(abs(iiy));
	}
	else {
	  gdc_valid = false;
	}
      }
    }

    if (gdc_valid)
      fprintf(stderr, " %d different lcm found\n", gdc_set.size());
    else
      fprintf(stderr, " rational number found, no lcm available\n");

    /* floating-point set fits into floats */
    if (flt_valid || gdc_valid)
      fprintf(stderr, " check fit:\n");

    /* check if we can use floats */
    if (flt_valid) {
      /* range search */
      double
	lwr =  DBL_MAX,
	upr = -DBL_MAX,
	dst = -DBL_MAX;

      /* determine ranges of floats */
      for (size_t d = 0; d < setsize; d++) {
	pair<double, double> &tf = TSPDoubles[d];

	upr = (upr < tf.first  ? tf.first  : upr);
	upr = (upr < tf.second ? tf.second : upr);

	lwr = (lwr > tf.first  ? tf.first  : lwr);
	lwr = (lwr > tf.second ? tf.second : lwr);

	/* weak check, just look at all distances from [0,0] for the datatype fit */
	if ((frmt == TSPF_List) && (dist == TSPD_Geographic2D)) {
	  double geo = Geographic<double, double, double>(tf.first, tf.second, 0.0, 0.0, 1.0);

	  dst = (dst < geo ? geo : dst);
	}
      }

      /* distance adjustments */
      if (frmt == TSPF_List) {
	if (dist == TSPD_Pseudo2D)
	  dst = Pseudo<double, double, double>(upr, upr, lwr, lwr, 1.0);
	else if (dist == TSPD_Ceil2D)
	  dst = Ceil<double, double, double>(upr, upr, lwr, lwr, 1.0);
	else if (dist != TSPD_Geographic2D)
	  dst = Euclidean<double, double, double>(upr, upr, lwr, lwr, 1.0);
      }
      else {
	dst = floor(upr + 0.5);
      }

      /* relaxed case: we don't check if all combination's distances
       * fit into the float, though we may loose a few bits here
       */
      if ((double)((float)dst) == (dst)) {
	TSPFloatBase = (float)dst;

	for (size_t d = 0; d < setsize; d++) {
	  pair<double, double> &tf = TSPDoubles[d];

	  TSPFloats[d] = pair<float, float>(
	    (float)(tf.first ),
	    (float)(tf.second)
	  );
	}

	fprintf(stderr, " - float [%g,%g] -> %g\n", lwr, upr, dst);
      }
    }

    /* calculate the lowest common multiple necessary to make all numbers integers */
    if (gdc_valid) {
      set<int>::iterator gdc_i;
      int gdc = 0;

      gdc_i = gdc_set.begin();
      gdc = *gdc_i;

      /* lowest common multiple search */
      int lcm = gdc;
      for (gdc_i++; gdc_i != gdc_set.end(); gdc_i++) {
	int a = gdc, b = (*gdc_i), c;

	while (1) {
	  a = a % b;
	  if (a == 0) {
	    c = b;
	    break;
	  }

	  b = b % a;
	  if (b == 0) {
	    c = a;
	    break;
	  }
	}

	gdc = c;
	lcm = (gdc * (*gdc_i)) / gdc;
      }

//    fprintf(stdout, "determined lcm: %d\n", lcm);

      /* range search */
      long long
	min = 0x7FFFFFFFFFFFFFFFLL,
	max = 0x8000000000000000LL,
	dst = 0x7FFFFFFFFFFFFFFFLL;

      /* determine ranges of integers */
      for (size_t d = 0; d < setsize; d++) {
	pair<double, double> &tf = TSPDoubles[d];

	long long f = (long long)(tf.first  * lcm);
	long long s = (long long)(tf.second * lcm);

	max = (max < f ? f : max);
	max = (max < s ? s : max);

	min = (min > f ? f : min);
	min = (min > s ? s : min);

	/* weak check, just look at all distances from [0,0] for the datatype fit */
	if ((frmt == TSPF_List) && (dist == TSPD_Geographic2D)) {
	  long long geo = Geographic<long long, long long, double>(f, s, 0, 0, 1.0);

	  dst = (dst < geo ? geo : dst);
	}
      }

      /* integer distance adjustments */
      if (frmt == TSPF_List) {
	if (dist == TSPD_Pseudo2D)
	  dst = Pseudo<long long, long long, long long>(max, max, min, min, 1LL);
	else if (dist == TSPD_Ceil2D)
	  dst = Ceil<long long, long long, long long>(max, max, min, min, 1LL);
	else if (dist != TSPD_Geographic2D)
	  dst = Euclidean<long long, long long, long long>(max, max, min, min, 1LL);
      }
      else {
	dst = (long long)(max + 0.5);
      }

      if (/* integer set fits into longs */
	  (min > 0xFFFFFFFF80000000LL) &&
	  (max < 0x000000007FFFFFFFLL) &&
	  /* integer set distances fit into longs */
	  (dst < 0x00000000FFFFFFFFLL)) {
	TSPLongBase = lcm;

	for (size_t d = 0; d < setsize; d++) {
	  pair<double, double> &tf = TSPDoubles[d];

	  TSPLongs[d] = pair<long, long>(
	    (long)(tf.first  * lcm),
	    (long)(tf.second * lcm)
	  );
	}

	fprintf(stderr, " - long [%d,%d] -> 0x%08x\n", (long)min, (long)max, (long)dst);
      }

      if (/* integer set fits into shorts */
	  (min > 0xFFFFFFFFFFFF8000LL) &&
	  (max < 0x0000000000007FFFLL) &&
	  /* integer set distances fit into shorts */
	  (dst < 0x000000000000FFFFLL)) {
	TSPShortBase = lcm;

	for (size_t d = 0; d < setsize; d++) {
	  pair<double, double> &tf = TSPDoubles[d];

	  TSPShorts[d] = pair<short, short>(
	    (short)(tf.first  * lcm),
	    (short)(tf.second * lcm)
	  );
	}

	fprintf(stderr, " - short [%d,%d] -> 0x%04x\n", (long)min, (long)max, (long)dst);
      }

      if (/* integer set fits into chars */
	  (min > 0xFFFFFFFFFFFFFF80LL) &&
	  (max < 0x000000000000007FLL) &&
	  /* integer set distances fit into chars */
	  (dst < 0x00000000000000FFLL)) {
	TSPCharBase = lcm;

	for (size_t d = 0; d < setsize; d++) {
	  pair<double, double> &tf = TSPDoubles[d];

	  TSPChars[d] = pair<char, char>(
	    (char)(tf.first  * lcm),
	    (char)(tf.second * lcm)
	  );
	}

	fprintf(stderr, " - char [%d,%d] -> 0x%02x\n", (long)min, (long)max, (long)dst);
      }
    }

    return true;
  }

  return false;
}

#include <sys/stat.h>
#include <sys/types.h>
#include <io.h>

bool PrintTSP(const char *tspname, char *name, enum TSPType &type, enum TSPFormat &frmt, enum TSPDistance &dist, int &dimension, vector< short > &route) {
  FILE *out = stdout;
  bool valid = false;

  vector< short >::const_iterator cur, nxt;
  pair<double, double> a, b, c;
  double length = 0.0, dst;

  if (TSPDoubles.size()) {
    switch (frmt) {
      case TSPF_FullMatrix:
      case TSPF_UpperDiagRow:
      case TSPF_UpperRow:
      case TSPF_LowerDiagRow:
      case TSPF_LowerRow:
        cur = route.begin();
        while (cur != route.end()) {
          /* wrap route around */
          nxt = cur + 1;
          if (nxt == route.end())
            nxt = route.begin();

          c = TSPDoubles[(*cur) * dimension + (*nxt)];
          dst = c.first;

          length += dst;
          cur++;
        }

	valid = true;
	break;

      case TSPF_UpperCol:
      case TSPF_LowerCol:
      case TSPF_UpperDiagCol:
      case TSPF_LowerDiagCol:
	valid = false;
	break;

      default:
        cur = route.begin();
        while (cur != route.end()) {
          /* wrap route around */
          nxt = cur + 1;
          if (nxt == route.end())
            nxt = route.begin();

          a = TSPDoubles[*cur];
          b = TSPDoubles[*nxt];

          switch (dist) {
            case TSPD_Geographic2D:
	      dst = Geographic<double, double, double>(a.first, a.second, b.first, b.second, 1.0);
              break;
            case TSPD_Pseudo2D:
	      dst = Pseudo<double, double, double>(a.first, a.second, b.first, b.second, 1.0);
              break;
            case TSPD_Euclidian2D:
	      dst = Euclidean<double, double, double>(a.first, a.second, b.first, b.second, 1.0);
              break;
            case TSPD_Euclidian3D:
//	      dst = Euclidean<double, double, double>(a.first, a.second, a.third, b.first, b.second, b.third, 1.0);
              break;
            case TSPD_Ceil2D:
	      dst = Ceil<double, double, double>(a.first, a.second, b.first, b.second, 1.0);
              break;
          }

          length += dst;
          cur++;
        }

	valid = true;
	break;
    }
  }

  if (valid) {
    if (tspname) {
      _chmod(tspname, _S_IREAD | _S_IWRITE);
      out = fopen(tspname, "wb");
      if (!out)
        return valid;
    }

    fprintf(out, "NAME : %s\n", tspname ? tspname : "stdout");
    fprintf(out, "COMMENT : %s %s (length %d)\n", "Held-Karp solution of", name, (int)round(length));
    fprintf(out, "TYPE : %s\n", "TOUR");
    fprintf(out, "DIMENSION : %d\n", dimension);
    fprintf(out, "TOUR_SECTION\n");

    cur = route.begin();
    while (cur != route.end()) {
      fprintf(out, "%d\n", (*cur) + 1);
      cur++;
    }

    fprintf(out, "-1\n");
    fprintf(out, "EOF\n");

    if (out != stdout) {
      fclose(out);
      _chmod(tspname, _S_IREAD | _S_IWRITE);
    }
  }

  return valid;
}

/* allow dumping mid-calc */
const char *dump_tspname;
char *dump_name;
enum TSPType dump_type;
enum TSPFormat dump_frmt;
enum TSPDistance dump_dist;
int dump_dimension;

void DumpTSP(vector< short > &route) {
  PrintTSP(dump_tspname, dump_name, dump_type, dump_frmt, dump_dist, dump_dimension, route);
}
