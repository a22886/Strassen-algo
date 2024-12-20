# What this is

An implementation of Strassen's algorithm of matrix multiplication.

The **main.cpp** will output the running time of Strassen's algorithm and the naive multiplication. Note that although Strassen's algorithm is in theory $O(n^{2.81})$ which is faster than the simple $O(n^3)$, the constant factor is too large for it to perform better than the naive algorithm unless the matrices are abnormally big. The one implemented here seems to have an even larger constant.

# Strassen's algorithm

Original paper [Gaussian Elimination is not Optimal](https://gdz.sub.uni-goettingen.de/id/PPN362160546_0013?tify=%7B%22pages%22:%5B358%5D%7D).