#include "ds/sorting.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void print(const char* title, const std::vector<T>& values) {
    std::cout << title << ": ";
    for (const auto& value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> a{9, 4, 6, 2, 8, 1, 5, 3, 7};
    std::vector<int> b = a;
    std::vector<int> c = a;

    ds::insertion_sort(a.begin(), a.end());
    ds::quick_sort(b.begin(), b.end());
    ds::merge_sort(c.begin(), c.end());

    print("insertion_sort", a);
    print("quick_sort    ", b);
    print("merge_sort    ", c);

    std::vector<std::string> names{"Ada", "Bjarne", "Dennis", "Grace"};
    ds::merge_sort(names.begin(), names.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.size() < rhs.size();
    });
    print("by name length", names);
    return 0;
}

