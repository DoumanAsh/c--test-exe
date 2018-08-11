#pragma once

#include <cstdint>
#include <cmath>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) noexcept : val(x), next(nullptr) {}
};

ListNode* add_two_number(ListNode* l1, ListNode* l2) {
    int sum = l1->val + l2->val;
    int carry = sum / 10;
    ListNode* result = new ListNode(sum % 10);
    ListNode* cur = result;

    ListNode* first = l1->next;
    ListNode* second = l2->next;

    for (; first != nullptr || second != nullptr;) {
        int left = 0;
        int right = 0;

        if (first != nullptr) {
            left = first->val;
            first = first->next;
        }
        if (second != nullptr) {
            right = second->val;
            second = second->next;
        }

        sum = left + right + carry;
        carry = sum / 10;
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
    }

    if (carry > 0) cur->next = new ListNode(carry);

    return result;
}
