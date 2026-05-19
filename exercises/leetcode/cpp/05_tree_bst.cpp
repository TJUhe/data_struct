#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter05 {

int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    std::swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::vector<std::vector<int>> ans;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = static_cast<int>(q.size());
        ans.push_back({});
        while (sz-- > 0) {
            TreeNode* cur = q.front();
            q.pop();
            ans.back().push_back(cur->val);
            if (cur->left != nullptr) {
                q.push(cur->left);
            }
            if (cur->right != nullptr) {
                q.push(cur->right);
            }
        }
    }
    return ans;
}

bool isValidBST(TreeNode* root) {
    std::function<bool(TreeNode*, long long, long long)> dfs = [&](TreeNode* node, long long low, long long high) {
        if (node == nullptr) {
            return true;
        }
        if (node->val <= low || node->val >= high) {
            return false;
        }
        return dfs(node->left, low, node->val) && dfs(node->right, node->val, high);
    };
    return dfs(root, LLONG_MIN, LLONG_MAX);
}

int kthSmallest(TreeNode* root, int k) {
    std::stack<TreeNode*> st;
    while (root != nullptr || !st.empty()) {
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
        root = st.top();
        st.pop();
        if (--k == 0) {
            return root->val;
        }
        root = root->right;
    }
    return -1;
}

void run() {
    {
        TreeNode* root = make_tree({3, 9, 20, std::nullopt, std::nullopt, 15, 7});
        assert(maxDepth(root) == 3);
        assert((levelOrder(root) == std::vector<std::vector<int>>{{3}, {9, 20}, {15, 7}}));
        free_tree(root);
    }
    {
        TreeNode* root = make_tree({4, 2, 7, 1, 3, 6, 9});
        invertTree(root);
        assert(root->left->val == 7);
        assert(root->right->val == 2);
        free_tree(root);
    }
    {
        TreeNode* root = make_tree({2, 1, 3});
        assert(isValidBST(root));
        assert(kthSmallest(root, 2) == 2);
        free_tree(root);
    }
}

} // namespace chapter05

int main() {
    chapter05::run();
    return 0;
}
