void matrix_multiplication(int **A, int **B, int **C, int m, int inner, int n, int BS) {
    int i, j, k, ii, jj, kk;
    for (i = 0; i < m; i += BS) {
        for (j = 0; j < n; j += BS) {
            for (k = 0; k < inner; k += BS) {
#pragma omp task private(ii, jj, kk)
                for (ii = i; ii < i + BS; ii++) {
                    for (jj = j; jj < j + BS; jj++) {
                        for (kk = k; kk < k + BS; kk++) {
                            C[ii][jj] = C[ii][jj] + A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

