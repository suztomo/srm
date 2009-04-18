/*
  Container.

  Reference:
  http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary2#creating

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


int main() {
  map_iterate_sample();
  next_permutaiton_sample();
  return 0;
}
