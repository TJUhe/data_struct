#pragma once

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <list>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
public:
    explicit HashTable(std::size_t bucket_count = 8)
        : buckets_(bucket_count) {
        if (bucket_count == 0) {
            throw std::invalid_argument("bucket_count must be positive");
        }
    }

    void insert_or_assign(const Key& key, const Value& value) {
        if (load_factor() > 0.75) {
            rehash(buckets_.size() * 2);
        }

        auto& bucket = bucket_for(key);
        for (auto& item : bucket) {
            if (item.first == key) {
                item.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        ++size_;
    }

    bool erase(const Key& key) {
        auto& bucket = bucket_for(key);
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    Value* find(const Key& key) {
        auto& bucket = bucket_for(key);
        for (auto& item : bucket) {
            if (item.first == key) {
                return &item.second;
            }
        }
        return nullptr;
    }

    const Value* find(const Key& key) const {
        const auto& bucket = bucket_for(key);
        for (const auto& item : bucket) {
            if (item.first == key) {
                return &item.second;
            }
        }
        return nullptr;
    }

    Value& at(const Key& key) {
        Value* value = find(key);
        if (value == nullptr) {
            throw std::out_of_range("key not found");
        }
        return *value;
    }

    [[nodiscard]] bool contains(const Key& key) const {
        return find(key) != nullptr;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] std::size_t bucket_count() const noexcept {
        return buckets_.size();
    }

    [[nodiscard]] double load_factor() const noexcept {
        return static_cast<double>(size_) / static_cast<double>(buckets_.size());
    }

private:
    using Entry = std::pair<Key, Value>;
    using Bucket = std::list<Entry>;

    Bucket& bucket_for(const Key& key) {
        return buckets_[hasher_(key) % buckets_.size()];
    }

    const Bucket& bucket_for(const Key& key) const {
        return buckets_[hasher_(key) % buckets_.size()];
    }

    void rehash(std::size_t next_bucket_count) {
        std::vector<Bucket> old = std::move(buckets_);
        buckets_ = std::vector<Bucket>(next_bucket_count);
        size_ = 0;
        for (const auto& bucket : old) {
            for (const auto& [key, value] : bucket) {
                insert_or_assign(key, value);
            }
        }
    }

    std::vector<Bucket> buckets_;
    std::size_t size_ = 0;
    Hash hasher_;
};

} // namespace ds

