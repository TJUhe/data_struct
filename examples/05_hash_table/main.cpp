#include "ds/hash_table.hpp"

#include <iostream>
#include <string>

int main() {
    ds::HashTable<std::string, int> word_count;

    for (const std::string word : {"tree", "graph", "tree", "hash", "tree", "graph"}) {
        int current = 0;
        if (auto* old = word_count.find(word)) {
            current = *old;
        }
        word_count.insert_or_assign(word, current + 1);
    }

    for (const std::string word : {"tree", "graph", "hash", "heap"}) {
        if (auto* count = word_count.find(word)) {
            std::cout << word << " appears " << *count << " time(s)\n";
        } else {
            std::cout << word << " is not present\n";
        }
    }

    std::cout << "size=" << word_count.size()
              << " buckets=" << word_count.bucket_count()
              << " load_factor=" << word_count.load_factor() << '\n';
    return 0;
}

