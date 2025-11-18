#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

class Solution {
public:
    int minimumRateToEatBananas(std::vector<int> &nums, int h) {
        auto check {[&nums, h](int b) -> bool {
            return std::accumulate(nums.begin(), nums.end(), 0ULL, 
            [b](std::size_t acc, double heap) {
                return acc + static_cast<unsigned>(std::ceil(heap / b)); 
            }) <= static_cast<unsigned>(h); 
        }};

        int low {1}, high {*std::max_element(nums.begin(), nums.end())};
        while (low <= high) {
            int mid {(low + high) / 2};
            if (check(mid)) high = mid - 1;
            else low = mid + 1;
        }

        return low;
    }
};
