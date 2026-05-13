# 练习题参考答案

这些答案是参考实现和解题思路，不是唯一写法。建议先自己完成，再对照复杂度、边界情况和接口行为。

## 基础练习

### 1. 给 DynamicArray 增加 pop_back 和 front/back

思路：

- `pop_back` 只需要检查空数组，然后 `--size_`。
- `front` 返回 `data_[0]`。
- `back` 返回 `data_[size_ - 1]`。
- 都要处理空数组。

可加入 [include/ds/dynamic_array.hpp](../include/ds/dynamic_array.hpp)：

```cpp
T pop_back() {
    if (empty()) {
        throw std::out_of_range("pop_back on empty array");
    }
    return std::move(data_[--size_]);
}

T& front() {
    if (empty()) {
        throw std::out_of_range("front on empty array");
    }
    return data_[0];
}

T& back() {
    if (empty()) {
        throw std::out_of_range("back on empty array");
    }
    return data_[size_ - 1];
}
```

复杂度：三个操作都是 `O(1)`。

### 2. 给 SinglyLinkedList 增加 find_middle

思路：快慢指针。`slow` 每次走一步，`fast` 每次走两步。`fast` 到尾部时，`slow` 在中间。

```cpp
const T& find_middle() const {
    if (empty()) {
        throw std::out_of_range("find_middle on empty list");
    }

    Node* slow = head_;
    Node* fast = head_;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->value;
}
```

偶数长度时，这个写法返回靠后的中间节点。例如 `1 -> 2 -> 3 -> 4` 返回 `3`。

复杂度：时间 `O(n)`，额外空间 `O(1)`。

### 3. 使用 Stack 实现十进制转二进制

思路：不断对 2 取余，余数入栈；最后出栈得到高位到低位。

```cpp
std::string to_binary(unsigned int value) {
    if (value == 0) {
        return "0";
    }

    ds::Stack<char> bits;
    while (value > 0) {
        bits.push(static_cast<char>('0' + value % 2));
        value /= 2;
    }

    std::string result;
    while (!bits.empty()) {
        result.push_back(bits.pop());
    }
    return result;
}
```

复杂度：`O(log n)`，因为每次除以 2。

### 4. 使用 CircularQueue 模拟客服排队系统

参考代码：

```cpp
struct Customer {
    int id;
    std::string question;
};

ds::CircularQueue<Customer> waiting(3);
waiting.push({1, "reset password"});
waiting.push({2, "refund"});
waiting.push({3, "upgrade plan"});

while (!waiting.empty()) {
    Customer customer = waiting.pop();
    std::cout << "serving #" << customer.id << ": " << customer.question << '\n';
}
```

扩展点：可以给 `Customer` 增加 `arrival_time`，统计平均等待时间。

### 5. 给 HashTable 增加 keys()

思路：遍历每个 bucket，再遍历 bucket 里的每个键值对。

```cpp
std::vector<Key> keys() const {
    std::vector<Key> result;
    result.reserve(size_);
    for (const auto& bucket : buckets_) {
        for (const auto& [key, value] : bucket) {
            (void)value;
            result.push_back(key);
        }
    }
    return result;
}
```

复杂度：`O(bucket_count + size)`。

## 进阶练习

### 1. 给 BST 增加 min、max 和 floor

`min`：一路向左。

```cpp
const T& min() const {
    if (empty()) {
        throw std::out_of_range("min on empty tree");
    }
    Node* cur = root_;
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur->value;
}
```

`max`：一路向右。

```cpp
const T& max() const {
    if (empty()) {
        throw std::out_of_range("max on empty tree");
    }
    Node* cur = root_;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    return cur->value;
}
```

`floor(x)`：小于等于 `x` 的最大值。

```cpp
std::optional<T> floor(const T& value) const {
    Node* cur = root_;
    std::optional<T> answer;
    while (cur != nullptr) {
        if (!compare_(cur->value, value) && !compare_(value, cur->value)) {
            return cur->value;
        }
        if (compare_(value, cur->value)) {
            cur = cur->left;
        } else {
            answer = cur->value;
            cur = cur->right;
        }
    }
    return answer;
}
```

平均复杂度：`O(log n)`；退化树最坏 `O(n)`。

### 2. 给 BST 增加层序遍历

思路：队列保存下一批要访问的节点。

```cpp
template <typename Visitor>
void level_order(Visitor visitor) const {
    if (root_ == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(root_);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        visitor(cur->value);
        if (cur->left != nullptr) {
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
        }
    }
}
```

需要 `#include <queue>`。

复杂度：时间 `O(n)`，空间最坏 `O(n)`。

### 3. 把 BinaryHeap 改造成最小堆

当前 `BinaryHeap<T, Compare>` 已经能通过比较器改变优先级。默认 `std::less<T>` 表示最大堆。最小堆可以这样用：

```cpp
ds::BinaryHeap<int, std::greater<int>> min_heap;
min_heap.push(3);
min_heap.push(1);
min_heap.push(2);
assert(min_heap.pop() == 1);
```

原因在于 `higher_priority(lhs, rhs)` 使用 `compare_(rhs, lhs)` 判断 `lhs` 是否优先级更高。

### 4. 给 WeightedGraph 增加无权最短路径并返回路径

思路：BFS 过程中记录 `parent`，到达终点后反向回溯。

```cpp
std::vector<int> shortest_path_unweighted(int start, int target) const {
    validate(start);
    validate(target);

    std::vector<int> parent(adjacency_.size(), -1);
    std::vector<bool> visited(adjacency_.size(), false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == target) {
            break;
        }
        for (const auto& edge : adjacency_[cur]) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                parent[edge.to] = cur;
                q.push(edge.to);
            }
        }
    }

    if (!visited[target]) {
        return {};
    }

    std::vector<int> path;
    for (int cur = target; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
```

需要 `#include <algorithm>` 和 `#include <queue>`。

复杂度：`O(V + E)`。

### 5. 给排序算法加计数器

思路：把统计数据传入排序函数，比较时加 `comparisons`，交换或移动时加 `moves`。

```cpp
struct SortStats {
    long long comparisons = 0;
    long long moves = 0;
};

template <typename RandomIt, typename Compare = std::less<>>
void insertion_sort_counted(RandomIt first, RandomIt last, SortStats& stats, Compare compare = Compare{}) {
    for (auto it = first; it != last; ++it) {
        auto key = std::move(*it);
        ++stats.moves;
        auto hole = it;
        while (hole != first) {
            ++stats.comparisons;
            if (!compare(key, *(hole - 1))) {
                break;
            }
            *hole = std::move(*(hole - 1));
            ++stats.moves;
            --hole;
        }
        *hole = std::move(key);
        ++stats.moves;
    }
}
```

用不同输入测试：已排序、逆序、随机、重复值。

## 综合练习

### 1. 表达式求值器

推荐用两个栈：

- `values` 保存数字。
- `ops` 保存运算符。

遇到数字就入 `values`。遇到运算符时，先把 `ops` 里优先级不低于当前运算符的操作执行掉。遇到 `(` 直接入栈，遇到 `)` 执行到匹配的 `(`。

核心函数：

```cpp
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int apply(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: throw std::invalid_argument("unknown operator");
    }
}
```

边界情况：空字符串、除零、一元负号、多位数和空格。

### 2. 任务调度器

可以用堆。优先级高的先执行，优先级相同则创建时间早的先执行。

```cpp
struct Task {
    int priority;
    long long created_at;
    std::string title;
};

struct TaskOrder {
    bool operator()(const Task& lhs, const Task& rhs) const {
        if (lhs.priority != rhs.priority) {
            return lhs.priority < rhs.priority;
        }
        return lhs.created_at > rhs.created_at;
    }
};
```

然后使用：

```cpp
ds::BinaryHeap<Task, TaskOrder> scheduler;
```

### 3. 简单拼写纠错器

思路：

1. 用 `std::unordered_set<std::string>` 或本仓库哈希表保存词典。
2. 对输入词生成所有编辑距离为 1 的候选词。
3. 在词典里查候选词。

编辑距离为 1 的候选包括：

- 删除一个字符。
- 替换一个字符。
- 插入一个字符。

示例生成删除候选：

```cpp
for (std::size_t i = 0; i < word.size(); ++i) {
    std::string candidate = word.substr(0, i) + word.substr(i + 1);
    if (dictionary.contains(candidate)) {
        suggestions.push_back(candidate);
    }
}
```

替换和插入可以枚举 `'a'` 到 `'z'`。

### 4. 图的拓扑排序并检测环

Kahn 算法：

1. 统计每个顶点入度。
2. 入度为 0 的点入队。
3. 每弹出一个点，就把它指向的邻居入度减 1。
4. 如果最终输出数量小于顶点数，说明有环。

```cpp
std::vector<int> topological_sort_or_empty(const std::vector<std::vector<int>>& graph) {
    std::vector<int> indegree(graph.size(), 0);
    for (const auto& edges : graph) {
        for (int to : edges) {
            ++indegree[to];
        }
    }

    std::queue<int> q;
    for (int i = 0; i < static_cast<int>(indegree.size()); ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> order;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        order.push_back(cur);
        for (int to : graph[cur]) {
            if (--indegree[to] == 0) {
                q.push(to);
            }
        }
    }

    if (order.size() != graph.size()) {
        return {};
    }
    return order;
}
```

### 5. 给 LRU Cache 增加命中率统计

新增成员：

```cpp
std::size_t hits_ = 0;
std::size_t misses_ = 0;
```

修改 `get`：

```cpp
std::optional<Value> get(const Key& key) {
    auto found = index_.find(key);
    if (found == index_.end()) {
        ++misses_;
        return std::nullopt;
    }
    ++hits_;
    touch(found->second);
    return found->second->second;
}
```

增加接口：

```cpp
double hit_rate() const noexcept {
    const std::size_t total = hits_ + misses_;
    if (total == 0) {
        return 0.0;
    }
    return static_cast<double>(hits_) / static_cast<double>(total);
}
```

可以再加 `hits()`、`misses()` 和 `reset_stats()`。

