#pragma once

#include <cstddef>
#include <list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace ds {

template <typename Key, typename Value>
class LruCache {
public:
    explicit LruCache(std::size_t capacity)
        : capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("LRU cache capacity must be positive");
        }
    }

    void put(const Key& key, const Value& value) {
        auto found = index_.find(key);
        if (found != index_.end()) {
            found->second->second = value;
            touch(found->second);
            return;
        }

        if (items_.size() == capacity_) {
            const auto& old_key = items_.back().first;
            index_.erase(old_key);
            items_.pop_back();
        }

        items_.push_front({key, value});
        index_[key] = items_.begin();
    }

    std::optional<Value> get(const Key& key) {
        auto found = index_.find(key);
        if (found == index_.end()) {
            return std::nullopt;
        }
        touch(found->second);
        return found->second->second;
    }

    [[nodiscard]] bool contains(const Key& key) const {
        return index_.contains(key);
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return items_.size();
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return capacity_;
    }

    template <typename Visitor>
    void most_recent_to_oldest(Visitor visitor) const {
        for (const auto& [key, value] : items_) {
            visitor(key, value);
        }
    }

private:
    using Item = std::pair<Key, Value>;
    using Iterator = typename std::list<Item>::iterator;

    void touch(Iterator it) {
        items_.splice(items_.begin(), items_, it);
    }

    std::size_t capacity_;
    std::list<Item> items_;
    std::unordered_map<Key, Iterator> index_;
};

} // namespace ds

