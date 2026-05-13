#include "ds/linked_list.hpp"

#include <iostream>
#include <string>

template <typename T>
void print(const ds::SinglyLinkedList<T>& list) {
    std::cout << "[ ";
    list.for_each([](const auto& value) {
        std::cout << value << ' ';
    });
    std::cout << "] size=" << list.size() << '\n';
}

int main() {
    ds::SinglyLinkedList<std::string> playlist;
    playlist.push_back("intro");
    playlist.push_back("array");
    playlist.push_back("linked list");
    playlist.push_front("warm up");
    print(playlist);

    playlist.remove_first("array");
    print(playlist);

    playlist.reverse();
    print(playlist);

    std::cout << "pop front: " << playlist.pop_front() << '\n';
    print(playlist);
    return 0;
}

