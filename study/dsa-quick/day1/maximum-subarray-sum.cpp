// https://leetcode.com/problems/maximum-subarray
#include <vector>

class Solution {
public:
    std::vector<int> maxSubArray(const std::vector<int> &nums) {
        int sum {}, max {nums[0]};
        long start {}, length {};
        for (std::size_t i {}; i < nums.size(); ++i) {
            sum += nums[i], ++length;
            if (sum > max) {
                max = sum;
                start = static_cast<long>(i) - (length - 1);
            }
            if (sum < 0) length = sum = 0;
        }
        return {nums.begin() + start, nums.begin() + start + length};
    }
};
