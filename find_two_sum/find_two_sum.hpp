#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> result;
        const size_t nums_len = nums.size();

        if (nums_len < 2) return result;

        std::unordered_map<int, int> map;

        for (size_t idx = 0; idx < nums_len; idx++) {
            int diff = target - nums[idx];
            auto find = map.find(diff);

            if (find != map.end()) {
                result.push_back(find->second);
                result.push_back(static_cast<int>(idx));
                break;
            }

            map.insert({nums[idx], static_cast<int>(idx)});
        }

        return result;
    }
};
