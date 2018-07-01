#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>
#include "find_distinct_pairs.hpp"

TEST_CASE("test ") {

    {
    long target = 10;
    int expected = 3;
    std::vector<int> nums = {1, 2, 3, 6, 7, 8, 9, 1};
    REQUIRE(expected == find_distinct_pairs(nums, target));
    }


    {
    long target = 12;
    int expected = 2;
    std::vector<int> nums = {6, 6, 3, 9, 3, 5, 1};
    REQUIRE(expected == find_distinct_pairs(nums, target));
    }

}
