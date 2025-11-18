#include <algorithm>
#include <vector>

class Solution{
public:
    int search(std::vector<int> &nums, int target) {
        return std::binary_search(nums.begin(), nums.end(), target);
        int low {1}, high {static_cast<int>(nums.size())};
        while (low <= high) {
            int mid {(low + high) / 2};
            if (nums[mid] == target) return mid - 1;
            else if (nums[mid - 1] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }
};
