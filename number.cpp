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
/* 2^64, about 20 digits */
typedef long long Int;

// the same as __gcd(a, b)
int gcd(int a, int b) {
  return b != 0 ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
  return a * b / gcd(a, b);
}

/*
  a x + b y = gcd(a, b)
 There're many pair of this. But returns ???.
 It seems x is not to be greater than b
*/
int extgcd(int a, int b, int &x, int &y) {
  int g = a;
  if (b != 0) {
    // looks like gcd()
    g = extgcd(b, a % b, y, x); // <- reset x and y
    // g = b * y + (a%b) * x
    y -= (a / b) * x;
  } else {
    // if b == 0
    // gcd(a, 0) = a = a * 1 + 0 * 0
    x = 1;
    y = 0;
  }
  return g;
}


bool gcd_verify(void) {
  int a=13, b=17, c, d, e;
  c = lcm(a, b);
  assert(c == 221);

  a=80,b=12;
  c = gcd(a, b);
  assert(c==4);
  a=12,b=18;
  c = lcm(a, b);
  assert(c==36);


  /*
    extgcd();
    6 = gcd(12, 18)
    6 = 12 * -1 + 18 * 1
  */
  e = extgcd(a, b, c, d);
  assert(c == -1);
  assert(d == 1);
  assert(e == 6);

  return true;
}

/*
  Calculate the x, s.t. "x * a == 1 (mod m)".
  Variable a and m must be coprime.
    x * a = y * m + 1 (y is a integer).
    if gcd(a, m) > 1, then there's a contradiction:
      the left part "x*a" is dividable by the gcd, but right part "y*m+1"
      cannot be dividable by gcd.
 */
int invMod(int a, int m) {
  int x, y; // y is not used.
  // extgcd : 1 = a*x + m*y.
  if (extgcd(a, m, x, y) == 1) // the x must not greater than m.
    return (x + m) % m; // convert x to x > 0.
  else // if a and m are coprime, unsolvable.
    return 0;
}

bool invMod_verify(void) {
  int a, b, c;
  // find x, s.t. x*7 = 1 (mod 9)
  a = invMod(7, 9);
  assert(a == 4);

  b = invMod(1, 1);
  // any integer leave its module by 1.
  assert(b == 0);

  // The numbers are not coprime.
  c = invMod(6, 4);
  assert(c == 0);
  return true;
}


int powMod(int x, int k, int m) {
  if (k == 0)     return 1;
  if (k % 2 == 0) return powMod(x*x % m, k/2, m);
  else            return x*powMod(x, k-1, m) % m;
}

bool powMod_verify(void) {
  int r = powMod(12, 5, 19);
  if (r != 8)
    assert(false);
  r = powMod(1, 12, 9);
  if (r != 1)
    assert(false);
  return true;
}


/*
  ???
  file:///Users/suztomo/Library/Application%20Support/Firefox/Profiles/m51vomto.default/ScrapBook/data/20090205181421/isprime.html
 */
bool suspect(int a, int s, int d, int n) {
  /* What is powmod */
  Int x;
  x= powMod(a, d, n);
  if (x == 1) return true;
  for (int r = 0; r < s; ++r) {
    if (x == n - 1) return true;
    x = x * x % n;
  }
  return false;
}

// {2,7,61,-1}                 is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^16 (at least)
bool isPrime(int n) {
  if (n <= 1 || (n > 2 && n % 2 == 0)) return false;

  // Famous primes, -1 means the end of array.
  int test[] = {2,3,5,7,11,13,17,19,23,-1};
  int d = n - 1, s = 0;
  // The number of division d by 2 is recorded in s.
  while (d % 2 == 0) ++s, d /= 2;

  for (int i = 0; test[i] < n && test[i] != -1; ++i)
    if (!suspect(test[i], s, d, n))
      return false; // most of them are true?
  return true;
}


bool isGaussianPrime(Int a, Int b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  if (a == 0) return b % 4 == 3 && isPrime(b);
  if (b == 0) return a % 4 == 3 && isPrime(a);
  return isPrime(a*a+b*b);
}


/*
  Sieve of eratosthenes.
  decide a number is a prime or not.
 */
vector<int> sieve_of_eratosthenes(int n) {
  vector<int> sieve(n, 1);
  for (int i=2; i<n; i++)
    for (int j=i; j<n; j+=i)
      sieve[j] = 0;
  return sieve;
}

bool sieve_verify(void) {
  int sieve_num = 1000;
  vector<int> sieve = sieve_of_eratosthenes(sieve_num);
  for(int i=1; i<sieve_num; ++i)
    if (sieve[i])
      for (int j=2; j<sieve_num; j++)
        if (i%j == 0)
          assert(0);
  return true;
}


/*
  used to confirm the all variables are the same.
 */
#include <cstdarg>
bool allDifference(int n, ...) {
  va_list args;
  va_start(args, n);
  int s[10];
  for(int i=0; i<n; ++i)
    s[i] = va_arg(args, int);
  for (int j=0; j<n; ++j)
    for (int i=j+1; i<n; ++i)
      if (s[i] == s[j])
        return false;
  va_end(args);
  return true;
}

bool allDifference_verify(void) {
  assert(allDifference(5, 1, 3, 3, 2, 5) == false);
  assert(allDifference(3, 1, 2, 3) == true);
  assert(allDifference(8, 1, 3, 5, 2, 4, 9, 7, 12) == true);
  return true;
}

#define C_N 10
#define REP(a, b) for (size_t (a) = 0; (a)<(size_t)(b); ++(a))

Int triangle[C_N+1][C_N+1];

void C_init() {
  REP(i, C_N+1)
    triangle[i][0] = 1, triangle[0][i] = 1;
  REP(i, C_N+1) REP(j, C_N+1) {
    if (i * j == 0) continue;
    triangle[i][j] = triangle[i-1][j] + triangle[i][j-1];
  }
}

Int C(int n, int k) {
  return triangle[n-k][k];
}

bool C_verify(void) {
  Int r;
  C_init();
  r = C(3, 1);
  assert(r == 3);
  assert(C(5, 2) == 10);
  assert(C(10, 0) == 1);
  assert(C(10, 5) == 252);
  assert(C(10, 10) == 1);
  return true;
}

int main() {
  if (gcd_verify()) cout << "gcd ok." << endl;
  if (sieve_verify()) cout << "eratosthenes ok." << endl;
  if (powMod_verify()) cout << "powMod ok." << endl;
  if (invMod_verify()) cout << "invMod ok." << endl;
  if (allDifference_verify()) cout << "allDifference ok." << endl;
  if (C_verify()) cout << "Combination ok." << endl;
  return 0;
}
