#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter08 {

void sortColors(std::vector<int>& nums) {
    int l = 0;
    int i = 0;
    int r = static_cast<int>(nums.size()) - 1;
    while (i <= r) {
        if (nums[i] == 0) {
            std::swap(nums[l++], nums[i++]);
        } else if (nums[i] == 2) {
            std::swap(nums[i], nums[r--]);
        } else {
            ++i;
        }
    }
}

std::vector<std::vector<int>> merge(std::vector<std::vector<int>> intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> ans;
    for (const auto& cur : intervals) {
        if (ans.empty() || ans.back()[1] < cur[0]) {
            ans.push_back(cur);
        } else {
            ans.back()[1] = std::max(ans.back()[1], cur[1]);
        }
    }
    return ans;
}

std::vector<std::vector<int>> insert(std::vector<std::vector<int>> intervals, std::vector<int> newInterval) {
    std::vector<std::vector<int>> ans;
    int i = 0;
    const int n = static_cast<int>(intervals.size());
    while (i < n && intervals[i][1] < newInterval[0]) {
        ans.push_back(intervals[i++]);
    }
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = std::min(newInterval[0], intervals[i][0]);
        newInterval[1] = std::max(newInterval[1], intervals[i][1]);
        ++i;
    }
    ans.push_back(newInterval);
    while (i < n) {
        ans.push_back(intervals[i++]);
    }
    return ans;
}

std::vector<int> topKFrequentByBucket(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> cnt;
    for (int x : nums) {
        ++cnt[x];
    }
    std::vector<std::vector<int>> bucket(nums.size() + 1);
    for (const auto& [x, c] : cnt) {
        bucket[c].push_back(x);
    }
    std::vector<int> ans;
    for (int i = static_cast<int>(bucket.size()) - 1; i >= 0 && static_cast<int>(ans.size()) < k; --i) {
        for (int x : bucket[i]) {
            ans.push_back(x);
            if (static_cast<int>(ans.size()) == k) {
                break;
            }
        }
    }
    std::sort(ans.begin(), ans.end());
    return ans;
}

class LRUCache {
public:
    explicit LRUCache(int capacity) : cap_(capacity) {}

    int get(int key) {
        auto it = mp_.find(key);
        if (it == mp_.end()) {
            return -1;
        }
        lst_.splice(lst_.begin(), lst_, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = mp_.find(key);
        if (it != mp_.end()) {
            it->second->second = value;
            lst_.splice(lst_.begin(), lst_, it->second);
            return;
        }
        if (static_cast<int>(lst_.size()) == cap_) {
            mp_.erase(lst_.back().first);
            lst_.pop_back();
        }
        lst_.push_front({key, value});
        mp_[key] = lst_.begin();
    }

private:
    int cap_;
    std::list<std::pair<int, int>> lst_;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> mp_;
};

void run() {
    {
        std::vector<int> nums{2,0,2,1,1,0};
        sortColors(nums);
        assert((nums == std::vector<int>{0,0,1,1,2,2}));
    }
    {
        auto merged = merge({{1,3},{2,6},{8,10},{15,18}});
        assert((merged == std::vector<std::vector<int>>{{1,6},{8,10},{15,18}}));
    }
    {
        auto inserted = insert({{1,2},{3,5},{6,7},{8,10},{12,16}}, {4,8});
        assert((inserted == std::vector<std::vector<int>>{{1,2},{3,10},{12,16}}));
    }
    {
        auto ans = topKFrequentByBucket({1,1,1,2,2,3}, 2);
        assert((ans == std::vector<int>{1,2}));
    }
    {
        LRUCache cache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        assert(cache.get(1) == 1);
        cache.put(3, 3);
        assert(cache.get(2) == -1);
        cache.put(4, 4);
        assert(cache.get(1) == -1);
        assert(cache.get(3) == 3);
        assert(cache.get(4) == 4);
    }
}

} // namespace chapter08

int main() {
    chapter08::run();
    return 0;
}

