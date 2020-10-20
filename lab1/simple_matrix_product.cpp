#include <cstddef>

void simple_matrix_product(int **A, int **B, int ** C, int &ma, int &inner, int &nb) {
    size_t i, j, k;
    for (i = 0; i < ma; ++i) {
        for (j = 0; j < nb; ++j) {
            for (k = 0; k < inner; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
