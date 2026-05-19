# 树 / BST

树题重点训练：

1. 递归思维。
2. 前中后序和层序遍历。
3. 二叉搜索树的“左小右大”性质。

## 104. Maximum Depth of Binary Tree

题眼：求二叉树深度。

思路：当前节点的深度等于左右子树深度最大值加一。

复杂度：时间 `O(n)`，空间 `O(h)`。

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
```

## 226. Invert Binary Tree

题眼：左右子树交换。

思路：递归交换左右孩子，然后继续翻转子树。

复杂度：时间 `O(n)`，空间 `O(h)`。

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
```

## 102. Binary Tree Level Order Traversal

题眼：层序遍历。

思路：队列按层推进，每次先记录当前层节点数，再逐个出队。

复杂度：时间 `O(n)`，空间 `O(n)`。

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            ans.push_back({});
            while (sz--) {
                auto* cur = q.front(); q.pop();
                ans.back().push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        return ans;
    }
};
```

## 98. Validate Binary Search Tree

题眼：判断树是不是 BST。

思路：递归时传上下界，当前节点值必须落在 `(low, high)` 之间。

复杂度：时间 `O(n)`，空间 `O(h)`。

```cpp
class Solution {
    bool dfs(TreeNode* node, long long low, long long high) {
        if (!node) return true;
        if (node->val <= low || node->val >= high) return false;
        return dfs(node->left, low, node->val) && dfs(node->right, node->val, high);
    }
public:
    bool isValidBST(TreeNode* root) {
        return dfs(root, LLONG_MIN, LLONG_MAX);
    }
};
```

## 230. Kth Smallest Element in a BST

题眼：求 BST 中第 k 小的值。

思路：中序遍历天然有序，遍历到第 k 个就停。

复杂度：平均 `O(h + k)`。

```cpp
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            root = st.top(); st.pop();
            if (--k == 0) return root->val;
            root = root->right;
        }
        return -1;
    }
};
```

