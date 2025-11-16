#include <vector>

class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        std::size_t N {nums.size()};
        int max {nums[0]}, prefix {1}, suffix {1};
        for (std::size_t i {}; i < N; ++i) {
            prefix *= nums[i]; suffix *= nums[N - i - 1];
            max = std::max({max, prefix, suffix});
            if (prefix == 0) prefix = 1;
            if (suffix == 0) suffix = 1;
        }
        return max;
    }
};
