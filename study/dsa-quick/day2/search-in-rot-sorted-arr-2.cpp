#include <vector>

class Solution {
public:
    // Same as prev problem, but can be problematic when
    // Eg: [[3], 1, 2, [3], 3, 3, [3]]
    //
    // In this case we wouldn't know which half is sorted
    // Solution is we simply trim down the search space: O(N) worst case
    bool searchInARotatedSortedArrayII(std::vector<int> &nums, int k)  {
        int low {0}, high {static_cast<int>(nums.size()) - 1}; 
        while (low <= high) {
            int mid {(low + high) / 2};
            if (nums[mid] == k) return true;
            else if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
                ++low; --high;
            } else if (nums[low] <= nums[mid]) {
                if (nums[low] <= k && k <= nums[mid]) 
                    high = mid - 1;
                else 
                    low = mid + 1;
            } else {
                if (nums[mid] <= k && k <= nums[high])
                    low = mid + 1;
                else 
                    high = mid - 1;
            }
        }
        return false;
    }
};
