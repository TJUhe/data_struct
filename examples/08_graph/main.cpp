#include "ds/graph.hpp"

#include <iostream>
#include <vector>

void print(const char* title, const std::vector<int>& values) {
    std::cout << title << ": ";
    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    ds::WeightedGraph graph(6);
    graph.add_undirected_edge(0, 1, 7);
    graph.add_undirected_edge(0, 2, 9);
    graph.add_undirected_edge(0, 5, 14);
    graph.add_undirected_edge(1, 2, 10);
    graph.add_undirected_edge(1, 3, 15);
    graph.add_undirected_edge(2, 3, 11);
    graph.add_undirected_edge(2, 5, 2);
    graph.add_undirected_edge(3, 4, 6);
    graph.add_undirected_edge(4, 5, 9);

    print("BFS from 0", graph.bfs(0));
    print("DFS from 0", graph.dfs(0));
    print("Dijkstra distance from 0", graph.dijkstra(0));
    return 0;
}

