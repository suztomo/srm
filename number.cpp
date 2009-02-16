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

// the same as __gcd(a, b)
int gcd(int a, int b) {
  return b != 0 ? gcd(b, a % b) : a;
}
int lcm(int a, int b) {
  return a * b / gcd(a, b);
}
// a x + b y = gcd(a, b)
// ?? Nandakore
int extgcd(int a, int b, int &x, int &y) {
  int g = a;
  x = 1;
  y = 0;
  if (b != 0) {
    // looks like gcd()
    g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }
  return g;
}


bool gcd_verify(void) {
  int a=13, b=17, c, d;
  c = lcm(a, b);
  assert(c == 221);

  a=80,b=12;
  c = gcd(a, b);
  assert(c==4);
  a=12,b=18;
  c = lcm(a, b);
  assert(c==36);

  extgcd(a, b, c, d);
  //  assert(d==3);
  return true;
}

int main() {
  if (gcd_verify()) cout << "gcd ok." << endl;
  return 0;
}
