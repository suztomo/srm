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

using namespace std;

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
  vector<int> vi, vi2;
  for(size_t i=0;i<5;++i) vi.push_back(k[i]), vi2.push_back(sorted[i]);
  quicksort(vi);
  if (vi != vi2) {
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
  return false;
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
  return 0;
}
