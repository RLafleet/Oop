#include <iostream>
#include <fstream>

void generateTestProgram(const std::string& filename, int n) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    file << "Added a let: x = 1\n";
    for (int i = 2; i <= n; ++i) {
        file << "Added a function: x = x" << (i - 1) << "\n";
    }
}

int main() {
    generateTestProgram("test_output.txt", 1000000);
    return 0;
}
