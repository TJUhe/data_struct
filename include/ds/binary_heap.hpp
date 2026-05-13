#pragma once

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
public:
    BinaryHeap() = default;

    explicit BinaryHeap(std::vector<T> values)
        : data_(std::move(values)) {
        heapify();
    }

    void push(const T& value) {
        data_.push_back(value);
        sift_up(data_.size() - 1);
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop on empty heap");
        }
        T top_value = data_.front();
        data_.front() = std::move(data_.back());
        data_.pop_back();
        if (!empty()) {
            sift_down(0);
        }
        return top_value;
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top on empty heap");
        }
        return data_.front();
    }

    [[nodiscard]] bool empty() const noexcept {
        return data_.empty();
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return data_.size();
    }

    [[nodiscard]] const std::vector<T>& raw() const noexcept {
        return data_;
    }

private:
    static std::size_t parent(std::size_t index) noexcept {
        return (index - 1) / 2;
    }

    static std::size_t left(std::size_t index) noexcept {
        return index * 2 + 1;
    }

    static std::size_t right(std::size_t index) noexcept {
        return index * 2 + 2;
    }

    bool higher_priority(const T& lhs, const T& rhs) const {
        return compare_(rhs, lhs);
    }

    void sift_up(std::size_t index) {
        while (index > 0) {
            std::size_t p = parent(index);
            if (!higher_priority(data_[index], data_[p])) {
                break;
            }
            std::swap(data_[index], data_[p]);
            index = p;
        }
    }

    void sift_down(std::size_t index) {
        while (true) {
            std::size_t best = index;
            const std::size_t l = left(index);
            const std::size_t r = right(index);

            if (l < data_.size() && higher_priority(data_[l], data_[best])) {
                best = l;
            }
            if (r < data_.size() && higher_priority(data_[r], data_[best])) {
                best = r;
            }
            if (best == index) {
                break;
            }
            std::swap(data_[index], data_[best]);
            index = best;
        }
    }

    void heapify() {
        if (data_.empty()) {
            return;
        }
        for (std::size_t i = data_.size() / 2; i > 0; --i) {
            sift_down(i - 1);
        }
    }

    std::vector<T> data_;
    Compare compare_;
};

} // namespace ds

