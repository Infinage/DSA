#include <array>
#include <vector>

class Solution {
public:
    int singleNumber(const std::vector<int> &nums) {        
        // Do a bit wise 'addition'
        std::array<int, 32> bitCs {};
        for (int n: nums) {
            for (std::size_t curr {}; curr < 32; ++curr)
                if ((1 << curr) & n) ++bitCs[curr];
        }

        // Reconstruct the single number
        int res {};
        for (std::size_t curr {}; curr < 32; ++curr)
            if (bitCs[curr] % 3) res += 1 << curr;

        return res;
    }
};
