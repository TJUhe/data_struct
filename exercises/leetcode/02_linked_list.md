# 链表

链表题重点练三件事：

1. 指针重连，不要丢链。
2. 虚拟头结点，简化删除和插入。
3. 快慢指针，处理环和中点。

## 通用定义

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

## 206. Reverse Linked List

题眼：整条链反转。

思路：三个指针 `prev / cur / next`，每次先保存后继，再改指向。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};
```

## 21. Merge Two Sorted Lists

题眼：两个有序链表合并成一个有序链表。

思路：用虚拟头结点做结果链表的起点，比较两个当前节点，把较小者接到尾部。

复杂度：时间 `O(m+n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0), *tail = &dummy;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        tail->next = list1 ? list1 : list2;
        return dummy.next;
    }
};
```

## 19. Remove Nth Node From End of List

题眼：删除倒数第 `n` 个节点。

思路：快指针先走 `n` 步，再让快慢指针一起走。快指针到尾时，慢指针正好停在待删节点前面。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;
        while (n--) fast = fast->next;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* del = slow->next;
        slow->next = del->next;
        return dummy.next;
    }
};
```

## 141. Linked List Cycle

题眼：判断链表是否有环。

思路：快慢指针。慢指针一次一步，快指针一次两步。如果有环，两者一定会相遇。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
```

## 142. Linked List Cycle II

题眼：找到环的入口。

思路：相遇后，把一个指针放回头结点，再让两个指针每次都走一步；再次相遇点就是入口。

复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode* p1 = head;
                ListNode* p2 = slow;
                while (p1 != p2) {
                    p1 = p1->next;
                    p2 = p2->next;
                }
                return p1;
            }
        }
        return nullptr;
    }
};
```

