#include <algorithm>
#include <vector>

class Solution {
public:
    int reversePairs(std::vector<int> &nums) {
        auto backtrack {[&nums](auto &&self, std::size_t start, std::size_t end) -> int {
            if (start >= end) return 0;
            std::size_t mid {(start + end) / 2};
            int res {self(self, start, mid) + self(self, mid + 1, end)};
            std::vector<int> temp; temp.reserve(end - start + 1);
            std::size_t left {start}, right {mid + 1};
            while (left <= mid || right <= end) {
                if (right > end || (left <= mid && nums[left] <= nums[right]))
                    temp.push_back(nums[left++]);
                else {
                    // The startit can be left, but then it won't work with negatives
                    // With startit being start, it will work even for cases like [-3, -2]
                    // Doubling a negative pushes it more negative, changing relative ordering.
                    // An element early in the left half might be a valid match for 
                    // nums[right] even if left has advanced past it.
                    auto startIt {nums.begin() + start}, endIt {nums.begin() + mid + 1};
                    auto it {std::upper_bound(startIt, endIt, static_cast<long>(nums[right]) * 2)};
                    res += endIt - it;
                    temp.push_back(nums[right++]);
                }
            }
            std::copy(temp.begin(), temp.end(), nums.begin() + static_cast<long>(start));
            return res;
        }};

        return backtrack(backtrack, 0, nums.size() - 1);
    }
};
