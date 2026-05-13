#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace ds {

template <typename T, typename Compare = std::less<T>>
class BinarySearchTree {
private:
    struct Node {
        T value;
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(const T& value) : value(value) {}
    };

public:
    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree& other) {
        root_ = clone(other.root_);
        size_ = other.size_;
    }

    BinarySearchTree& operator=(BinarySearchTree other) noexcept {
        swap(other);
        return *this;
    }

    BinarySearchTree(BinarySearchTree&& other) noexcept {
        swap(other);
    }

    ~BinarySearchTree() {
        clear(root_);
    }

    bool insert(const T& value) {
        bool inserted = false;
        root_ = insert(root_, value, inserted);
        if (inserted) {
            ++size_;
        }
        return inserted;
    }

    bool contains(const T& value) const noexcept {
        Node* cur = root_;
        while (cur != nullptr) {
            if (compare_(value, cur->value)) {
                cur = cur->left;
            } else if (compare_(cur->value, value)) {
                cur = cur->right;
            } else {
                return true;
            }
        }
        return false;
    }

    bool erase(const T& value) {
        bool removed = false;
        root_ = erase(root_, value, removed);
        if (removed) {
            --size_;
        }
        return removed;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] int height() const noexcept {
        return height(root_);
    }

    template <typename Visitor>
    void inorder(Visitor visitor) const {
        inorder(root_, visitor);
    }

    template <typename Visitor>
    void preorder(Visitor visitor) const {
        preorder(root_, visitor);
    }

    template <typename Visitor>
    void postorder(Visitor visitor) const {
        postorder(root_, visitor);
    }

    void swap(BinarySearchTree& other) noexcept {
        std::swap(root_, other.root_);
        std::swap(size_, other.size_);
    }

private:
    Node* insert(Node* node, const T& value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(value);
        }
        if (compare_(value, node->value)) {
            node->left = insert(node->left, value, inserted);
        } else if (compare_(node->value, value)) {
            node->right = insert(node->right, value, inserted);
        }
        return node;
    }

    Node* erase(Node* node, const T& value, bool& removed) {
        if (node == nullptr) {
            return nullptr;
        }
        if (compare_(value, node->value)) {
            node->left = erase(node->left, value, removed);
            return node;
        }
        if (compare_(node->value, value)) {
            node->right = erase(node->right, value, removed);
            return node;
        }

        removed = true;
        if (node->left == nullptr) {
            Node* right = node->right;
            delete node;
            return right;
        }
        if (node->right == nullptr) {
            Node* left = node->left;
            delete node;
            return left;
        }

        Node* successor = min_node(node->right);
        node->value = successor->value;
        bool ignored = false;
        node->right = erase(node->right, successor->value, ignored);
        return node;
    }

    Node* min_node(Node* node) const noexcept {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    static Node* clone(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* copied = new Node(node->value);
        copied->left = clone(node->left);
        copied->right = clone(node->right);
        return copied;
    }

    static void clear(Node* node) noexcept {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    static int height(Node* node) noexcept {
        if (node == nullptr) {
            return 0;
        }
        const int left = height(node->left);
        const int right = height(node->right);
        return 1 + (left > right ? left : right);
    }

    template <typename Visitor>
    static void inorder(Node* node, Visitor visitor) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, visitor);
        visitor(node->value);
        inorder(node->right, visitor);
    }

    template <typename Visitor>
    static void preorder(Node* node, Visitor visitor) {
        if (node == nullptr) {
            return;
        }
        visitor(node->value);
        preorder(node->left, visitor);
        preorder(node->right, visitor);
    }

    template <typename Visitor>
    static void postorder(Node* node, Visitor visitor) {
        if (node == nullptr) {
            return;
        }
        postorder(node->left, visitor);
        postorder(node->right, visitor);
        visitor(node->value);
    }

    Node* root_ = nullptr;
    std::size_t size_ = 0;
    Compare compare_;
};

} // namespace ds

