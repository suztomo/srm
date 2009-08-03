/*
  Container.

  Reference:
  http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary2#creating

 */
//#define _GLIBCXX_DEBUG
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

#define Tr(c, i) for(typeof((c).begin()) i= (c).begin(); (i) != (c).end(); ++(i))
#define All(a) (a).begin(), (a).end()

bool pred(pair<string, int> a, pair<string, int> b) {
 return a.second < b.second;
}

int map_iterate_sample() {
  map<string, int> m;

  m["suzuki"] = 12;
  m["takuya"] = 18;
  m["noriko"] = 26;

  vector< pair<string, int> > v(All(m));

  sort(All(v), pred);

  Tr(m, i) {
    cout << (i->first) << " : " << (i->second) << endl;
  }
  Tr(v, i) {
    cout << (i->second) << " : " << (i->first) << endl;
  }

  return 0;
}

int next_permutaiton_sample() {
  int ary[4];
  ary[0] = 0, ary[1] = 1, ary[2] = 2, ary[3] = 3;
  set<string> s;
  vector<string> vs;
  vs.push_back("a"), vs.push_back("b"), vs.push_back("c"), vs.push_back("d");
  sort(All(vs));
  do {
    string t;
    t = vs[ary[0]] + vs[ary[1]] + vs[ary[2]] + vs[ary[3]];
    s.insert(t);
  } while (next_permutation(ary, ary+4));

  int c = s.size();
  assert(c == 24);
  return 0;
}

int element_sample() {
  vector<int> v;
  v.push_back(1);v.push_back(10);v.push_back(-39);v.push_back(5);
  assert(-39 == *min_element(All(v)));
  assert(10 == *max_element(All(v)));
  sort(All(v));
  assert(binary_search(All(v), 5));

  /* upper_bound returns a itereator of next to upper limit */
  /* See http://topcoder.g.hatena.ne.jp/nitoyon/20081025/1224944902 */

  /* 6以上になるはじめての場所 */
  assert(5 == *(upper_bound(All(v), 6) - 1));

  /* 1以下の最大の数字 */
  assert(1 == *(lower_bound(All(v), 1)));

  v.push_back(10);
  assert(10 == *adjacent_find(All(v)));
  assert(2 == count(All(v), 10));



  cout << "passed min_element_sample" << endl;

  return 1;
}

int count_continue() {
  int a[] = {1, 3, 5, 2, 4, 10, 2, 2};
  // got error:   int n = (int)sizeof(a);
  int n = (int)(sizeof(a) / sizeof(int));
  int c=0;
  sort(a, a+n);
  do {
    if (adjacent_find(a, a+n) != a + n) {
      ++c;
    }
  }while(next_permutation(a, a+n));
  assert(c == 4320);
  return 0;
}

int erase_sample() {
  vector<int> v;
  v.push_back(2);  v.push_back(5);  v.push_back(3);  v.push_back(9);
  v.push_back(12);  v.push_back(1);  v.push_back(12);  v.push_back(8);
  assert(v.size() == 8);
  sort(All(v));
  v.erase(unique(All(v)), v.end());
  assert(v.size() == 7);

  v.clear();
  assert(v.size() == 0);

  return 1;
}


int main() {
  map_iterate_sample();
  next_permutaiton_sample();
  element_sample();
  count_continue();
  erase_sample();
  return 0;
}
