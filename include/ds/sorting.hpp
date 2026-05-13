#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

namespace ds {

template <typename RandomIt, typename Compare = std::less<>>
void insertion_sort(RandomIt first, RandomIt last, Compare compare = Compare{}) {
    for (auto it = first; it != last; ++it) {
        auto key = std::move(*it);
        auto hole = it;
        while (hole != first && compare(key, *(hole - 1))) {
            *hole = std::move(*(hole - 1));
            --hole;
        }
        *hole = std::move(key);
    }
}

template <typename RandomIt, typename Compare = std::less<>>
void quick_sort(RandomIt first, RandomIt last, Compare compare = Compare{}) {
    if (last - first <= 1) {
        return;
    }

    auto pivot = *(first + (last - first) / 2);
    auto left = first;
    auto right = last - 1;

    while (left <= right) {
        while (compare(*left, pivot)) {
            ++left;
        }
        while (compare(pivot, *right)) {
            --right;
        }
        if (left <= right) {
            std::iter_swap(left, right);
            ++left;
            --right;
        }
    }

    quick_sort(first, right + 1, compare);
    quick_sort(left, last, compare);
}

template <typename RandomIt, typename Compare = std::less<>>
void merge_sort(RandomIt first, RandomIt last, Compare compare = Compare{}) {
    const auto length = last - first;
    if (length <= 1) {
        return;
    }

    auto mid = first + length / 2;
    merge_sort(first, mid, compare);
    merge_sort(mid, last, compare);

    using Value = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<Value> merged;
    merged.reserve(static_cast<std::size_t>(length));

    auto left = first;
    auto right = mid;
    while (left != mid && right != last) {
        if (compare(*right, *left)) {
            merged.push_back(std::move(*right++));
        } else {
            merged.push_back(std::move(*left++));
        }
    }
    while (left != mid) {
        merged.push_back(std::move(*left++));
    }
    while (right != last) {
        merged.push_back(std::move(*right++));
    }
    std::move(merged.begin(), merged.end(), first);
}

} // namespace ds

