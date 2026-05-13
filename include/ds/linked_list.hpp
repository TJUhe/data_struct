#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace ds {

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T value;
        Node* next = nullptr;

        explicit Node(const T& value) : value(value) {}
        explicit Node(T&& value) : value(std::move(value)) {}
    };

public:
    SinglyLinkedList() = default;

    SinglyLinkedList(std::initializer_list<T> values) {
        for (const auto& value : values) {
            push_back(value);
        }
    }

    SinglyLinkedList(const SinglyLinkedList& other) {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push_back(cur->value);
        }
    }

    SinglyLinkedList& operator=(SinglyLinkedList other) noexcept {
        swap(other);
        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept {
        swap(other);
    }

    ~SinglyLinkedList() {
        clear();
    }

    void push_front(const T& value) {
        Node* node = new Node(value);
        node->next = head_;
        head_ = node;
        if (tail_ == nullptr) {
            tail_ = head_;
        }
        ++size_;
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front on empty list");
        }
        Node* old_head = head_;
        T value = std::move(old_head->value);
        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
        delete old_head;
        --size_;
        return value;
    }

    bool remove_first(const T& value) {
        Node* prev = nullptr;
        Node* cur = head_;
        while (cur != nullptr) {
            if (cur->value == value) {
                if (prev == nullptr) {
                    head_ = cur->next;
                } else {
                    prev->next = cur->next;
                }
                if (tail_ == cur) {
                    tail_ = prev;
                }
                delete cur;
                --size_;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void reverse() noexcept {
        tail_ = head_;
        Node* prev = nullptr;
        Node* cur = head_;
        while (cur != nullptr) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head_ = prev;
    }

    bool contains(const T& value) const noexcept {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            if (cur->value == value) {
                return true;
            }
        }
        return false;
    }

    void clear() noexcept {
        while (head_ != nullptr) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    template <typename Visitor>
    void for_each(Visitor visitor) const {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            visitor(cur->value);
        }
    }

    void swap(SinglyLinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};

} // namespace ds

