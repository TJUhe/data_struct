#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

long long linear_sum(const std::vector<int>& data) {
    return std::accumulate(data.begin(), data.end(), 0LL);
}

long long quadratic_pair_count(const std::vector<int>& data) {
    long long count = 0;
    for (std::size_t i = 0; i < data.size(); ++i) {
        for (std::size_t j = i + 1; j < data.size(); ++j) {
            if ((data[i] + data[j]) % 7 == 0) {
                ++count;
            }
        }
    }
    return count;
}

template <typename Func>
void time_it(const char* name, Func func) {
    const auto begin = std::chrono::steady_clock::now();
    const auto result = func();
    const auto end = std::chrono::steady_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << std::left << std::setw(24) << name
              << "result=" << std::setw(12) << result
              << " time=" << ms.count() << "ms\n";
}

int main() {
    std::vector<int> small(10'000);
    std::vector<int> large(40'000);
    std::iota(small.begin(), small.end(), 1);
    std::iota(large.begin(), large.end(), 1);

    std::cout << "Big-O is about growth, not one exact number.\n\n";
    time_it("O(n), n=10k", [&] { return linear_sum(small); });
    time_it("O(n), n=40k", [&] { return linear_sum(large); });
    time_it("O(n^2), n=10k", [&] { return quadratic_pair_count(small); });
    time_it("O(n^2), n=40k", [&] { return quadratic_pair_count(large); });

    std::cout << "\nWhen n grows 4x, O(n) is roughly 4x, while O(n^2) is roughly 16x.\n";
    return 0;
}

