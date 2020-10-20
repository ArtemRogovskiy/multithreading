cmake_minimum_required(VERSION 3.15)
project(multithreading)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(multithreading entrypoint.cpp simple_matrix_product.cpp entrypoint.h parallel_simple_matrix_product.cpp
        simple_matrix_product_transposed.cpp parallel_simple_matrix_product_transposed.cpp  matrix_multiplication.cpp)
#add_executable(multithreading generateAB.cpp)
