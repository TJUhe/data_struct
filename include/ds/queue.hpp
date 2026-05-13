#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

template <typename T>
class CircularQueue {
public:
    explicit CircularQueue(std::size_t capacity = 8)
        : data_(capacity + 1) {
        if (capacity == 0) {
            throw std::invalid_argument("queue capacity must be positive");
        }
    }

    void push(const T& value) {
        if (full()) {
            grow();
        }
        data_[tail_] = value;
        tail_ = next(tail_);
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop on empty queue");
        }
        T value = std::move(data_[head_]);
        head_ = next(head_);
        return value;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("front on empty queue");
        }
        return data_[head_];
    }

    [[nodiscard]] bool empty() const noexcept {
        return head_ == tail_;
    }

    [[nodiscard]] bool full() const noexcept {
        return next(tail_) == head_;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        if (tail_ >= head_) {
            return tail_ - head_;
        }
        return data_.size() - head_ + tail_;
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return data_.size() - 1;
    }

private:
    std::size_t next(std::size_t index) const noexcept {
        return (index + 1) % data_.size();
    }

    void grow() {
        std::vector<T> next_data(data_.size() * 2);
        const std::size_t old_size = size();
        for (std::size_t i = 0; i < old_size; ++i) {
            next_data[i] = std::move(data_[(head_ + i) % data_.size()]);
        }
        data_ = std::move(next_data);
        head_ = 0;
        tail_ = old_size;
    }

    std::vector<T> data_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
};

} // namespace ds

