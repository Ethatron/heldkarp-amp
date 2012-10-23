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

#include <assert.h>

/* number of possible parallel branches, this is clamped
 * by the minimum-spanning tree connectivity and by the
 * number of cores
 */
#define PARALLEL_BRANCHES	32

/* the implicit order of a set is by comparison, then by age,
 * of those elements which have the same "key" the oldest is
 * first, then follow the younger ones
 *
 * if we want to have a stack-like order, that is: the younger
 * elements preceed the older ones we have turn the order around
 *
 * this is necessary as the set doesn't permit us to use "<="
 * as comparator
 */
#undef	PRIORIZE_FORWARDS
#define PRIORIZE_BACKWARDS

/* ********************************************************************************************
 */
namespace tsp_cpu {

/* 1-way vectors
 */
const int SIMDsize		= 1;	// in elements (for passed-in memory allocations)
const int AccessAlignment	= 1;	// in elements (for locally allocated memory only)
const int MemoryAlignment	= 1;	// in bytes

/* ********************************************************************************************
 */

template<typename sumtype>
class PathMem {
protected:
  typedef vector<sumtype> sumvector;

  /* edge matrix with weights applied, the edge weights, and the minimum spanning tree */
  static sumvector
    wghtmatrix,			// [numnodes][edgestride]
    weights,			//           [edgestride]
    mstree;			//           [edgestride]
  /* we don't count static_memory against peak_memory */

  static int numnodes;		// number of nodes, in elements
  static int edgestride;	// number of one row of edges, in elements, aligned
};

template<typename sumtype, typename idxtype>
class Path : protected PathMem<sumtype> {
public:
  /* Held-Karp solution */
  sumtype lowerBound;
  int lambdaSteps;

  /* tree of permutations */
  int depth;
  Path *seed;

  /* number of connections */
  vector<idxtype> connections;	//           [edgestride]
  vector<idxtype> parent;	//           [edgestride]

private:
  /* exclusion matrix */
  vector<bool> excluded;	// [numnodes][edgestride]

  friend bool operator < (const Path &a, const Path  &b) {
    return (a.lowerBound >= b.lowerBound);
  }

  /* --------------------------------------------------------------------------------------
   * helpers (or optimized)
   */

  static void initialize(int firstNeighbor, int edgestride, sumvector &mstree, int numnodes) {
#if 0
    /* very bad, bad bad bad */
    sumvector::iterator b = wghtmatrix.begin() + firstNeighbor * edgestride + 0;
    sumvector::iterator e = wghtmatrix.begin() + firstNeighbor * edgestride + numnodes;

    /* copy out initial costs from weight-matrix */
    mstree.assign(b, e);
#else
    memcpy(&mstree[0], &wghtmatrix[0] + firstNeighbor * edgestride + 0, numnodes * sizeof(sumtype));
#endif
  }

  static void clear(int edgestride, sumvector &weights, int numnodes) {
#if 0
    /* very bad, bad bad bad */
    weights.assign(weights.size(), 0);
#else
    memset(&weights[0], 0, edgestride * sizeof(sumtype));
#endif
  }

  static void clear(int edgestride, vector<bool> &excluded, int numnodes) {
    /* very bad, bad bad bad */
    excluded.resize(numnodes * edgestride);
    excluded.assign(numnodes * edgestride, false);
  }

  static void clone(int edgestride, vector<bool> &dstexcluded, const vector<bool> &srcexcluded, int numnodes) {
    /* very bad, bad bad bad */
    vector<bool>::const_iterator b = srcexcluded.begin();
    vector<bool>::const_iterator e = srcexcluded.end();

    dstexcluded.resize(srcexcluded.size());
    dstexcluded.assign(b, e);
  }

  /* --------------------------------------------------------------------------------------
   */

  void initialize(int firstNeighbor, int edgestride) {
#if 0
    /* very bad, bad bad bad */
    this->connections.assign(this->connections.size(), 0);
    this->parent.assign(this->parent.size(), firstNeighbor);
#else
    memset(&this->connections[0], 0, edgestride * sizeof(idxtype));
    for (int j = 0; j < edgestride; j += 1)
      this->parent[j] = firstNeighbor;
#endif
  }

  void connect(int i, int j, int edgestride, sumvector &wghtmatrix) {
    this->lowerBound += wghtmatrix[i * edgestride + j];

    /* register new connections */
    this->connections[i]++;
    this->connections[j]++;
  }

  /* --------------------------------------------------------------------------------------
   * main function (50-60% of time spend here)
   */

  template<typename edgtype>
  void computeOneTree(int numnodes, int edgestride, const vector<edgtype> &edgematrix) {
    /* compute adjusted costs */

//  int exclusions = 0;
//  double checksum = 0.0;

    /* embarrassingly parallel */
    for (int row = 0; row < numnodes; row++) {
      for (int col = 0; col < numnodes; col++) {
	if (this->excluded[row * edgestride + col]) {
//	  checksum += 0.0; exclusions++;
//	  report("EX %d,%d ", row, col);

	  wghtmatrix[row * edgestride + col] = maxvec<sumtype>();
	}
	else {
//	  checksum += edgematrix[row * edgestride + col] + weights[row] + weights[col];

	  wghtmatrix[row * edgestride + col] = edgematrix[row * edgestride + col] + weights[row] + weights[col];
	}
      }
    }

//  report("CS %f (%d) ", checksum, exclusions);

    /* get the two cheapest edges from 0 --------------------------------------------------- */

    /* get the two cheapest edges from 0 */
    int firstNeighbor  = 1;
    int secondNeighbor = 2;
    /* order by cost */
    if (wghtmatrix[0 * edgestride + 2] < wghtmatrix[0 * edgestride + 1]) {
      firstNeighbor  = 2;
      secondNeighbor = 1;
    }

    /* parallel search */
    for (int j = 3; j < numnodes; j++) {
      if (wghtmatrix[0 * edgestride + j] < wghtmatrix[0 * edgestride + secondNeighbor]) {
	if (wghtmatrix[0 * edgestride + j] < wghtmatrix[0 * edgestride + firstNeighbor]) {
	  secondNeighbor = firstNeighbor;
	  firstNeighbor = j;
	}
	else {
	  secondNeighbor = j;
	}
      }
    }

    /* initialize tree */
    initialize(firstNeighbor, edgestride);

    /* compute the minimum spanning tree on nodes [1, numnodes - 1] ------------------------ */

    /* calculate length of path */
    this->lowerBound = 0;

    /* add first edge */
    this->connect(0, firstNeighbor, edgestride, wghtmatrix);
    this->parent[firstNeighbor] = 0;

    report("FS %d %d %f\n", firstNeighbor, secondNeighbor, this->lowerBound);

    /* copy out initial costs from weight-matrix */
    initialize(firstNeighbor, edgestride, mstree, numnodes);

    /* consume all unassigned edges */
    for (int k = 2, l = 1; k < numnodes; k++) {
      /* remember last first found to start next */
      int i, h = numnodes;

      /* search first unassigned */
      for (i = l; i < numnodes; i++) {
	if ((this->connections[i] == 0)) {
	  l = i;
	  break;
	}
      }

      /* search next unassigned with lowest cost */
      for (int j = i + 1; j < numnodes; j++) {
	if (this->connections[j] == 0) {
	  if (mstree[j] < mstree[i])
	    i = j;

	  h = j + 1;
	}
      }

      report(" %d %g [%d,%d]\n", i, mstree[i], l, h);

      /* add unassigned with lowest cost */
      this->connect(this->parent[i], i, edgestride, wghtmatrix);

      for (int j = l; j < numnodes; j++) {
	if ((this->connections[j] == 0) && (wghtmatrix[i * edgestride + j] < mstree[j])) {
	  mstree[j] = wghtmatrix[i * edgestride + j];

	  this->parent[j] = i;
	}
      }
    }

    /* add last edge */
    this->connect(0, secondNeighbor, edgestride, wghtmatrix);
    this->parent[0] = secondNeighbor;

    report("OT %f\n", this->lowerBound);

    /* round-to-nearest, round half towards minus infinity, prevent sum-of-squares problem */
    this->lowerBound = round(this->lowerBound);
  }

  template<typename edgtype>
  bool computeHeldKarp(int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    this->connections.resize(edgestride);
    this->parent.resize(edgestride);

    /* prepare weights (initially zero) */
    clear(edgestride, weights, numnodes);

    this->lowerBound = maxvec<sumtype>();

    /* lagrangian optimization */
    sumtype lambda = (sumtype)0.1;
    int     lambda_count = 0;
    sumtype lambda_reduction = (sumtype)::lambda_reduction;
    sumtype lambda_termination = (sumtype)::lambda_termination;

    while (lambda > lambda_termination) {
      sumtype prevLowerBound = this->lowerBound;

      /* interpretes:
       * - weights (all of it)
       * - edgematrix (all of it)
       *
       * fills:
       * - wghtmatrix (all of it)
       * - degree (all of it)
       * - parent (all of it)
       */
      this->computeOneTree(numnodes, edgestride, edgematrix);

      /* cut early */
      if (!(this->lowerBound < bestLowerBound))
	break;
      if (!(this->lowerBound < prevLowerBound))
	lambda *= lambda_reduction;

      {
	/* reduction */
	int denom = 0;
        /* connections[0] is always "2" */
	for (int i = 1; i < numnodes; i++) {
	  int d = (this->connections[i] - 2);
	  denom += d * d;
	}

	/* switch */
	if (denom == 0)
	  break;

	/* embarrassingly parallel */
	sumtype t = lambda * this->lowerBound / denom;
	for (int i = 1; i < numnodes; i++)
	  weights[i] += t * (this->connections[i] - 2);
      }

      lambda_count++;
    }

    /* is this a possibly shorter path? */
    this->lambdaSteps = lambda_count;
    return (this->lowerBound < bestLowerBound);
  }

public:
  Path() { curr_memory += sizeof(Path) + sizeof(idxtype) * (edgestride) * 2 + sizeof(bool) * (edgestride); peak_memory = max(peak_memory, curr_memory); }
  virtual ~Path() { curr_memory -= sizeof(Path) + sizeof(idxtype) * (edgestride) * 2 + sizeof(bool) * (edgestride); num_iterations += this->lambdaSteps; }

  static void exit() {
    PathMem::weights.clear();
    PathMem::wghtmatrix.clear();
    PathMem::mstree.clear();
  }

  template<typename edgtype>
  static Path *setup(int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    Path *root = new Path();

    /* root node initializes static memories */
    PathMem::weights.resize(edgestride);
    PathMem::wghtmatrix.resize(numnodes * edgestride);
    PathMem::mstree.resize(edgestride);

    /* round to full ulongs */
    PathMem::numnodes   = numnodes;
    PathMem::edgestride = edgestride;

    /* clear out exclusion-matrix */
    clear(edgestride, root->excluded, numnodes);

    root->depth = 0;
    root->seed = NULL;
    root->computeHeldKarp<edgtype>(numnodes, edgestride, edgematrix, bestLowerBound);

    return root;
  }

  template<typename edgtype>
  Path *permute(int i, int j, int numnodes, int edgestride, const vector<edgtype> &edgematrix, sumtype bestLowerBound) {
    /* memory allocation limit */
    if (curr_memory >= memory_limit)
      return NULL;
    /* loop-detection: depth exceeds the possible number of connections */
    if (this->depth >= numnodes)
      return NULL;

    Path *child = new Path();
    if (!child) {
      /* soft-abort, we can continue ignoring this
       * later maybe some memory is free again
       * won't find the optimal solution anymore of course
       */
      return child;
    }

    assert(!(this->excluded[i * edgestride + j]));
    assert(!(this->excluded[j * edgestride + i]));

    /* clone out exclusion-matrix */
    clone(edgestride, child->excluded, this->excluded, numnodes);

    child->excluded[i * edgestride + j] = true;
    child->excluded[j * edgestride + i] = true;

    child->depth = this->depth + 1;
    child->seed = this;
    if (!child->computeHeldKarp(numnodes, edgestride, edgematrix, bestLowerBound)) {
      delete child;
      child = NULL;
    }

    return child;
  }

  int verify() {
    int i = -1;

    /* search first node with too many connections */
    for (int j = 0; j < numnodes; j++) {
      if ((this->connections[j] > 2)) {
	i = j;

	/* search next node with lowest too many connections */
	for (j = i + 1; j < numnodes; j++) {
	  if ((this->connections[j] > 2) && (this->connections[j] < this->connections[i]))
	    i = j;
	}

	break;
      }
    }

    return i;
  }
};

vector<float> PathMem<float>::weights;
vector<float> PathMem<float>::wghtmatrix;
vector<float> PathMem<float>::mstree;

int PathMem<float>::numnodes;
int PathMem<float>::edgestride;

vector<double> PathMem<double>::weights;
vector<double> PathMem<double>::wghtmatrix;
vector<double> PathMem<double>::mstree;

int PathMem<double>::numnodes;
int PathMem<double>::edgestride;

/* ********************************************************************************************
 */
#include "solver/Plain.cpp"

#undef	PARALLEL_BRANCHES
#undef	PRIORIZE_FORWARDS
#undef	PRIORIZE_BACKWARDS

}
