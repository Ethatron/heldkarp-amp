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

#ifndef	DISTANCES_HPP
#define	DISTANCES_HPP

#include "Maths.h"

/* ceiled euclidean distance */
template<typename intype, typename outype, typename basetype>
outype Ceil(intype data1x, intype data1y, intype data2x, intype data2y, basetype base) {
  intype deltax = data1x - data2x;
  intype deltay = data1y - data2y;

  double dx = (double)deltax;
  double dy = (double)deltay;

  dx /= base;
  dy /= base;

  return (outype)ceil(sqrt(dx * dx + dy * dy));
}

/* euclidean distance */
template<typename intype, typename outype, typename basetype>
outype Euclidean(intype data1x, intype data1y, intype data2x, intype data2y, basetype base) {
  intype deltax = data1x - data2x;
  intype deltay = data1y - data2y;

  double dx = (double)deltax;
  double dy = (double)deltay;

  dx /= base;
  dy /= base;

  return (outype)round(sqrt(dx * dx + dy * dy));
}

/* pseudo euclidean distance (att) */
template<typename intype, typename outype, typename basetype>
outype Pseudo(intype data1x, intype data1y, intype data2x, intype data2y, basetype base) {
  intype deltax = data1x - data2x;
  intype deltay = data1y - data2y;

  double dx = (double)deltax;
  double dy = (double)deltay;

  dx /= base;
  dy /= base;

  double att = sqrt((dx * dx + dy * dy) / 10.0);
  double rnd = round(att);

  return (outype)(rnd < att ? rnd + 1 : rnd);
}

/* geographic distance */
template<typename intype, typename outype, typename basetype>
outype Geographic(intype data1x, intype data1y, intype data2x, intype data2y, basetype base) {
  double dat1x = (double)data1x;
  double dat1y = (double)data1y;
  double dat2x = (double)data2x;
  double dat2y = (double)data2y;

  dat1x /= base;
  dat1y /= base;
  dat2x /= base;
  dat2y /= base;

  double lat1 = floor(dat1x + 0.5);
  double lng1 = floor(dat1y + 0.5);
  double lat2 = floor(dat2x + 0.5);
  double lng2 = floor(dat2y + 0.5);

  lat1 = M_PI * (lat1 + 5.0 * (dat1x - lat1) / 3.0) / 180;
  lng1 = M_PI * (lng1 + 5.0 * (dat1y - lng1) / 3.0) / 180;
  lat2 = M_PI * (lat2 + 5.0 * (dat2x - lat2) / 3.0) / 180;
  lng2 = M_PI * (lng2 + 5.0 * (dat2y - lng2) / 3.0) / 180;

  double q1 = cos(lng1 - lng2);
  double q2 = cos(lat1 - lat2);
  double q3 = cos(lat1 + lat2);

  return (outype)floor(6378.388 * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
}

#endif // DISTANCES_HPP