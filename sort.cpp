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

  return 0;
}
