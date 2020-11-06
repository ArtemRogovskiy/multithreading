#include <fstream>
#include <chrono>
#include <iostream>
#include <mpi.h>

void read_A_and_F(std::fstream &data, double *matrix, double *vector, int &m, int &n);

void read_X(std::fstream &data, double *array, int &m);

void jacobi(int N, double *X, int bloc_size, int rank, double *A_bloc, double *F_bloc,
            double *X_bloc);

void write_result(double *array, int &m);

int main() {
//    MPI_Status status;
    int rank, procnum;
    double *A, *F, *X; // AX = F
    double *A_bloc, *F_bloc, *X_bloc;
    int m, n, k, block_size;


    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procnum);


    if (rank == 0) {
        std::fstream readaf(
                "/home/artem/dev/cpp/projects/multithreading/lab2/coefficients_of_equations.txt", std::ios_base::in);
        std::fstream readx(
                "/home/artem/dev/cpp/projects/multithreading/lab2/initial_approximations.txt", std::ios_base::in);
        readaf >> m >> n; // n = m + 1
        readx >> k; // k = m

        A = new double[m * m];
        F = new double[m];
        X = new double[m];
        read_A_and_F(readaf, A, F, m, n); // Read data from file "coefficients_of_equations.txt"
        read_X(readx, X, k); // Read data from file "initial_approximations.txt"
        readaf.close();
        readx.close();

    }

    auto start = std::chrono::high_resolution_clock::now();

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        X = new double[m];
    }

    MPI_Bcast(X, m, MPI_INT, 0, MPI_COMM_WORLD);

    if(n != m + 1) {
        MPI_Finalize();
        if(rank == 0){
            std::cout << "Wrong input matrix dimensions: n must be equals m+1" << std::endl;
        }
        exit(-1);
    }

    if(m != k) {
        MPI_Finalize();
        if(rank == 0){
            std::cout << "Wrong input approximation vector dimension: k must be equals m" << std::endl;
        }
        exit(-1);
    }

    if(m % procnum != 0) {
        MPI_Finalize();
        if(rank == 0){
            std::cout << "Matrix can not be striped evenly" << std::endl;
        }
        exit(-1);
    }

    block_size = m / procnum; // Every process will processed own block

    A_bloc = new double[block_size * m];
    F_bloc = new double[block_size];
    X_bloc = new double[block_size];

    /*......Scatter the Input Data to all process ......*/
    MPI_Scatter (A, block_size * m, MPI_DOUBLE, A_bloc, block_size * m,
                 MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter (F, block_size, MPI_DOUBLE, F_bloc, block_size, MPI_DOUBLE, 0,
                 MPI_COMM_WORLD);


    jacobi(m, X, block_size, rank, A_bloc, F_bloc, X_bloc);

    if (rank == 0) {
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";

        write_result(X, m);
    }

    MPI_Finalize();

    return 0;
}

void read_A_and_F(std::fstream &data, double *matrix, double *vector, int &m, int &n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == n - 1) {
                data >> vector[i];
            } else {
                data >> matrix[i*m + j];
            }
        }
    }
}

void read_X(std::fstream &data, double *array, int &m) {
    for (int i = 0; i < m; ++i) {
        data >> array[i];
    }
}

void write_result(double *array, int &m) {
    std::ofstream outfile;
    outfile.open("/home/artem/dev/cpp/projects/multithreading/lab2/result.txt");
    for (int i = 0; i < m; ++i) {
        outfile << array[i] << std::endl;
    }
    outfile.close();
}

