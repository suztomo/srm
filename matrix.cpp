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

typedef double number;
const number eps = 1e-8;
typedef vector<number> array;
typedef vector<array> matrix;

// O( n )
matrix identity(int n) {
  matrix A(n, array(n));
  for (int i = 0; i < n; ++i) A[i][i] = 1;
  return A;
}
// O( n )
number inner_product(const array &a, const array &b) {
  number ans = 0;
  for (size_t i = 0; i < a.size(); ++i)
    ans += a[i] * b[i];
  return ans;
}
// O( n^2 )
array mul(const matrix &A, const array &x) {
  array y(A.size());
  for (size_t i = 0; i < A.size(); ++i)
    for (size_t j = 0; j < A[0].size(); ++j)
      y[i] = A[i][j] * x[j];
  return y;
}
// O( n^3 )
matrix mul(const matrix &A, const matrix &B) {
  matrix C(A.size(), array(B[0].size()));
  for (size_t i = 0; i < C.size(); ++i)
    for (size_t j = 0; j < C[i].size(); ++j)
      for (size_t k = 0; k < A[i].size(); ++k)
        C[i][j] += A[i][k] * B[k][j];
  return C;
}
// O( n^3 log e )
matrix pow(const matrix &A, int e) {
  return e == 0 ? identity(A.size())  :
     e % 2 == 0 ? pow(mul(A, A), e/2) : mul(A, pow(A, e-1));
}
// O( n^3 )
number det(matrix A) {
  const int n = A.size();
  number D = 1;
  for (int i = 0; i < n; ++i) {
    int pivot = i;
    for (int j = i+1; j < n; ++j)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[i]);
    D *= A[i][i] * (i != pivot ? -1 : 1);
    if (abs(A[i][i]) < eps) break;
    for(int j = i+1; j < n; ++j)
      for(int k = n-1; k >= i; --k)
        A[j][k] -= A[i][k] * A[j][i] / A[i][i];
  }
  return D;
}
// O(n)
number tr(const matrix &A) {
  number ans = 0;
  for (size_t i = 0; i < A.size(); ++i)
    ans += A[i][i];
  return ans;
}
// O( n^3 ).
int rank(matrix A) {
  const int n = A.size(), m = A[0].size();
  int r = 0;
  for (int i = 0; r < n && i < m; ++i) {
    int pivot = r;
    for (int j = r+1; j < n; ++j)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[r]);
    if (abs(A[r][i]) < eps) continue;
    for (int k = m-1; k >= i; --k)
      A[r][k] /= A[r][i];
    for(int j = r+1; j < n; ++j)
      for(int k = i; k < m; ++k)
        A[j][k] -= A[r][k] * A[j][i];
    ++r;
  }
  return r;
}
