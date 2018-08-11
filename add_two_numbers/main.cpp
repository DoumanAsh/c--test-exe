#include <iostream>
#include "add_two_number.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("add LeetCode") {
    ListNode first(2);
    ListNode first_next(4);
    ListNode first_next_next(3);

    ListNode second(5);
    ListNode second_next(6);
    ListNode second_next_next(4);

    first.next = &first_next;
    first_next.next = &first_next_next;

    second.next = &second_next;
    second_next.next = &second_next_next;

    auto result = add_two_number(&first, &second);

    REQUIRE(result->val == 7);
    REQUIRE(result->next != nullptr);
    REQUIRE(result->next->val == 0);
    REQUIRE(result->next->next != nullptr);
    REQUIRE(result->next->next->val == 8);
    REQUIRE(result->next->next->next == nullptr);
}

TEST_CASE("add with empty list") {
    ListNode first(1);
    ListNode first_next(8);

    ListNode second(0);

    first.next = &first_next;

    auto result = add_two_number(&first, &second);
    REQUIRE(result->val == 1);
    REQUIRE(result->next != nullptr);
    REQUIRE(result->next->val == 8);
    REQUIRE(result->next->next == nullptr);
}
