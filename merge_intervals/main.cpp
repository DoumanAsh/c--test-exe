#include <cassert>

#include <utility>
#include <algorithm>
#include <vector>

using interval = std::pair<size_t, size_t>;
using i_vector = std::vector<interval>;

/**
 * Merges overlapping intervals in place.
 *
 * Performs initial sorting to allow simple linear loop further on
 * As loop goes one, we identify overlaps, merge it and then decrement number of actual elements
 * On exit we trim vector up to the number of remaining intervals
 */
static void merge_intervals(i_vector& intervals) {
    size_t size = intervals.size();
    if (size == 0) return;

    //We assume that left <= right
    std::sort(intervals.begin(), intervals.end(), [](auto left, auto right) {
        return left.first < right.first;
    });

    //Start of leftovers from merges
    //Since we always has at least one interval we can start from it
    size_t partition = 1;

    for (size_t idx = 1; idx < size; idx++) {
        if (intervals[partition-1].second >= intervals[idx].first) {
            //If we're overlapping, then merge intervals.
            //Later we'll over-write old intervals with greater ones
            //Each overlapping interval is also excluded from final results so that we could shrink vector.
            intervals[partition-1].first = std::min(intervals[partition-1].first, intervals[idx].first);
            intervals[partition-1].second = std::max(intervals[partition-1].second, intervals[idx].second);
            partition--;
        } else {
            intervals[partition] = intervals[idx];
        }

        partition++;
    }

    intervals.resize(partition);
    intervals.shrink_to_fit();
}

int main() {
    i_vector input  = { {1,3}, {8,10}, {2,6}, {15,18}, {18,21} };
    i_vector expected = { {1, 6}, {8, 10}, {15, 21} };
    merge_intervals(input);
    assert(input == expected);

    input = { {1,3}, {1,10}, {2,6}, {15,17}, {18,21} };
    expected = { {1, 10}, {15, 17}, {18, 21} };
    merge_intervals(input);
    assert(input == expected);

    input = { {1,10}, {1,10}, {2,6}, {10,20}, {2,19} };
    expected = { {1, 20} };
    merge_intervals(input);
    assert(input == expected);

    input = { };
    expected = { };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,10}, {15,25}, {35, 45}, {55, 100}, {1, 5} };
    expected = { {1,10}, {15,25}, {35, 45}, {55, 100} };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,10}, {10, 20} };
    expected = { {2, 20} };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,20}, {5, 25} };
    expected = { {2, 25} };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,20}, {5, 15} };
    expected = { {2, 20} };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,20}, {1, 25} };
    expected = { {1, 25} };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,20}, {20, 25} };
    expected = { {2, 25} };
    merge_intervals(input);
    assert(input == expected);

    input = { {5,10}, {1,3} };
    expected = { {1, 3}, {5, 10} };
    merge_intervals(input);
    assert(input == expected);

    input = { {1, 2}, {3, 4}, {10, 15}, {5, 9} };
    expected = { {1, 2}, {3, 4}, {5, 9}, {10, 15} };
    merge_intervals(input);
    assert(input == expected);

    input = { {5,10}, {1,3}, {2, 4}, {11, 20} };
    expected = { {1, 4}, {5, 10}, {11, 20} };
    merge_intervals(input);
    assert(input == expected);

    input = { {2,10}, {15,25}, {20, 45}, {55, 100}, {55, 100}, {1, 5} };
    expected = { {1,10}, {15,45}, {55, 100} };
    merge_intervals(input);
    assert(input == expected);

    input = { {16, 18}, {16, 18}, {9, 10}, {12, 14}, {12, 15}, {13, 4}, {14, 16}, {15, 17}, {15, 16}, {16, 18}, {2, 5}, {6, 8}, };
    expected = { {2, 5}, {6, 8}, {9, 10}, {12, 18} };
    merge_intervals(input);
    assert(input == expected);

    input = { {6, 8}, {1, 9}, {2, 4}, {4, 7}, {2, 4}, {3, 5} };
    expected = { {1, 9} };
    merge_intervals(input);
    assert(input == expected);

    return 0;
}
