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

const int inf = 99999999;
#define REP(a, b) for (size_t (a) = 0; (a)<(size_t)(b); ++(a))
#define All(a) (a).begin(), (a).end()
#define index_of(as, x) \
  distance(as.begin(), lower_bound(as.begin(), as.end(), x))

/*
  distance? lower_bound?
 */

vector<int> lis_fast(const vector<int>& a) {
  const int n = a.size();
  vector<int> A(n, inf);
  vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    // if the same value of a[i] is prior to a[i], id[i] < i
    //    latter, id[i] > i
    id[i] = index_of(A, a[i]);
    A[ id[i] ] = a[i];
  }
  // easier than REP(i, n) m >?= id[i]... No.
  int m = id[0];
  REP(i, id.size()) if (m > id[i]) m = id[i];
  m = *max_element(id.begin(), id.end());
  vector<int> b(m+1);
  for (int i = n-1; i >= 0; --i)
    if (id[i] == m) b[m--] = a[i];
  return b;
}
bool lis_fast_verify(void) {
  int a[] = {1, 3, 0, 3, 4, 2, 4, 1, 3};
  vector<int> b;
  REP(i, 9) b.push_back(a[i]);
  cout << *max_element(All(b)) << endl;
  vector<int> c = lis_fast(b);
  cout << c;
  return true;
}


vector<int> money_change(int C, vector<int> &cs) {
  int n = cs.size();
  // two big-size array.
  // It seems good to minitualiza 100 -> 1, 1,000 -> 10, 10,000 -> 100
  vector<int> xs(C+1, 99999999); // or C
  vector<int> ys(C+1);
  xs[0] = 0;
  for (int i = 0; i < n; ++i) { // for all coins
    for (int c = 0; c + cs[i] <= C; ++c) { // for all mounts?
      int tmp = c + cs[i];
      int tmp2 = xs[c] + 1;
      if (xs[tmp] > tmp2) {
        // almost all xs are 99999999 and xs+1 are 100000000.
        // So, it passes.
        xs[tmp] = tmp2;
        ys[tmp] = c;
      }
    }
  }
  /*
    xs[100] : the number of coin when you pay 100.
    ys[500] : the movement of mount when you pay 500.
      if ys[500] == 400, 500 should be partially paid by 100 coin.

    if (ys[400+100] > ys[400] + 1)
      you should pay 500 by the way of paying 400  +  a coin of 100
   */
  vector<int> zs;
  for (int c = C; c > 0; c = ys[c])
    zs.push_back(c - ys[c]);
  return zs;
}

bool money_change_verify() {
  int b[] = {10, 10, 10, 10,  100, 500};
  vector<int> a; REP(i, 8) a.push_back(b[i]);
  vector<int> c = money_change(730, a);
  cout << c;
  return true;
}


int main() {
  if (lis_fast_verify() == true)
    cout << "lis_fast ok." << endl;
  /*
  if (money_change_verify() == true)
    cout << "money_change ok." << endl;
  */
  return 0;
}
