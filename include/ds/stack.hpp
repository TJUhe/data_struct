#pragma once

#include "ds/dynamic_array.hpp"

#include <stdexcept>

namespace ds {

template <typename T>
class Stack {
public:
    void push(const T& value) {
        items_.push_back(value);
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop on empty stack");
        }
        return items_.erase(items_.size() - 1);
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("top on empty stack");
        }
        return items_[items_.size() - 1];
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top on empty stack");
        }
        return items_[items_.size() - 1];
    }

    [[nodiscard]] bool empty() const noexcept {
        return items_.empty();
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return items_.size();
    }

private:
    DynamicArray<T> items_;
};

} // namespace ds

