#include "Strassen.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>
const int N = 64;
int main() {
  srand(time(0));
  matrix<int> a(N, N), b(N, N);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      a[i][j] = rand() % 100, b[i][j] = rand() % 100;

  double start1 = clock();
  matrix<int> c = strassen(a, b);
  double end1 = clock();

  double start2 = clock();
  matrix<int> d = a.operator*(b);
  double end2 = clock();

  assert(c == d);
  std::cout << "Strassen: " << (end1 - start1) / CLOCKS_PER_SEC << std::endl;
  std::cout << "Naive: " << (end2 - start2) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
