#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

class WeightedGraph {
public:
    struct Edge {
        int to;
        int weight;
    };

    explicit WeightedGraph(int vertex_count)
        : adjacency_(static_cast<std::size_t>(vertex_count)) {
        if (vertex_count < 0) {
            throw std::invalid_argument("vertex_count must not be negative");
        }
    }

    void add_directed_edge(int from, int to, int weight = 1) {
        validate(from);
        validate(to);
        if (weight < 0) {
            throw std::invalid_argument("this graph uses non-negative weights");
        }
        adjacency_[static_cast<std::size_t>(from)].push_back({to, weight});
    }

    void add_undirected_edge(int a, int b, int weight = 1) {
        add_directed_edge(a, b, weight);
        add_directed_edge(b, a, weight);
    }

    std::vector<int> bfs(int start) const {
        validate(start);
        std::vector<int> order;
        std::vector<bool> visited(adjacency_.size(), false);
        std::queue<int> q;

        visited[static_cast<std::size_t>(start)] = true;
        q.push(start);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            order.push_back(cur);

            for (const auto& edge : adjacency_[static_cast<std::size_t>(cur)]) {
                if (!visited[static_cast<std::size_t>(edge.to)]) {
                    visited[static_cast<std::size_t>(edge.to)] = true;
                    q.push(edge.to);
                }
            }
        }
        return order;
    }

    std::vector<int> dfs(int start) const {
        validate(start);
        std::vector<int> order;
        std::vector<bool> visited(adjacency_.size(), false);
        dfs_visit(start, visited, order);
        return order;
    }

    std::vector<int> dijkstra(int start) const {
        validate(start);
        constexpr int infinity = std::numeric_limits<int>::max() / 4;
        std::vector<int> distance(adjacency_.size(), infinity);
        using State = std::pair<int, int>;
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

        distance[static_cast<std::size_t>(start)] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            const auto [dist, cur] = pq.top();
            pq.pop();
            if (dist != distance[static_cast<std::size_t>(cur)]) {
                continue;
            }
            for (const auto& edge : adjacency_[static_cast<std::size_t>(cur)]) {
                const int next_dist = dist + edge.weight;
                if (next_dist < distance[static_cast<std::size_t>(edge.to)]) {
                    distance[static_cast<std::size_t>(edge.to)] = next_dist;
                    pq.push({next_dist, edge.to});
                }
            }
        }
        return distance;
    }

    [[nodiscard]] int vertex_count() const noexcept {
        return static_cast<int>(adjacency_.size());
    }

    [[nodiscard]] const std::vector<Edge>& neighbors(int vertex) const {
        validate(vertex);
        return adjacency_[static_cast<std::size_t>(vertex)];
    }

private:
    void validate(int vertex) const {
        if (vertex < 0 || vertex >= vertex_count()) {
            throw std::out_of_range("vertex is out of range");
        }
    }

    void dfs_visit(int vertex, std::vector<bool>& visited, std::vector<int>& order) const {
        visited[static_cast<std::size_t>(vertex)] = true;
        order.push_back(vertex);
        for (const auto& edge : adjacency_[static_cast<std::size_t>(vertex)]) {
            if (!visited[static_cast<std::size_t>(edge.to)]) {
                dfs_visit(edge.to, visited, order);
            }
        }
    }

    std::vector<std::vector<Edge>> adjacency_;
};

} // namespace ds

