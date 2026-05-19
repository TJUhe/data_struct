#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter06 {

int findKthLargest(const std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int x : nums) {
        pq.push(x);
        if (static_cast<int>(pq.size()) > k) {
            pq.pop();
        }
    }
    return pq.top();
}

std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> cnt;
    for (int x : nums) {
        ++cnt[x];
    }
    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    for (const auto& [val, c] : cnt) {
        pq.push({c, val});
        if (static_cast<int>(pq.size()) > k) {
            pq.pop();
        }
    }
    std::vector<int> ans;
    while (!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }
    std::sort(ans.begin(), ans.end());
    return ans;
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;
    };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (ListNode* node : lists) {
        if (node != nullptr) {
            pq.push(node);
        }
    }
    ListNode dummy;
    ListNode* tail = &dummy;
    while (!pq.empty()) {
        ListNode* node = pq.top();
        pq.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next != nullptr) {
            pq.push(node->next);
        }
    }
    return dummy.next;
}

class MedianFinder {
public:
    void addNum(int num) {
        if (lo_.empty() || num <= lo_.top()) {
            lo_.push(num);
        } else {
            hi_.push(num);
        }
        if (lo_.size() > hi_.size() + 1) {
            hi_.push(lo_.top());
            lo_.pop();
        } else if (hi_.size() > lo_.size()) {
            lo_.push(hi_.top());
            hi_.pop();
        }
    }

    double findMedian() const {
        if (lo_.size() > hi_.size()) {
            return lo_.top();
        }
        return (lo_.top() + hi_.top()) / 2.0;
    }

private:
    std::priority_queue<int> lo_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> hi_;
};

int leastInterval(const std::vector<char>& tasks, int n) {
    std::unordered_map<char, int> cnt;
    for (char c : tasks) {
        ++cnt[c];
    }
    std::priority_queue<int> pq;
    for (const auto& [task, c] : cnt) {
        (void)task;
        pq.push(c);
    }
    std::queue<std::pair<int, int>> cool;
    int time = 0;
    while (!pq.empty() || !cool.empty()) {
        while (!cool.empty() && cool.front().first <= time) {
            pq.push(cool.front().second);
            cool.pop();
        }
        if (!pq.empty()) {
            int c = pq.top();
            pq.pop();
            --c;
            if (c > 0) {
                cool.push({time + n + 1, c});
            }
            ++time;
        } else {
            time = cool.front().first;
        }
    }
    return time;
}

void run() {
    assert(findKthLargest({3,2,1,5,6,4}, 2) == 5);
    assert((topKFrequent({1,1,1,2,2,3}, 2) == std::vector<int>{1, 2}));
    {
        ListNode* a = make_list({1, 4, 5});
        ListNode* b = make_list({1, 3, 4});
        ListNode* c = make_list({2, 6});
        std::vector<ListNode*> lists{a, b, c};
        ListNode* merged = mergeKLists(lists);
        assert((list_to_vector(merged) == std::vector<int>{1,1,2,3,4,4,5,6}));
        free_list(merged);
    }
    {
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        assert(mf.findMedian() == 1.5);
        mf.addNum(3);
        assert(mf.findMedian() == 2.0);
    }
    assert(leastInterval({'A','A','A','B','B','B'}, 2) == 8);
}

} // namespace chapter06

int main() {
    chapter06::run();
    return 0;
}

