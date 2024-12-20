#include "matrix.h"

inline int nextPowerOf2(int n) {
  int p = 1;
  if (n && !(n & (n - 1)))
    return n;
  while (p < n)
    p <<= 1;
  return p;
}
template <typename T>
// Strassen algorithm for square matrix multiplication where size of matrix is
// power of 2. It is likely somebody else has implemented this before
// becasue github copilot seems to know this algorithm.
matrix<T> strassen2(matrix<T>& a, matrix<T>& b) {
  int n = a.size().first;
  matrix<T> res(n, n);
  if (n == 1) {
    res[0][0] = a[0][0] * b[0][0];
    return res;
  }
  matrix<T> a11 = a.submatrix(0, 0, n / 2, n / 2);
  matrix<T> a12 = a.submatrix(0, n / 2, n / 2, n / 2);
  matrix<T> a21 = a.submatrix(n / 2, 0, n / 2, n / 2);
  matrix<T> a22 = a.submatrix(n / 2, n / 2, n / 2, n / 2);

  matrix<T> b11 = b.submatrix(0, 0, n / 2, n / 2);
  matrix<T> b12 = b.submatrix(0, n / 2, n / 2, n / 2);
  matrix<T> b21 = b.submatrix(n / 2, 0, n / 2, n / 2);
  matrix<T> b22 = b.submatrix(n / 2, n / 2, n / 2, n / 2);

  matrix<T> M1 = b12 - b22;
  matrix<T> M2 = a11 + a12;
  matrix<T> M3 = a21 + a22;
  matrix<T> M4 = b21 - b11;
  matrix<T> M5 = a11 + a22;
  matrix<T> M6 = b11 + b22;
  matrix<T> M7 = a12 - a22;
  matrix<T> M8 = b21 + b22;
  matrix<T> M9 = a11 - a21;
  matrix<T> M10 = b11 + b12;

  matrix<T> I1 = strassen2(a11, M1);
  matrix<T> I2 = strassen2(M2, b22);
  matrix<T> I3 = strassen2(M3, b11);
  matrix<T> I4 = strassen2(a22, M4);
  matrix<T> I5 = strassen2(M5, M6);
  matrix<T> I6 = strassen2(M7, M8);
  matrix<T> I7 = strassen2(M9, M10);

  matrix<T> c11 = I5 + I4 - I2 + I6, c12 = I1 + I2, c21 = I3 + I4,
            c22 = I1 + I5 - I3 - I7;

  matrix<T> c(n, n);
  c.copy(c11, 0, 0);
  c.copy(c12, 0, n / 2);
  c.copy(c21, n / 2, 0);
  c.copy(c22, n / 2, n / 2);
  return c;
}
template <typename T>
// Strassen algorithm for arbitrary size matrix multiplication. Very likely not
// the best implementation.
matrix<T> strassen(matrix<T>& a, matrix<T>& b) {
  Assert(a.size().second == b.size().first, "Matrix multiplication undefined");
  int m = a.size().first, n = a.size().second, k = b.size().second;
  int size = std::max(std::max(m, n), k);
  int x = nextPowerOf2(size);
  a.resize(x, x), b.resize(x, x);
  return strassen2(a, b).submatrix(0, 0, m, k);
}
