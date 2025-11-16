// https://leetcode.com/problems/3sum/
#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &&nums) {
        std::vector<std::vector<int>> res;
        std::size_t N {nums.size()};
        if (N < 3) return {};
        std::ranges::sort(nums);
        for (std::size_t i {}; i < N - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            auto j {i + 1}, k {N - 1};
            while (j < k) {
                int sum {nums[i] + nums[j] + nums[k]};
                if (sum < 0) ++j;
                else if (sum > 0) --k;
                else {
                    res.push_back({nums[i], nums[j++], nums[k--]});
                    while (j < k && nums[j] == nums[j - 1]) ++j;
                    while (j < k && nums[k] == nums[k + 1]) --k;
                }
            }
        }
        return res;
    }
};
