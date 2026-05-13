#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace ds {

template <typename T>
class DynamicArray {
public:
    DynamicArray() = default;

    DynamicArray(std::initializer_list<T> values) {
        reserve(values.size());
        for (const auto& value : values) {
            push_back(value);
        }
    }

    DynamicArray(const DynamicArray& other) {
        reserve(other.size_);
        for (std::size_t i = 0; i < other.size_; ++i) {
            push_back(other.data_[i]);
        }
    }

    DynamicArray& operator=(DynamicArray other) noexcept {
        swap(other);
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept {
        swap(other);
    }

    ~DynamicArray() {
        delete[] data_;
    }

    void push_back(const T& value) {
        ensure_capacity_for_one_more();
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        ensure_capacity_for_one_more();
        data_[size_++] = std::move(value);
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("insert index is out of range");
        }
        ensure_capacity_for_one_more();
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = value;
        ++size_;
    }

    T erase(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("erase index is out of range");
        }
        T removed = std::move(data_[index]);
        for (std::size_t i = index + 1; i < size_; ++i) {
            data_[i - 1] = std::move(data_[i]);
        }
        --size_;
        return removed;
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index is out of range");
        }
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index is out of range");
        }
        return data_[index];
    }

    T& operator[](std::size_t index) noexcept {
        return data_[index];
    }

    const T& operator[](std::size_t index) const noexcept {
        return data_[index];
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        T* next = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            next[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = next;
        capacity_ = new_capacity;
    }

    void clear() noexcept {
        size_ = 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    T* begin() noexcept {
        return data_;
    }

    T* end() noexcept {
        return data_ + size_;
    }

    const T* begin() const noexcept {
        return data_;
    }

    const T* end() const noexcept {
        return data_ + size_;
    }

    void swap(DynamicArray& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    void ensure_capacity_for_one_more() {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 4 : capacity_ * 2);
        }
    }

    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};

} // namespace ds

