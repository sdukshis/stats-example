#include <iostream>

int main() {
    double sum = 0.0;
    size_t count = 0;

    double val;
    while (std::cin >> val) {
        sum += val;
        ++count;
    }
    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }
    // Print results if any
    if (count > 0) {
        std::cout << sum / count << '\n';
    }
    return 0;
}