#include <functional>
#include <numeric>
#include <vector>

class Solution {
public:
    std::vector<int> singleNumber(const std::vector<int> &nums) {        
        // XOR all nums
        int _xor {std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>())};

        // Find the first set bit to differentiate the nums into 2 groups
        int dBit {(_xor & (_xor - 1)) ^ _xor};

        // Iterate across nums and bucket them based on dBit
        int n1 {}, n2 {};
        for (int n: nums) {
            if (dBit & n) n1 ^= n;
            else n2 ^= n;
        }

        return n1 < n2? std::vector{n1, n2}: std::vector{n2, n1};
    }
};
