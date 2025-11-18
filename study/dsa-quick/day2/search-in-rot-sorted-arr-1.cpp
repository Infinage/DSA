#include <vector>

class Solution {
public:
    // Identify the sorted half and check if target can exist inside it
    int search(std::vector<int> &nums, int k) {
        int low {0}, high {static_cast<int>(nums.size() - 1)};
        while (low <= high) {
            int mid {(low + high) / 2};
            if (nums[mid] == k) return mid;
            else if (nums[low] <= nums[mid]) {
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
        return -1;
    }
};
