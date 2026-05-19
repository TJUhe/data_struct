#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter04 {

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> pos;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        const int need = target - nums[i];
        if (pos.count(need)) {
            return {pos[need], i};
        }
        pos[nums[i]] = i;
    }
    return {};
}

bool isAnagram(const std::string& s, const std::string& t) {
    if (s.size() != t.size()) {
        return false;
    }
    int cnt[26] = {};
    for (char c : s) {
        ++cnt[c - 'a'];
    }
    for (char c : t) {
        if (--cnt[c - 'a'] < 0) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> mp;
    for (auto s : strs) {
        std::string key = s;
        std::sort(key.begin(), key.end());
        mp[key].push_back(s);
    }
    std::vector<std::vector<std::string>> ans;
    for (auto& [k, group] : mp) {
        (void)k;
        ans.push_back(std::move(group));
    }
    return ans;
}

int longestConsecutive(const std::vector<int>& nums) {
    std::unordered_set<int> st(nums.begin(), nums.end());
    int ans = 0;
    for (int x : st) {
        if (!st.count(x - 1)) {
            int y = x;
            while (st.count(y)) {
                ++y;
            }
            ans = std::max(ans, y - x);
        }
    }
    return ans;
}

int subarraySum(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> cnt;
    cnt[0] = 1;
    int sum = 0;
    int ans = 0;
    for (int x : nums) {
        sum += x;
        if (cnt.count(sum - k)) {
            ans += cnt[sum - k];
        }
        ++cnt[sum];
    }
    return ans;
}

void run() {
    assert((twoSum({2, 7, 11, 15}, 9) == std::vector<int>{0, 1}));
    assert(isAnagram("anagram", "nagaram"));
    assert(!isAnagram("rat", "car"));
    auto groups = groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"});
    assert(groups.size() == 3);
    assert(longestConsecutive({100, 4, 200, 1, 3, 2}) == 4);
    assert(subarraySum({1,1,1}, 2) == 2);
}

} // namespace chapter04

int main() {
    chapter04::run();
    return 0;
}

