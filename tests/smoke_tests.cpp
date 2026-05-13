#include "ds/binary_heap.hpp"
#include "ds/binary_search_tree.hpp"
#include "ds/dynamic_array.hpp"
#include "ds/graph.hpp"
#include "ds/hash_table.hpp"
#include "ds/linked_list.hpp"
#include "ds/lru_cache.hpp"
#include "ds/queue.hpp"
#include "ds/sorting.hpp"
#include "ds/stack.hpp"

#include <cassert>
#include <string>
#include <vector>

int main() {
    ds::DynamicArray<int> array{1, 2, 4};
    array.insert(2, 3);
    assert(array.size() == 4);
    assert(array[2] == 3);
    assert(array.erase(1) == 2);

    ds::SinglyLinkedList<int> list{1, 2, 3};
    list.reverse();
    assert(list.pop_front() == 3);
    assert(list.contains(1));

    ds::Stack<int> stack;
    stack.push(10);
    stack.push(20);
    assert(stack.pop() == 20);

    ds::CircularQueue<int> queue(2);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    assert(queue.pop() == 1);
    assert(queue.pop() == 2);
    assert(queue.pop() == 3);

    ds::HashTable<std::string, int> table;
    table.insert_or_assign("cpp", 20);
    assert(table.at("cpp") == 20);

    ds::BinarySearchTree<int> tree;
    for (int value : {5, 2, 7, 1, 3}) {
        tree.insert(value);
    }
    assert(tree.contains(3));
    assert(tree.erase(2));

    ds::BinaryHeap<int> heap;
    heap.push(3);
    heap.push(9);
    heap.push(1);
    assert(heap.pop() == 9);

    ds::WeightedGraph graph(3);
    graph.add_undirected_edge(0, 1, 5);
    graph.add_undirected_edge(1, 2, 7);
    auto distance = graph.dijkstra(0);
    assert(distance[2] == 12);

    std::vector<int> values{4, 1, 3, 2};
    ds::merge_sort(values.begin(), values.end());
    assert((values == std::vector<int>{1, 2, 3, 4}));

    ds::LruCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    assert(cache.get(1).value() == "one");
    cache.put(3, "three");
    assert(!cache.contains(2));
    return 0;
}

