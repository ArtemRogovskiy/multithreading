#include "mpi.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

void read_data();

void write_result();

void quicksort(int *array, int size);

void quicksortMPI(int *array, int arrayIntialSize, int rank, int numsProcess);


int *arrayData;
int length, size, rank;

int main() {

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        read_data();
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    auto start = std::chrono::high_resolution_clock::now();

    if (size == 1) {
        quicksort(arrayData, length);
    } else {
        quicksortMPI(arrayData, length, rank, size);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
        write_result();
    }
    MPI_Finalize();

    return 0;
}

void read_data() {
    std::fstream stream("/home/artem/dev/cpp/projects/multithreading/lab3/input.txt", std::ios_base::in);
    stream >> length;
    arrayData = new int[length];
    for (int i = 0; i < length; ++i) {
        stream >> arrayData[i];
    }
}

void write_result() {
    std::ofstream outfile;
    outfile.open("/home/artem/dev/cpp/projects/multithreading/lab3/result.txt");
    for (int i = 0; i < length; ++i) {
        outfile << arrayData[i] << std::endl;
    }
    outfile.close();
}