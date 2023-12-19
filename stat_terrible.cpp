#include <iostream>
#include <iomanip>
#include <string>

struct options {
    bool calc_mean = false;
    bool calc_min = false;
    bool calc_max = false;
};

bool parse_args(int argc, char *argv[], options& opts);

int main(int argc, char *argv[]) {
    options opts;
    if (!parse_args(argc, argv, opts)) {
        std::cerr << "Error parsing command line options\n";
        return 1;
    }
    double sum = 0.0;
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();
    size_t count = 0;

    double val;
    while (std::cin >> val) {
        if (opts.calc_mean)
            sum += val;
        if (opts.calc_min)
            min = std::min(min, val);
        if (opts.calc_max)
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
        if (opts.calc_mean) {
            std::cout << std::setw(8) << sum / count;
        }
        if (opts.calc_min) {
            std::cout << std::setw(8) << min;
        }
        if (opts.calc_max) {
            std::cout << std::setw(8) << max;
        }
        std::cout << '\n'; 
    }
    return 0;
}

bool parse_args(int argc, char *argv[], options& opts) {
    using namespace std::literals;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "mean"sv) {
            opts.calc_mean = true;
        } else if (argv[i] == "min"sv) {
            opts.calc_min =  true;
        } else if (argv[i] == "max"sv) {
            opts.calc_max = true;
        } else {
            std::cerr << "Unknown cmd option: '" << argv[i] << "'\n";
            return false;
        }
    }
    return true;
}
