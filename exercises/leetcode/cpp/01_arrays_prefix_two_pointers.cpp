#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter01 {

int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    int slow = 1;
    for (int fast = 1; fast < static_cast<int>(nums.size()); ++fast) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow++] = nums[fast];
        }
    }
    return slow;
}

void moveZeroes(std::vector<int>& nums) {
    int slow = 0;
    for (int fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
        if (nums[fast] != 0) {
            std::swap(nums[slow++], nums[fast]);
        }
    }
}

void rotate(std::vector<int>& nums, int k) {
    const int n = static_cast<int>(nums.size());
    k %= n;
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin() + k);
    std::reverse(nums.begin() + k, nums.end());
}

std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> res(n, 1);
    int left = 1;
    for (int i = 0; i < n; ++i) {
        res[i] = left;
        left *= nums[i];
    }
    int right = 1;
    for (int i = n - 1; i >= 0; --i) {
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}

int maxArea(const std::vector<int>& height) {
    int l = 0;
    int r = static_cast<int>(height.size()) - 1;
    int ans = 0;
    while (l < r) {
        ans = std::max(ans, std::min(height[l], height[r]) * (r - l));
        if (height[l] < height[r]) {
            ++l;
        } else {
            --r;
        }
    }
    return ans;
}

void run() {
    {
        std::vector<int> nums{1, 1, 2, 2, 3};
        assert(removeDuplicates(nums) == 3);
        assert((std::vector<int>{nums.begin(), nums.begin() + 3} == std::vector<int>{1, 2, 3}));
    }
    {
        std::vector<int> nums{0, 1, 0, 3, 12};
        moveZeroes(nums);
        assert((nums == std::vector<int>{1, 3, 12, 0, 0}));
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7};
        rotate(nums, 3);
        assert((nums == std::vector<int>{5, 6, 7, 1, 2, 3, 4}));
    }
    {
        const std::vector<int> nums{1, 2, 3, 4};
        assert((productExceptSelf(nums) == std::vector<int>{24, 12, 8, 6}));
    }
    {
        assert(maxArea({1,8,6,2,5,4,8,3,7}) == 49);
    }
}

} // namespace chapter01

int main() {
    chapter01::run();
    return 0;
}

