#include "ds/dynamic_array.hpp"

#include <iostream>
#include <string>

template <typename T>
void print(const ds::DynamicArray<T>& array) {
    std::cout << "[ ";
    for (const auto& value : array) {
        std::cout << value << ' ';
    }
    std::cout << "] size=" << array.size()
              << " capacity=" << array.capacity() << '\n';
}

int main() {
    ds::DynamicArray<std::string> tasks;
    print(tasks);

    tasks.push_back("learn contiguous memory");
    tasks.push_back("understand capacity");
    tasks.push_back("practice insert");
    tasks.push_back("practice erase");
    print(tasks);

    tasks.insert(1, "observe shifting cost");
    print(tasks);

    std::cout << "removed: " << tasks.erase(2) << '\n';
    print(tasks);

    std::cout << "Random access is fast: tasks[1] = " << tasks[1] << '\n';
    return 0;
}

