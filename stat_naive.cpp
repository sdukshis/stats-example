#include <iostream>
#include <iomanip>

int main() {
    double sum = 0.0;
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();
    size_t count = 0;

    double val;
    while (std::cin >> val) {
        sum += val;
        min = std::min(min, val);
        max = std::max(max, val);
        ++count;
    }
    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }
    // Print results if any
    if (count > 0) {
        std::cout << std::setw(8) << sum / count
                  << std::setw(8) << min 
                  << std::setw(8) << max << '\n';
    }
    return 0;
}