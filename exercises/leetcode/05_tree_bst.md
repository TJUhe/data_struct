# 树 / BST

树题重点训练：

1. 递归思维。
2. 前中后序和层序遍历。
3. 二叉搜索树的“左小右大”性质。

![二叉搜索树结构示意图](../../docs/images/06_tree.svg)

## 104. Maximum Depth of Binary Tree

题目描述：给定一棵二叉树，返回它的最大深度。

示意：一条根到叶子的最长路径有几层，就是深度。

关键点：树的问题通常都能拆成“当前节点 + 左子树 + 右子树”。

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

题目描述：将一棵二叉树左右镜像翻转。

示意：`left` 和 `right` 互换，整棵树像照镜子一样反过来。

关键点：每个节点都只需要把左右孩子交换一次，然后继续递归处理子树。

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

题目描述：按层从上到下、从左到右输出二叉树节点。

示意：`[root] -> [下一层所有节点] -> [再下一层所有节点]`

关键点：层序遍历天然对应队列。

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

题目描述：判断给定二叉树是否满足二叉搜索树的定义。

示意：任意节点左边都要小，右边都要大，而且这个约束要传递到整个子树。

关键点：不能只看当前节点和直接孩子，要保证整个子树都在合法范围内。

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

题目描述：返回二叉搜索树中第 k 小的元素。

示意：中序遍历结果天然是升序序列。

关键点：BST 的中序遍历是有序的，所以第 k 个访问到的值就是答案。

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
