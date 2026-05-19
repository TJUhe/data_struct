# 数组 / 前缀和 / 双指针

这一组题主要练三件事：

1. 连续内存上的原地操作。
2. 两端夹逼的双指针。
3. 前缀和把区间问题转成“到这里为止统计过什么”。

## 26. Remove Duplicates from Sorted Array

题眼：有序数组，去重后原地保留结果。

思路：慢指针 `slow` 维护“下一个不同元素应该放的位置”，快指针 `fast` 扫描全数组。遇到新值就写入。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int slow = 1;
        for (int fast = 1; fast < (int)nums.size(); ++fast) {
            if (nums[fast] != nums[fast - 1]) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
```

## 283. Move Zeroes

题眼：把 0 挪到末尾，且非零元素相对顺序不变。

思路：`slow` 记录当前该放非零元素的位置。`fast` 扫描时遇到非零就交换到前面。这个写法比“先收集再补 0”更直接。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        for (int fast = 0; fast < (int)nums.size(); ++fast) {
            if (nums[fast] != 0) {
                swap(nums[slow++], nums[fast]);
            }
        }
    }
};
```

## 189. Rotate Array

题眼：把数组整体右移 `k` 步。

思路：经典三次反转。先整体反转，再反转前 `k` 个和后 `n-k` 个，就能把尾部元素转到前面。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = (int)nums.size();
        k %= n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```

## 238. Product of Array Except Self

题眼：每个位置返回“除自己外所有元素的乘积”，不能用除法。

思路：两趟扫描。第一趟算前缀积，第二趟从右往左乘后缀积。`res[i]` 先存左边乘积，再乘右边乘积。

复杂度：时间 `O(n)`，空间 `O(1)` 额外空间（不算答案数组）。

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> res(n, 1);
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
};
```

## 11. Container With Most Water

题眼：两条线围水，找最大面积。

思路：双指针从两边往中间走。面积受较短边限制，所以每次移动较短的一边才有机会变大。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = (int)height.size() - 1;
        int ans = 0;
        while (l < r) {
            ans = max(ans, min(height[l], height[r]) * (r - l));
            if (height[l] < height[r]) ++l;
            else --r;
        }
        return ans;
    }
};
```

