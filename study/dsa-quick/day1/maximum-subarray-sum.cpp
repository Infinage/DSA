// https://leetcode.com/problems/maximum-subarray
#include <limits>
#include <vector>

class Solution {
public:
    std::vector<int> maxSubArray(const std::vector<int> &nums) {
        int max {std::numeric_limits<int>::min()}, sum {};
        long long ansBeg {}, ansEnd {}, currBeg {}, N {static_cast<long long>(nums.size())};
        for (long long i {}; i < N; ++i) {
            sum += nums[static_cast<std::size_t>(i)];

            // Update max and beg / end indices of ans
            if (sum > max) { max = sum; ansBeg = currBeg; ansEnd = i; }

            // Reset tot sum and beginning
            if (sum < 0) { sum = 0; currBeg = i; }
        }

        // Returning subarray
        return {nums.begin() + ansBeg, nums.begin() + ansEnd};
    }
};
