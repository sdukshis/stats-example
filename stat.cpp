#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <thread>
#include <vector>
#include <algorithm>
#include <limits>

class Stats {
public:
    virtual ~Stats() {}
    virtual void update(double val) = 0;
    virtual double eval() const = 0;
    virtual std::string_view name() const = 0;
};

std::unique_ptr<Stats> create_stat_from_name(const std::string_view& name);

int main(int argc, char *argv[]) {
    std::vector<std::unique_ptr<Stats>> stats_ptrs;
    for (int i = 1; i < argc; ++i) {
        stats_ptrs.emplace_back(create_stat_from_name(argv[i]));
    }

    bool any_input = false;
    double val;
    while (std::cin >> val) {
        std::for_each(stats_ptrs.begin(), stats_ptrs.end(), [val](auto& stat_ptr) {
            stat_ptr->update(val);
        });
        any_input = true;
    }

    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }
    // Print results if any
    if (any_input) {
        std::for_each(stats_ptrs.begin(), stats_ptrs.end(), [](auto& stat_ptr) {
            std::cout << std::setw(8) << stat_ptr->eval();
        });
        std::cout << '\n';       
    }
    return 0;
}


class MeanStats: public Stats {
public:
    void update(double val) override {
        sum_ += val;
        ++count_;
    }
    double eval() const override {
        return sum_ / count_;
    }
    std::string_view name() const override {
        using namespace std::literals;
        return "mean"sv;
    }

private:
    double sum_ = 0.0;
    size_t count_ = 0;
};

class MinStats: public Stats {
public:
    void update(double val) override {
        min_ = std::min(min_, val);
    }
    double eval() const override {
        return min_;
    }
private:
    double min_ = std::numeric_limits<double>::max();
};

class MaxStats: public Stats {
public:
    void update(double val) override {
        max_ = std::max(max_, val);
    }
    double eval() const override {
        return max_;
    }
private:
    double max_ = std::numeric_limits<double>::min();
};



std::unique_ptr<Stats> create_stat_from_name(const std::string_view& name) {
    using namespace std::literals;
    if (name == "mean"sv) {
        return std::make_unique<MeanStats>();
    } else if (name == "min"sv) {
        return std::make_unique<MinStats>();
    } else if (name == "max"sv) {
        return std::make_unique<MaxStats>();
    }
    throw std::invalid_argument{"Unknown stat name: "s.append(name)};
}
