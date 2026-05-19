# 堆 / 优先队列

堆题重点训练：

1. 什么时候该用“保留前 k 个最优值”。
2. 什么时候要动态维护中位数或最小/最大集合。
3. 用堆模拟调度、合并和重排。

![堆结构示意图](../../docs/images/07_heap_priority_queue.svg)

## 215. Kth Largest Element in an Array

题目描述：给定一个数组，返回其中第 k 大的元素。

示意：只保留最大的 k 个数，小堆堆顶就是答案。

关键点：你不需要把整个数组完全排序，保留前 k 个最优值就够了。

思路：维护一个大小为 k 的最小堆。堆里永远放当前最大的 k 个元素，堆顶就是这 k 个里最小的，也就是答案。

复杂度：时间 `O(n log k)`，空间 `O(k)`。

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : nums) {
            pq.push(x);
            if ((int)pq.size() > k) pq.pop();
        }
        return pq.top();
    }
};
```

## 347. Top K Frequent Elements

题目描述：返回出现频率最高的前 k 个元素。

示意：先数次数，再按次数取前 k 名。

关键点：先统计频率，再根据频率取前 k 名。

思路：先统计频次，再用最小堆保留频次最高的 k 个条目。

复杂度：时间 `O(n log k)`，空间 `O(n)`。

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) ++cnt[x];
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        for (auto& [val, c] : cnt) {
            pq.push({c, val});
            if ((int)pq.size() > k) pq.pop();
        }
        vector<int> ans;
        while (!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
    }
};
```

## 23. Merge k Sorted Lists

题目描述：合并 k 个升序链表，返回一个新的升序链表。

示意：每次从所有链表头里取最小值接到结果尾部。

关键点：每次都只取当前所有链表头里最小的那个，这正适合堆。

思路：堆里放每个链表当前头节点，每次取最小的那个，取完后把它的 next 再放进去。

复杂度：时间 `O(n log k)`。

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b){ return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for (auto* node : lists) if (node) pq.push(node);
        ListNode dummy(0), *tail = &dummy;
        while (!pq.empty()) {
            auto* node = pq.top(); pq.pop();
            tail->next = node;
            tail = tail->next;
            if (node->next) pq.push(node->next);
        }
        return dummy.next;
    }
};
```

## 295. Find Median from Data Stream

题目描述：设计一个数据结构，支持不断插入数字，并随时返回当前中位数。

示意：左边一半、右边一半，两个堆始终平衡。

关键点：中位数把数据分成左右两半，所以用两个堆分别维护两半数据。

思路：两个堆。左边最大堆保存较小一半，右边最小堆保存较大一半，始终保持数量平衡。

复杂度：插入 `O(log n)`，找中位数 `O(1)`。

```cpp
class MedianFinder {
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
public:
    void addNum(int num) {
        if (lo.empty() || num <= lo.top()) lo.push(num);
        else hi.push(num);
        if (lo.size() > hi.size() + 1) {
            hi.push(lo.top()); lo.pop();
        } else if (hi.size() > lo.size()) {
            lo.push(hi.top()); hi.pop();
        }
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};
```

## 621. Task Scheduler

题目描述：给定任务列表和冷却时间 n，相同任务之间至少间隔 n 个单位时间，求完成所有任务的最短时间。

示意：任务执行后进入冷却队列，冷却结束再回到最大堆。

关键点：每一步都优先执行当前剩余次数最多的任务。

思路：用最大堆总是选当前剩余次数最多的任务，再用队列记录冷却中的任务何时能重新入堆。

复杂度：时间 `O(n log m)`，`m` 为任务种类数。

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> cnt;
        for (char c : tasks) ++cnt[c];
        priority_queue<int> pq;
        for (auto& [_, c] : cnt) pq.push(c);
        queue<pair<int,int>> wait;
        int time = 0;
        while (!pq.empty() || !wait.empty()) {
            ++time;
            if (!pq.empty()) {
                int c = pq.top(); pq.pop();
                if (--c > 0) wait.push({time + n, c});
            }
            while (!wait.empty() && wait.front().first == time) {
                pq.push(wait.front().second);
                wait.pop();
            }
        }
        return time;
    }
};
```
