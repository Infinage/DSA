#include <vector>

class Solution {
private:
    long long int backtrack(std::vector<int> &nums, 
            std::size_t start, std::size_t end) 
    {
        if (start >= end) return 0ull;
        std::size_t mid {(start + end) / 2};
        long long int res {backtrack(nums, start, mid) + 
            backtrack(nums, mid + 1, end)};

        std::vector<int> temp; temp.reserve(end - start + 1);
        std::size_t left {start}, right {mid + 1};
        while (left <= mid || right <= end) {
            if (right > end || (left <= mid && nums[left] <= nums[right]))
                temp.push_back(nums[left++]);
            else {
                temp.push_back(nums[right++]);
                res += mid - left + 1;
            }
        }

        std::copy(temp.begin(), temp.end(), nums.begin() + static_cast<long>(start));
        return res;
    }

public:
    long long int numberOfInversions(std::vector<int> &nums) {
        return backtrack(nums, 0, nums.size() - 1);
    }
};
