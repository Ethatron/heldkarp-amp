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

//#ifndef	SOLVETSP_SBM_HPP
//#define SOLVETSP_SBM_HPP

/* cross-link exclusion matrices to save space, it's slower
 * of course
 * this effectively only allocates new memory for the
 * two changed rows, the others are copied references
 */
#define	CONSERVE_MEMORY
#ifndef	CONSERVE_MEMORY
template<typename InheritedMem>
class SBMatrixMem : protected InheritedMem {
protected:
  typedef vector<ulong, SSE2Allocator<ulong> > bolvector;

//static int numnodes;		// number of nodes, in elements
//static int boolstride;	// number of one row of bools, in bits, aligned

#define	boolulongs()	(boolstride / (sizeof(ulong) * 8))
};

/* Shared Boolean Matrix */
template<typename InheritedMem>
class SBMatrix : protected SBMatrixMem<InheritedMem> {

private:
  /* exclusion matrix */
  bolvector included;			// [numnodes][boolstride]

  /* --------------------------------------------------------------------------
   */
protected:

  bool operator () (int i, int j) {
    int bitposi = (i + 0) * boolstride + (j + 0);
    int basebiti = bitposi & 31;

    return !!(this->included[bitposi >> 5] >> basebiti);
  }

  void set(int j) {
    int bitposj = (j + 0) * boolstride + (j + 0);
    int basebitj = bitposj & 31;

    assert(!!(this->included[bitposj >> 5] & (1 << basebitj)));

    this->included[bitposj >> 5] &= ~(1 << basebitj);
  }

  void set(int i, int j) {
    int bitposi = (i + 0) * boolstride + (j + 0);
    int bitposj = (j + 0) * boolstride + (i + 0);
    int basebiti = bitposi & 31;
    int basebitj = bitposj & 31;

    assert(!!(this->included[bitposi >> 5] & (1 << basebiti)));
    assert(!!(this->included[bitposj >> 5] & (1 << basebitj)));

    this->included[bitposi >> 5] &= ~(1 << basebiti);
    this->included[bitposj >> 5] &= ~(1 << basebitj);
  }

  ulong *raw(int pb) {
    return &this->included[0];
  }

  /* --------------------------------------------------------------------------
   */
private:

  static void __fastcall clear(vector<ulong> &included) {
    included.resize(numnodes * boolulongs());
    memset(&included[0], -1, numnodes * boolulongs() * sizeof(ulong));
  }

  static void __fastcall clone(vector<ulong> &dstincluded, const vector<ulong> &srcincluded) {
    dstincluded.resize(numnodes * boolulongs());
    memcpy(&dstincluded[0], &srcincluded[0], numnodes * boolulongs() * sizeof(ulong));
  }

  void clear() {
    this->included.resize(numnodes * boolulongs());
    memset(&this->included[0], -1, numnodes * boolulongs() * sizeof(ulong));
  }

  void clone(SBMatrix &src) {
    this->included.resize(numnodes * boolulongs());
    memcpy(&this->included[0], &src.included[0], numnodes * boolulongs() * sizeof(ulong));
  }

  /* --------------------------------------------------------------------------
   */
public:
  SBMatrix() {}
  virtual ~SBMatrix() { included.clear(); }

protected:

  void setup(int pb, int numnodes, int edgestride) {
    SBMatrixMem::numnodes   = numnodes;
    SBMatrixMem::boolstride = (edgestride + 31) & (~31);

    /* clear out exclusion-matrix */
    clear();

    /* mask out all j->j edges (specifically 0->0) */
    for (int j = 0; j < numnodes; j++)
      set(j);
  }

  void permute(int pb, int i, int j, SBMatrix &src) {
    /* clone out exclusion-matrix */
    clone(src);

    /* mask out the i->j/j->i edge */
    set(i, j);
  }

};
#else
template<typename InheritedMem>
class SBMatrixMem : protected InheritedMem {
protected:
  typedef vector<ulong, SSE2Allocator<ulong> > bolvector;

  static critical_section r;
  static bolvector
    continuous[PARALLEL_BRANCHES];		// [numnodes][boolstride]
  /* we don't count static_memory against peak_memory */

//static int numnodes;		// number of nodes, in elements
//static int boolstride;	// number of one row of bools, in bits, aligned

#define	boolulongs()	(boolstride / (sizeof(ulong) * 8))
};

/* Shared Boolean Matrix */
template<typename InheritedMem>
class SBMatrix : protected SBMatrixMem<InheritedMem> {

  /* --------------------------------------------------------------------------
   */
private:
  struct sharedrow {
    size_t counter;
    ulong row[1];

//  sharedrow &operator -> () { return *this; }
//  ulong &operator [] (int offs) { return row[offs]; }
  };

#define	sharesize()	(sizeof(size_t) + boolulongs() * sizeof(ulong))

  /* exclusion matrix */
  vector<sharedrow *> included;			// [numnodes][boolstride]

  /* --------------------------------------------------------------------------
   */
protected:

  bool operator () (int i, int j) {
    int bitposi = (j + 0);
    int basebiti = bitposi & 31;

    return !!(this->included[(i + 0)]->row[bitposi >> 5] >> basebiti);
  }

  void set(int j) {
    int bitposj = (j + 0);
    int basebitj = bitposj & 31;

    assert(!!(this->included[(j + 0)]->row[bitposj >> 5] & (1 << basebitj)));

    this->included[(j + 0)]->row[bitposj >> 5] &= ~(1 << basebitj);
  }

  void set(int i, int j) {
    int bitposi = (i + 0);
    int bitposj = (j + 0);
    int basebiti = bitposi & 31;
    int basebitj = bitposj & 31;

    assert(!!(this->included[(i + 0)]->row[bitposj >> 5] & (1 << basebitj)));
    assert(!!(this->included[(j + 0)]->row[bitposi >> 5] & (1 << basebiti)));

    this->included[(i + 0)]->row[bitposj >> 5] &= ~(1 << basebitj);
    this->included[(j + 0)]->row[bitposi >> 5] &= ~(1 << basebiti);
  }

  /* return the requested single vector-memory */
  ulong *raw(int pb) {
    return &continuous[pb][0];
  }

  /* return the requested multiple consecusive vector-memories */
  ulong *raw(int pb, int np) {
#ifndef PARALLEL_MEMORY
    abort();
#else
    size_t length = (pb + np) * numnodes * boolulongs();
    size_t position = (pb + 0) * numnodes * boolulongs();

    assert(length <= continuous[0].size());
    return &continuous[0][position];
#endif
  }

  /* --------------------------------------------------------------------------
   */
private:

  void release() {
#if 1
//  for (int j = 0; j < numnodes; j++) {
    for (size_t j = 0; j < this->included.size(); j++) {
      assert(this->included[j]->counter > 0);
      if (!InterlockedDecrement(&this->included[j]->counter)) {
        free(this->included[j]);
      }
    }
#else
//  for (int j = 0; j < numnodes; j++) {
    for (size_t j = 0; j < this->included.size(); j++) {
      if (this->included[j]) {
	assert(this->included[j]->counter > 0);
	if (!InterlockedDecrement(&this->included[j]->counter)) {
	  free(this->included[j]);
	  this->included[j] = NULL;
	}
      }
    }

    this->included.clear();
#endif
  }

  void clear() {
    /* assign caches */
    this->included.resize(numnodes);

    for (int j = 0; j < numnodes; j++) {
      this->included[j] = (sharedrow *)malloc(sharesize());
      this->included[j]->counter = 1;

      memset(&this->included[j]->row, -1, boolulongs() * sizeof(ulong));
    }
  }

  void clone(SBMatrix &src, int ci, int cj) {
    /* assign caches */
    this->included.resize(numnodes);

    for (int j = 0; j < numnodes; j++) {
      assert(src.included[j]->counter > 0);

      /* shallow copy */
      if ((j != ci) && (j != cj)) {
	this->included[j] = src.included[j];
	InterlockedIncrement(&this->included[j]->counter);
      }
      /* deep copy */
      else {
	this->included[j] = (sharedrow *)malloc(sharesize());
	this->included[j]->counter = 1;

	memcpy(&this->included[j]->row, &src.included[j]->row, boolulongs() * sizeof(ulong));
      }
    }
  }

  void map(int pb) {
#ifdef PARALLEL_MEMORY
    r.lock();
#endif

#ifndef PARALLEL_MEMORY
    continuous[pb].resize(numnodes * boolulongs());
    ulong *block = &continuous[pb][0];
#else
    size_t length = (pb + 1) * numnodes * boolulongs();
    size_t position = (pb + 0) * numnodes * boolulongs();

    if (continuous[0].size() < length)
      continuous[0].resize(length);

    ulong *block = &continuous[0][position];
#endif

    for (int j = 0; j < numnodes; j++) {
      assert(this->included[j]->counter > 0);

      /* cloning is always a 1-pass process: clone()+calc()
       *
       * the thread which requested the clone will immediately
       * start using that clone and will request the flat continous
       * matrix, so we can do that in this moment, reducing overhead
       */
      memcpy(block + j * boolulongs(), &this->included[j]->row, boolulongs() * sizeof(ulong));
    }

#ifdef PARALLEL_MEMORY
    r.unlock();
#endif
  }

  /* --------------------------------------------------------------------------
   */
public:
  SBMatrix() { mst.lock(); curr_memory += sharesize(); peak_memory = max(peak_memory, curr_memory); mst.unlock(); }
  virtual ~SBMatrix() { mst.lock(); curr_memory -= sharesize(); release(); mst.unlock(); }

protected:

  static void exit(int pb) {
    for (int p = 0; p < pb; p++) {
      glob_memory += SBMatrixMem::continuous[p].size() * sizeof(ulong);

      SBMatrixMem::continuous[p].clear();
    }
  }

  void setup(int pb, int numnodes, int edgestride) {
    SBMatrix::numnodes   = numnodes;
    SBMatrix::boolstride = (edgestride + 31) & (~31);

    /* clear out exclusion-matrix */
    clear();

    /* mask out all j->j edges (specifically 0->0) */
    for (int j = 0; j < numnodes; j++)
      set(j);

    /* get the raw view */
    map(0);
  }

  void permute(int pb, int i, int j, SBMatrix &src) {
    /* clone out exclusion-matrix */
    clone(src, i, j);

    /* mask out the i->j/j->i edge */
    set(i, j);

    /* get the raw view */
    map(pb);
  }
};
#endif

//#endif
