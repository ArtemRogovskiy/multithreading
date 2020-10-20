#include <cstddef>

void simple_matrix_product_transposed(int **A, int **B, int ** C, int &ma, int &inner, int &nb) {

    // Transpose B
    int **BT = new int *[nb];
    for (size_t t = 0; t < nb; ++t) {
        BT[t] = new int[inner];
        for (size_t d = 0; d < inner; ++d) {
            BT[t][d] = B[d][t];
        }
    }

    size_t i, j, k;
    for (i = 0; i < ma; ++i) {
        for (j = 0; j < nb; ++j) {
            for (k = 0; k < inner; ++k) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}
