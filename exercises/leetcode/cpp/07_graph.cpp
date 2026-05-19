#include "../leetcode_support.hpp"

#include <cassert>
#include <unordered_set>

namespace chapter07 {

int numIslands(std::vector<std::vector<char>> grid) {
    const int m = static_cast<int>(grid.size());
    const int n = static_cast<int>(grid[0].size());
    int ans = 0;
    std::function<void(int, int)> dfs = [&](int x, int y) {
        grid[x][y] = '0';
        static const int dx[4] = {1, -1, 0, 0};
        static const int dy[4] = {0, 0, 1, -1};
        for (int d = 0; d < 4; ++d) {
            const int nx = x + dx[d];
            const int ny = y + dy[d];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                dfs(nx, ny);
            }
        }
    };
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                ++ans;
                dfs(i, j);
            }
        }
    }
    return ans;
}

Node* cloneGraph(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    std::unordered_map<Node*, Node*> mp;
    std::function<Node*(Node*)> dfs = [&](Node* cur) -> Node* {
        if (mp.count(cur)) {
            return mp[cur];
        }
        Node* copy = new Node(cur->val);
        mp[cur] = copy;
        for (Node* nei : cur->neighbors) {
            copy->neighbors.push_back(dfs(nei));
        }
        return copy;
    };
    return dfs(node);
}

bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> g(numCourses);
    std::vector<int> indeg(numCourses, 0);
    for (const auto& e : prerequisites) {
        g[e[1]].push_back(e[0]);
        ++indeg[e[0]];
    }
    std::queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }
    int cnt = 0;
    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        ++cnt;
        for (int v : g[u]) {
            if (--indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    return cnt == numCourses;
}

int orangesRotting(std::vector<std::vector<int>> grid) {
    const int m = static_cast<int>(grid.size());
    const int n = static_cast<int>(grid[0].size());
    std::queue<std::pair<int, int>> q;
    int fresh = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                ++fresh;
            }
        }
    }
    int minutes = 0;
    static const int dx[4] = {1, -1, 0, 0};
    static const int dy[4] = {0, 0, 1, -1};
    while (!q.empty() && fresh > 0) {
        const int sz = static_cast<int>(q.size());
        ++minutes;
        for (int s = 0; s < sz; ++s) {
            const auto [x, y] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                const int nx = x + dx[d];
                const int ny = y + dy[d];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    --fresh;
                    q.push({nx, ny});
                }
            }
        }
    }
    return fresh == 0 ? minutes : -1;
}

int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k) {
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    for (const auto& e : times) {
        g[e[0]].push_back({e[1], e[2]});
    }
    const int INF = 1e9;
    std::vector<int> dist(n + 1, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    dist[k] = 0;
    pq.push({0, k});
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (const auto& [v, w] : g[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) {
            return -1;
        }
        ans = std::max(ans, dist[i]);
    }
    return ans;
}

void free_graph(Node* node) {
    if (node == nullptr) {
        return;
    }
    std::unordered_set<Node*> visited;
    std::queue<Node*> q;
    q.push(node);
    visited.insert(node);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        for (Node* nei : cur->neighbors) {
            if (!visited.count(nei)) {
                visited.insert(nei);
                q.push(nei);
            }
        }
    }
    for (Node* cur : visited) {
        delete cur;
    }
}

void run() {
    assert(numIslands({{'1','1','0'},{'0','1','0'},{'1','0','1'}}) == 3);
    {
        Node* a = new Node(1);
        Node* b = new Node(2);
        Node* c = new Node(3);
        a->neighbors = {b, c};
        b->neighbors = {a, c};
        c->neighbors = {a, b};
        Node* copy = cloneGraph(a);
        assert(copy != a);
        assert(copy->val == 1);
        assert(copy->neighbors.size() == 2);
        free_graph(a);
        free_graph(copy);
    }
    assert(canFinish(2, {{1,0}}));
    assert(!canFinish(2, {{1,0},{0,1}}));
    assert(orangesRotting({{2,1,1},{1,1,0},{0,1,1}}) == 4);
    assert(networkDelayTime({{2,1,1},{2,3,1},{3,4,1}}, 4, 2) == 2);
}

} // namespace chapter07

int main() {
    chapter07::run();
    return 0;
}
