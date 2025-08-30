// https://leetcode.com/problems/sort-colors/
#include <vector>

class Solution {
public:
    void sortColors(std::vector<int> &nums) {
        // Dutch National flag algorithm
        // [0,        low - 1] -> 0s
        // [low,      mid - 1] -> 1s
        // [mid,         high] -> unsorted
        // [high + 1,   N - 1] -> 2s
        std::size_t low {0}, mid {0}, high {nums.size() - 1};
        while (mid <= high) {
            if (nums[mid] == 0) std::swap(nums[low++], nums[mid++]);
            else if (nums[mid] == 1) ++mid;
            else {
                std::swap(nums[mid], nums[high]); 
                if (high > 0) --high; 
                else break;
            } 
        }
    }
};
