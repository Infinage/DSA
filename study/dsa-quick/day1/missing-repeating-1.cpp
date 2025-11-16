#include <vector>

class Solution {
public:
    std::vector<int> findMissingRepeatingNumbers(std::vector<int> &nums) {
        // Compute totals: sum and sum of squares
        long asum {}, esum {}, asum2 {}, esum2 {};     
        for (std::size_t i {}; i < nums.size(); ++i) {
            asum += nums[i]; asum2 += nums[i] * nums[i];
            esum += i + 1; esum2 += (i + 1) * (i + 1);
        }

        // Solve for equations to find missing (x), repeated (y)
        // 1) esum - asum = x - y
        // 2) esum2 - asum2 = x2 - y2 = (x + y) * (x - y)
        // 3) (esum2 - asum2) / (x - y) = x + y
        // 4) 2x = esum - asum + ((esum2 - asum2) / (esum - asum))
        // 5) y = asum - esum + x;
        long missing {((esum - asum) + ((esum2 - asum2) / (esum - asum))) / 2};
        long repeated {asum - esum + missing};
        return {static_cast<int>(repeated), static_cast<int>(missing)};
    }
};
