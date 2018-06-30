#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>
#include "find_two_sum.hpp"

TEST_CASE("test find two sum") {
    Solution solution;

    {
    int target = 9;
    std::vector<int> expected = {};
    std::vector<int> nums = {2, 8, 11, 15};
    REQUIRE(expected == solution.twoSum(nums, target));
    }

    {
    int target = 9;
    std::vector<int> expected = {0, 1};
    std::vector<int> nums = {2, 7, 11, 15};
    REQUIRE(expected == solution.twoSum(nums, target));
    }


    {
    int target = 9;
    std::vector<int> expected = {3, 4};
    std::vector<int> nums = {1, 90, 20, 2, 7, 11, 15};
    REQUIRE(expected == solution.twoSum(nums, target));
    }

    {
    int target = 3;
    std::vector<int> expected = {0, 2};
    std::vector<int> nums = {1, 90, 2, 2, 7, 11, 15};
    REQUIRE(expected == solution.twoSum(nums, target));
    }

    {
    int target = 101;
    std::vector<int> expected = {1, 5};
    std::vector<int> nums = {1, 90, 2, 2, 7, 11, 15};
    REQUIRE(expected == solution.twoSum(nums, target));
    }

}
