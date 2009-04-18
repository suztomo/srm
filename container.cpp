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

int main() {
  map_iterate_sample();
  return 0;
}
