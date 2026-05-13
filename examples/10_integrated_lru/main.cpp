#include "ds/lru_cache.hpp"

#include <iostream>
#include <string>

void print(ds::LruCache<int, std::string>& cache) {
    std::cout << "most recent -> oldest: ";
    cache.most_recent_to_oldest([](int key, const std::string& value) {
        std::cout << '(' << key << ':' << value << ") ";
    });
    std::cout << '\n';
}

int main() {
    ds::LruCache<int, std::string> cache(3);
    cache.put(1, "array");
    cache.put(2, "list");
    cache.put(3, "tree");
    print(cache);

    std::cout << "get(1): " << cache.get(1).value_or("<missing>") << '\n';
    print(cache);

    cache.put(4, "graph");
    print(cache);

    std::cout << "get(2): " << cache.get(2).value_or("<missing>") << '\n';
    std::cout << "Key 2 was evicted because it became least recently used.\n";
    return 0;
}

