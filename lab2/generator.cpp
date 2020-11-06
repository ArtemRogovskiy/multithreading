#include <iostream>
#include <fstream>

void generate_matrix(int &m, int &n, const std::string &matrix_file, const std::string &approximation_file);

int main() {
    int m;
    std::cout << "Input matrix dimension M for matrix of coefficients: " << std::endl;
    std::cin >> m;
    int n = m + 1;
    generate_matrix(m, n, "coefficients_of_equations.txt", "initial_approximations.txt");

    return 0;
}

void generate_matrix(int &m, int &n, const std::string &matrix_file, const std::string &approximation_file) {
    std::ofstream outaf;
    std::ofstream outx;
    outaf.open("/home/artem/dev/cpp/projects/multithreading/lab2/" + matrix_file);
    outx.open("/home/artem/dev/cpp/projects/multithreading/lab2/" + approximation_file);
    outaf << m << " " << n << std::endl;
    outx << m << std::endl;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            int val = -20 + (std::rand() % (-20 - 100 + 1));
            if (val == 0) val = 1;
            if (i == j) val *= 2000;
            if (j == n - 1) {
                outx << val << std::endl;
            }
            outaf << val << " ";
        }
        outaf << std::endl;
    }
    outaf.close();
    outx.close();
}

