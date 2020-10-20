#include <iostream>
#include <fstream>

void generate_matrix(int &m, int &n, std::string S);

int main() {
    int ma, na, mb, nb;
    std::cout << "Input matrix dimensions (MxN) for matrix A: " << std::endl;
    std::cin >> ma >> na;
    std::cout << "Input matrix dimensions (MxN) for matrix B: " << std::endl;
    std::cin >> mb >> nb;

    generate_matrix(ma, na, "A");
    generate_matrix(mb, nb, "B");

    return 0;
}

void generate_matrix(int &m, int &n, std::string S) {
    std::ofstream outfile;
    outfile.open("/home/artem/dev/cpp/projects/multithreading/lab1/matrix" + S + ".txt");
    outfile << m << " " << n << std::endl;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            outfile << -20 + (std::rand() % (-20 - 100 + 1)) << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
}

