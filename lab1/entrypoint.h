//
// Created by artem on 20.10.2020.
//

#ifndef MULTITHREADING_ENTRYPOINT_H
#define MULTITHREADING_ENTRYPOINT_H

void write_result(int **matrix, int &m, int &n);

void fill_matrix(std::fstream &data, int **matrix, int &m, int &n);

void fill_matrix_zeros(int **matrix, int &m, int &n);

void simple_matrix_product(int **A, int **B, int **C, int &ma, int &inner, int &nb);

void parallel_simple_matrix_product(int **A, int **B, int ** C, int &ma, int &inner, int &nb);

void simple_matrix_product_transposed(int **A, int **B, int ** C, int &ma, int &inner, int &nb);

void parallel_simple_matrix_product_transposed(int **A, int **B, int ** C, int &ma, int &inner, int &nb);

void matrix_multiplication(int **A, int **B, int **C, int m, int inner, int n, int BS);

void check_result_correctness();

#endif //MULTITHREADING_ENTRYPOINT_H
