#include <iostream>
#include <fstream>

void generate_array(int &m, const std::string &matrix_file);

int main() {
    int m;
    std::cout << "Input array length: " << std::endl;
    std::cin >> m;

    generate_array(m, "input.txt");

    return 0;
}

void generate_array(int &m, const std::string &file_name) {
    std::ofstream out;
    out.open("/home/artem/dev/cpp/projects/multithreading/lab3/" + file_name);

    out << m << std::endl;
    for (size_t i = 0; i < m; ++i) {
            int val = -10000 + (std::rand() % (10000 - (- 10000) + 1));
            out << val << " ";
    }

    out.close();
}

