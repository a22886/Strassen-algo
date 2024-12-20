# Strassen-algo

An implementation of Strassen's algorithm of matrix multiplication.

The **main.cpp** will output the running time of Strassen's algorithm and the naive multiplication. Note that although Strassen's algorithm is in theory $O(n^2.81)$ which is faster than the simple $O(n^3)$, the constant factor is too large for it to perform better than the naive algorithm unless the matrices are abnormally big.