#include "ds/binary_search_tree.hpp"

#include <iostream>
#include <vector>

int main() {
    ds::BinarySearchTree<int> tree;
    for (int value : {8, 3, 10, 1, 6, 14, 4, 7, 13}) {
        tree.insert(value);
    }

    std::cout << "inorder means sorted for a binary search tree: ";
    tree.inorder([](int value) { std::cout << value << ' '; });

    std::cout << "\npreorder shows root-before-children shape: ";
    tree.preorder([](int value) { std::cout << value << ' '; });

    std::cout << "\ncontains 7? " << std::boolalpha << tree.contains(7);
    std::cout << "\nheight=" << tree.height() << " size=" << tree.size() << '\n';

    tree.erase(3);
    std::cout << "after erase(3), inorder: ";
    tree.inorder([](int value) { std::cout << value << ' '; });
    std::cout << '\n';
    return 0;
}

