#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "entrypoint.h"

int **A;
int **B;
int **C; // Result of AxB
int ma, na, mb, nb; // Matrix A (ma x na), matrix B (mb x nb)

int main() {
    std::fstream reada("/home/artem/dev/cpp/projects/multithreading/lab1/matrixA.txt", std::ios_base::in);
    std::fstream readb("/home/artem/dev/cpp/projects/multithreading/lab1/matrixB.txt", std::ios_base::in);
    reada >> ma >> na;
    readb >> mb >> nb;

    if (na != mb)
        std::cout << "Can not multiply matrices with different inner dimension: " << na << " and " << mb << std::endl;

    A = new int *[ma];
    B = new int *[mb];
    C = new int *[ma];
    fill_matrix_zeros(C, ma, nb);
    fill_matrix(reada, A, ma, na); // Read data from file "matrixA.txt"
    fill_matrix(readb, B, mb, nb); // Read data from file "matrixB.txt"

    reada.close();
    readb.close();

    auto start = std::chrono::high_resolution_clock::now();

//    simple_matrix_product(A, B, C, ma, na, nb);
//    parallel_simple_matrix_product(A, B, C, ma, na, nb);
//    simple_matrix_product_transposed(A, B, C, ma, na, nb);
//    parallel_simple_matrix_product_transposed(A, B, C, ma, na, nb);
    matrix_multiplication(A, B, C, ma, na, nb, 200);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    // Write resulted matrix C into "result.txt"
    write_result(C, ma, nb);

    // Output to console if uncorrected matrices multiplication
    check_result_correctness();
    return 0;
}

void fill_matrix_zeros(int **matrix, int &m, int &n) {
    for (size_t i = 0; i < m; ++i) {
        matrix[i] = new int[n];
        std::fill(matrix[i], matrix[i] + n, 0);
    }
}

void fill_matrix(std::fstream &data, int **matrix, int &m, int &n) {
    for (size_t i = 0; i < m; ++i) {
        matrix[i] = new int[n];
        for (size_t j = 0; j < n; ++j) {
            data >> matrix[i][j];
        }
    }
}

void write_result(int **matrix, int &m, int &n) {
    std::ofstream outfile;
    outfile.open("/home/artem/dev/cpp/projects/multithreading/lab1/result.txt");
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            outfile << matrix[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
}

void check_result_correctness() {
    int **matrix = new int *[ma];
    fill_matrix_zeros(matrix, ma, nb);
    simple_matrix_product(A, B, matrix, ma, na, nb);
    std::fstream read("/home/artem/dev/cpp/projects/multithreading/lab1/result.txt", std::ios_base::in);
    int element;
    for (size_t i = 0; i < ma; ++i) {
        for (size_t j = 0; j < nb; ++j) {
            read >> element;
            if (element != matrix[i][j]) {
                std::cout << "Wrong result of AxB!" << std::endl;
                read.close();
                return;
            }
        }
    }
    read.close();
}



