/*
  The ``Shakyo'' algorithm library for TopCoder.
  http://www.prefield.com/algorithm/
 */
#define _GLIBCXX_DEBUG
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>
#include <list>
#include "cout.h"


using namespace std;

#define REP(a, b) for (size_t (a) = 0; (a)<(size_t)(b); ++(a))

/*
  K is sizeof alphabet e.g. a-z => ('z' - 'a'+1)
  This parameter must be passed by poiner.
*/
void countingSort(vector<int> &a, int K) {
  int c[K], j = 0;
  fill(c, c+K, 0);
  REP(i,a.size()) ++c[a[i]];
  REP(k,K) REP(i,c[k]) a[j++] = k;
}

bool verify_countingSort(void) {
  int a[] = {5, 3, 2, 8, 9};
  int a2[] = {2, 3, 5, 8, 9};
  vector<int> b, b2;
  REP(i, 5) b.push_back(a[i]), b2.push_back(a2[i]);
  countingSort(b, 10);
  assert(b == b2);
  return true;
}

void mergesort(vector<int> &a) {
  size_t n = a.size();
  if (n > 1) {
    vector<int> b(a.begin(), a.begin() + n/2);
    vector<int> c(a.begin() + n/2, a.end());
    mergesort(b);
    mergesort(c);
    for (size_t i = 0, j = 0, k = 0; i < n; ++i)
      if (k == c.size())      a[i] = b[j++];
      else if (j == b.size()) a[i] = c[k++];
      else if (b[j] < c[k])   a[i] = b[j++];
      else                    a[i] = c[k++];
  }
}

void quicksort_iter(vector<int> &a, int l, int r) {
  if (l < r) {
    int p = a[(l+r)/2];
    int i = l-1, j = r+1;
    while (1) {
      while (a[++i] < p);
      while (a[--j] > p);
      if (i >= j) break;
      swap(a[i], a[j]);
    }
    quicksort_iter(a, l, i-1);
    quicksort_iter(a, j+1, r);
  }
}
void quicksort(vector<int> &a) {
  quicksort_iter(a, 0, a.size()-1);
}

bool quicksort_valid(void) {
  int k[] = {1, 5,3, 9, 2};
  int sorted[] = {1, 2, 3, 5, 9};
  vector<int> vi, vi2, vi3;
  for(size_t i=0;i<5;++i) vi.push_back(k[i]), vi2.push_back(sorted[i]),
                            vi3.push_back(k[i]);
  quicksort(vi);
  mergesort(vi3);
  if (vi != vi2 && vi == vi3) {
    exit(1);
  }
  return true;
}


bool pred(pair<string, int> a, pair<string, int> b) {
 return a.second < b.second;
}

bool sort_by_second() {
  map<string, int> m;
  m["suzuki"] = 12;
  m["tomohiro"] = 234;
  m["tako"] = 23;
  vector<pair<string, int> > vp(m.begin(), m.end());
  sort(vp.begin(), vp.end(), pred);
  if (vp[0].first == "suzuki" && vp[1].first == "tako" && vp[2].first == "tomohiro"){
    return true;
  }
  assert(false);
  return false;
}
#include <functional>

class comp_size{
public:
  template< class PairTyp > bool operator()( PairTyp& a, PairTyp& b ) {
    return a.size() < b.size();
  }
};


bool pred_size(vector<string> &a, vector<string> &b) {
  return a.size() > b.size();
}

bool sort_vector_by_size() {
  vector< vector < string > > vv;
  vector<string> v1; v1.push_back("Hello"); v1.push_back("world");
  vector<string> v2; v2.push_back("konbanwa"); v2.push_back("hogehog"); v2.push_back("");
  vector<string> v3;
  vv.push_back(v1); vv.push_back(v2); vv.push_back(v3);
  sort(vv.begin(), vv.end(), comp_size());

  assert(vv[0].size() == 0 && vv[1].size() == 2 && vv[2].size() == 3);


  return true;
}

int main() {
  if (sort_by_second()) {
    cout << "sort ok." << endl;
  } else {
    cout << "sort ng." << endl;
    exit(1);
  }
  if (!quicksort_valid()) {
    cout << "quicksort ok." << endl;
  }
  if (verify_countingSort()) 
    cout << "countingSort ok." << endl;
  if (sort_vector_by_size())
    cout << "sort by size ok." << endl;
  return 0;
}
