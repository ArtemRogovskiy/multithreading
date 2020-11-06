#include <math.h>
#include <iostream>
#include <mpi.h>

const double eps = 0.1; ///< желаемая точность

void jacobi(int N, double *A, double *F, double *X, int bloc_size, int rank, double *A_bloc, double *F_bloc,
            double *X_bloc) {
    double *TempX = new double[N];
    double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.

    do {
        for (int i = 0; i < N; ++i) {
            TempX[i] = X[i];
        }

        for (int i = 0; i < bloc_size; ++i) {

            int GlobalRowNo = rank * bloc_size + i;
            X_bloc[i] = F_bloc[i];
            int index = i * N;

            for (int j = 0; j < GlobalRowNo; ++j) {
                X_bloc[i] -= A_bloc[index + j] * X[j];
            }
            for (int j = GlobalRowNo + 1; j < N; ++j) {
                X_bloc[i] -= A_bloc[index + j] * X[j];
            }
            X_bloc[i] /= A_bloc[index + GlobalRowNo];
        }

        MPI_Allgather(X_bloc, bloc_size, MPI_DOUBLE, X,
                      bloc_size, MPI_DOUBLE, MPI_COMM_WORLD);

        norm = fabs(X[0] - TempX[0]);
        for (int h = 0; h < N; ++h) {
            if (fabs(X[h] - TempX[h]) > norm)
                norm = fabs(X[h] - TempX[h]);
        }
    } while (norm > eps);
    delete[] TempX;
}

