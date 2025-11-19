#include <algorithm>
#include <vector>

class Solution {
public:
    int aggressiveCows(std::vector<int> &nums, int k) {
        auto check {[&nums, k](int distance) -> bool {
            int prevPos {nums[0] - distance}, assigned {};
            for (int pos: nums) {
                if (pos - prevPos >= distance) 
                    prevPos = pos, ++assigned;
            }
            return assigned >= k;
        }};

        std::sort(nums.begin(), nums.end());
        int low {0}, high {nums.back() - nums.front()};
        while (low <= high) {
             int mid {(low + high) / 2};
             if (check(mid)) low = mid + 1;
             else high = mid - 1;
        }
        return high;
    }
};
