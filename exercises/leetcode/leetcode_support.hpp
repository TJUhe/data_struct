#pragma once

#include <algorithm>
#include <cassert>
#include <climits>
#include <functional>
#include <optional>
#include <queue>
#include <unordered_set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;

    explicit ListNode(int x = 0, ListNode* next_node = nullptr)
        : val(x), next(next_node) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int x = 0, TreeNode* left_node = nullptr, TreeNode* right_node = nullptr)
        : val(x), left(left_node), right(right_node) {}
};

struct Node {
    int val;
    std::vector<Node*> neighbors;

    explicit Node(int x) : val(x) {}
};

inline ListNode* make_list(const std::vector<int>& values) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int value : values) {
        tail->next = new ListNode(value);
        tail = tail->next;
    }
    return dummy.next;
}

inline std::vector<int> list_to_vector(ListNode* head, std::size_t limit = 1000) {
    std::vector<int> values;
    while (head != nullptr && limit-- > 0) {
        values.push_back(head->val);
        head = head->next;
    }
    return values;
}

inline void free_list(ListNode* head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

inline TreeNode* make_tree(const std::vector<std::optional<int>>& values) {
    if (values.empty() || !values.front().has_value()) {
        return nullptr;
    }

    std::vector<TreeNode*> nodes(values.size(), nullptr);
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i].has_value()) {
            nodes[i] = new TreeNode(*values[i]);
        }
    }

    for (std::size_t i = 0; i < values.size(); ++i) {
        if (nodes[i] == nullptr) {
            continue;
        }
        const std::size_t left = i * 2 + 1;
        const std::size_t right = i * 2 + 2;
        if (left < values.size()) {
            nodes[i]->left = nodes[left];
        }
        if (right < values.size()) {
            nodes[i]->right = nodes[right];
        }
    }

    return nodes[0];
}

inline void free_tree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

inline std::vector<int> inorder_values(TreeNode* root) {
    std::vector<int> values;
    std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        dfs(node->left);
        values.push_back(node->val);
        dfs(node->right);
    };
    dfs(root);
    return values;
}

inline bool same_multiset(std::vector<std::string> lhs, std::vector<std::string> rhs) {
    std::sort(lhs.begin(), lhs.end());
    std::sort(rhs.begin(), rhs.end());
    return lhs == rhs;
}
