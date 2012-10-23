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

template<typename sumtype, typename idxtype, typename sumvectype, typename idxvectype>
class Solution {
  typedef Path<sumtype, idxtype, sumvectype, idxvectype> SPath;

  template<typename sumtype, typename idxtype>
  struct sorting {
    bool operator() (SPath *a, SPath *b) const {
#ifdef	PRIORIZE_FORWARDS
      return (a->lowerBound < b->lowerBound);
#else
      return (a->lowerBound > b->lowerBound);
#endif
    }
  };

  void putroute(vector<idxtype> &route) {
    /* give the solution back ... */
    route.clear();

    /* ... if it exists */
    if (bestPath->lowerBound < maxvec<sumtype>()) {
      int j = 0;
      do {
        route.push_back(j);
        j = bestPath->parent[j];
      } while (j != 0);
    }
  }

public:
  /* number of nodes to process, and in one matrix-row */
  int concurrent;
  int numnodes;
  int edgestride;

  /* edge matrix */
//sumvector edgematrix;	// [numnodes][edgestride]

  SPath *bestPath;
  SPath *currPath;

  /* branch buffer */
  critical_section robin[PARALLEL_BRANCHES];
  vector<int> branches;
  vector<SPath *> paths;

  /* priority "queue" */
  multiset< SPath *, sorting<sumtype, idxtype> > ms;

  Solution(int num, int stride) : branches(num), paths(num) {
    /* get number of parallel processors/concurrency limits */
    int PARALLEL_THREADS = CurrentScheduler::GetNumberOfVirtualProcessors();
    if (PARALLEL_THREADS < 1)
      PARALLEL_THREADS = PARALLEL_BRANCHES;
    if (thread_limit > 0)
      PARALLEL_THREADS = min(PARALLEL_THREADS, thread_limit);

    SchedulerPolicy sp = CurrentScheduler::GetPolicy();
    concurrent = sp.GetPolicyValue(MaxConcurrency);
    concurrent = (concurrent < PARALLEL_BRANCHES ? concurrent : PARALLEL_BRANCHES);
    concurrent = (concurrent < PARALLEL_THREADS  ? concurrent : PARALLEL_THREADS );
    sp.SetConcurrencyLimits(1, concurrent);

    /* get number of nodes from the square edge matrix */
    numnodes = num;
    edgestride = stride;
  }

  ~Solution() {
    bestPath->exit(PARALLEL_BRANCHES);
    delete bestPath;
  }

  template<typename edgtype, typename edgvectype, typename edgresview>
  void solve(edgresview &edgematrix, vector<idxtype> &route) {
    int prunes = 0;
    int drops = 0;

    /* set up a dummy path to compare to */
    bestPath = new SPath();
    bestPath->lambdaSteps = 0;
    bestPath->lowerBound = maxvec<sumtype>();

    /* set up an empty path to start with */
    currPath = SPath::setup<edgtype, edgvectype, edgresview>(concurrent, numnodes, edgestride, edgematrix, bestPath->lowerBound);

    do {
      do {
	int i = currPath->lowestSubgraph;

	/* a round-trip path has been found (all connections == 2, none > 2) */
	if (i < 0) {
	  /* the path is better than the old */
	  if (currPath->lowerBound < bestPath->lowerBound) {
	    delete bestPath;
	    bestPath = currPath;

#ifdef	DUMP_BEST_ALWAYS
            putroute(route);
            DumpTSP(route);
#endif

	    fprintf(stderr, "pool %6d (%6d drops, %6d prunes), best %.2f                      \n", ms.size(), drops, prunes, currPath->lowerBound);
	  }

	  break;
	}

//	printf("%d %d", i, currPath->parent[i]);
//	printf(".");

	/* use current, and search the other two nodes the current is parent of */
	int p = 0;

	/* parallel search (capped) */
	branches[p++] = currPath->parent[i];
	for (int j = 0; j < numnodes; j++) {
	  if (currPath->parent[j] == i)
	    branches[p++] = j;
	}

	/* local priority "queue" */
	multiset< SPath *, sorting<sumtype, idxtype> > children;
	multiset< SPath *, sorting<sumtype, idxtype> >::iterator cP;
	multiset< SPath *, sorting<sumtype, idxtype> >::reverse_iterator cR;

	/* branch out 2-4 new permutations with the found node as anchor (possible in parallel) */
#ifndef DUMP
	parallel_for(0, p, 1, [&](int pb) {
#else
	for (int bp = 0; bp < p; bp++) { int pb = bp;
#endif
	  /* limited number of parallel instances, round-robin assignment */
	  pb %= concurrent;

	  robin[pb].lock();
	  paths[pb] = currPath->permute<edgtype, edgvectype, edgresview>(pb, i, branches[pb], edgematrix, bestPath->lowerBound);
	  robin[pb].unlock();
	}
#ifndef DUMP
	);
#endif

	/* remove all already worst, dead branches, don't follow */
	for (int pb = 0; pb < p; pb++) {
	  if (paths[pb])
	    children.insert(paths[pb]);
	  else
	    drops++;
	}

	/* no branches have a lower bound, leave the loop */
#ifdef	PRIORIZE_FORWARDS
	cP = children.begin();
	if (cP == children.end())
	  break;
#else
	cR = children.rbegin();
	if (cR == children.rend())
	  break;
	cR++;
	cP = cR.base();
#endif

	/* delete the seed-path of newly added paths ... */
	if (currPath != bestPath)
	  delete currPath;

	/* try successive branches immediately to complete a valid path quickly */
	currPath = *cP;
	children.erase(cP);

	/* transfer rest of the queue */
	cP = children.begin();
	if (cP != children.end())
	  ms.insert(cP, children.end());

	static int progress = 0;
	if (!(++progress & 31))
	  fprintf(stderr, "pool %6d (%6d drops, %6d prunes), next %.2f, depth %4d\r", ms.size(), drops, prunes, currPath->lowerBound, currPath->depth);

	assert(currPath->lowerBound < bestPath->lowerBound);
      } while (1);

     /* global priority "queue" */
      multiset< SPath *, sorting<sumtype, idxtype> >::iterator cP, cF;
      multiset< SPath *, sorting<sumtype, idxtype> >::reverse_iterator cR;

      /* remove all already worst, dead branches, don't follow */
#ifdef	PRIORIZE_FORWARDS
      cP = ms.lower_bound(bestPath);
      if (cP != ms.end()) {
	for (cF = cP; cF != ms.end(); cF++, prunes++)
	  delete *cF;

	ms.erase(cP, ms.end());
      }

      /* no remaining entries left */
      cP = ms.begin();
      if (cP == ms.end())
	break;
#else
      cP = ms.upper_bound(bestPath);
      if (cP != ms.begin()) {
	for (cF = ms.begin(); cF != cP; cF++, prunes++)
	  delete *cF;

	ms.erase(ms.begin(), cP);
      }

      /* no remaining entries left */
      cR = ms.rbegin();
      if (cR == ms.rend())
	break;
      cR++;
      cP = cR.base();
#endif

      /* delete the last checked path ... */
      if (currPath != bestPath)
	delete currPath;

      /* try what's left in the queue */
      currPath = *cP;
      ms.erase(cP);

      assert(currPath->lowerBound < bestPath->lowerBound);
    } while (1);

    if (currPath != bestPath)
      delete currPath;

    /* give the solution back ... */
    putroute(route);
  }
};

#undef	PRIORIZE_FORWARDS
#undef	PRIORIZE_BACKWARDS
