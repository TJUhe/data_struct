#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter02 {

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;
    while (cur != nullptr) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy;
    ListNode* tail = &dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = (list1 != nullptr) ? list1 : list2;
    return dummy.next;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;
    while (n--) {
        fast = fast->next;
    }
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* del = slow->next;
    slow->next = del->next;
    return dummy.next;
}

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
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

void run() {
    {
        ListNode* head = make_list({1, 2, 3, 4, 5});
        head = reverseList(head);
        assert((list_to_vector(head) == std::vector<int>{5, 4, 3, 2, 1}));
        free_list(head);
    }
    {
        ListNode* a = make_list({1, 2, 4});
        ListNode* b = make_list({1, 3, 4});
        ListNode* merged = mergeTwoLists(a, b);
        assert((list_to_vector(merged) == std::vector<int>{1, 1, 2, 3, 4, 4}));
        free_list(merged);
    }
    {
        ListNode* head = make_list({1, 2, 3, 4, 5});
        head = removeNthFromEnd(head, 2);
        assert((list_to_vector(head) == std::vector<int>{1, 2, 3, 5}));
        free_list(head);
    }
    {
        ListNode* head = make_list({3, 2, 0, -4});
        ListNode* tail = head;
        ListNode* entry = nullptr;
        while (tail->next != nullptr) {
            if (tail->val == 2) {
                entry = tail;
            }
            tail = tail->next;
        }
        entry = head->next;
        tail->next = entry;
        assert(hasCycle(head));
        assert(detectCycle(head) == entry);
        tail->next = nullptr;
        free_list(head);
    }
}

} // namespace chapter02

int main() {
    chapter02::run();
    return 0;
}

