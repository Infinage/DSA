// https://leetcode.com/problems/sort-colors/
#include <vector>

class Solution {
public:
    auto sortColors(std::vector<int> &nums) {
        long N {static_cast<long>(nums.size())}, start {}, end {N - 1}, i {};
        while (i <= end) {
           if (nums[i] == 0)  std::swap(nums[start++], nums[i++]);
           else if (nums[i] == 2) std::swap(nums[end--], nums[i]);
           else ++i;
        }
        return nums;
    }
};
