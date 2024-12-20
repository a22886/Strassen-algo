#include <assert.h>
#include <iostream>
#include <string.h>
#include <utility>
#define Assert(x, msg)                                                         \
  if (!(x)) {                                                                  \
    std::cerr << msg << std::endl;                                             \
    exit(1);                                                                   \
  }
template <typename T>
// Matrix class with basic operations. Maybe not the best implementation but it
// works.
class matrix {
private:
  int row;
  int col;
  T** mat;

public:
  matrix() : row(0), col(0), mat(nullptr) {
    Assert(false, "Matrix must be initialized by size");
  }
  matrix(int r, int c) : row(r), col(c) {
    Assert(r > 0 && c > 0, "Size must be a positive integer");
    mat = new T*[r];
    for (int i = 0; i < r; i++)
      mat[i] = new T[c];
    for (int i = 0; i < r; i++)
      memset(mat[i], 0, c * sizeof(T));
  }
  matrix(matrix&& m) : row(m.row), col(m.col) {
    mat = m.mat;
    m.mat = nullptr;
    m.row = m.col = 0;
  }
  ~matrix() {
    for (int i = 0; i < row; i++)
      delete[] mat[i];
    delete[] mat;
  }

  T* operator[](int i) const { return mat[i]; }
  matrix operator+(matrix& m) {
    matrix res(row, col);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        res[i][j] = (*this)[i][j] + m[i][j];
    return res;
  }
  matrix operator-(matrix& m) {
    matrix res(row, col);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        res[i][j] = (*this)[i][j] - m[i][j];
    return res;
  }
  bool operator==(matrix& m) {
    if (row != m.size().first || col != m.size().second)
      return false;
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        if ((*this)[i][j] != m[i][j])
          return false;
    return true;
  }

  std::pair<int, int> size() { return {row, col}; }

  matrix submatrix(int _r, int _c, int r, int c) {
    matrix<T> sub(r, c);
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        sub[i][j] = (*this)[_r + i][_c + j];
    return sub;
  }
  void copy(matrix& m, int _r, int _c) {
    for (int i = 0; i < m.size().first && _r + i < row; i++)
      for (int j = 0; j < m.size().second && _c + j < col; j++)
        (*this)[_r + i][_c + j] = m[i][j];
  }
  void resize(int r, int c) {
    matrix that(r, c);
    that.copy(*this, 0, 0);
    mat = that.mat;
    row = r, col = c;
    that.mat = nullptr;
    that.row = that.col = 0;
  }
  void print() {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++)
        std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
  }
  matrix operator*(matrix& m) {
    Assert(mat != nullptr && m.mat != nullptr, "Matrix not initialized");
    Assert(col == m.size().first, "Matrix multiplication undefined");
    matrix res(row, m.size().second);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < m.size().second; j++)
        for (int k = 0; k < col; k++)
          res[i][j] += (*this)[i][k] * m[k][j];
    return res;
  }
};
