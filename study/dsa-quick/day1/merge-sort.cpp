#include <vector>

class Solution {
private:
    void _merge(std::vector<int> &nums, std::size_t start, std::size_t end) {
        if (start >= end) return;
        std::size_t mid {(start + end) / 2};
        _merge(nums, start, mid); 
        _merge(nums, mid + 1, end); 

        // Insert in sorted order to temp array
        std::vector<int> temp; temp.reserve(end - start + 1);
        std::size_t left {start}, right {mid + 1};
        while (left <= mid || right <= end) {
            if (right > end || (left <= mid && nums[left] < nums[right])) {
                temp.push_back(nums[left++]);
            } else {
                temp.push_back(nums[right++]);
            }
        }

        // Write back from temp array
        std::copy(temp.begin(), temp.end(), 
            nums.begin() + static_cast<unsigned int>(start));
    }

public:
    std::vector<int> mergeSort(std::vector<int>& nums) {
        _merge(nums, 0, nums.size() - 1); 
        return nums;
    }
};
