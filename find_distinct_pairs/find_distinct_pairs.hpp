#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>

template <typename T>
struct distinct_compare {
    bool operator() (const std::pair<T, T>& left, const std::pair<T, T>& right) const {
        //Re-arrange pairs to be in the same order
        auto ordered_left = left.first < left.second ? left : std::make_pair(left.second, left.first);
        auto ordered_right = right.first < right.second ? right : std::make_pair(right.second, right.first);
        return ordered_left < ordered_right;
    }
};

int find_distinct_pairs(std::vector<int>& nums, long target) {
    const size_t nums_len = nums.size();

    if (nums_len < 2) return 0;

    std::unordered_map<int, int> map;
    //Store unique pairs
    //Do not use hashes for ints
    //as it is implementation defined
    //and GCC just returns numbers themself
    std::set<std::pair<int, int>, distinct_compare<int>> distinct_pairs;

    for (size_t idx = 0; idx < nums_len; idx++) {
        int diff = target - nums[idx];
        auto find = map.find(diff);

        if (find != map.end()) {
            distinct_pairs.emplace(find->first, nums[idx]);
        }

        map.emplace(nums[idx], static_cast<int>(idx));
    }

    return static_cast<int>(distinct_pairs.size());
}
