#include <algorithm>
#include <bit>
#include <cmath>
#include <vector>

class Solution {
private:
    static constexpr int firstSetBitR (int N) {
        int res {1};
        while (N) {
            if (N & 1) return res;
            N >>= 1; res <<= 1;
        }
        return 0;
    }

public:
    std::vector<int> findMissingRepeatingNumbers(std::vector<int> &&nums) {
        // XOR everything to get repeat ^ missing
        std::size_t N {nums.size()}; int repeatXmissing {};
        for (std::size_t i {}; i < N; ++i)
            repeatXmissing ^= static_cast<int>(i + 1) ^ nums[i];

        // Find first differentiating bit
        int setPos {std::countr_zero(static_cast<unsigned int>(repeatXmissing))}, 
            diffBit {static_cast<int>(std::pow(2, setPos))};

        // Seperate [1..N], [...nums] based on setPos & xor to find missing, repeated
        int n1 {}, n2 {};
        for (std::size_t i {}; i < N; ++i) {
            diffBit & static_cast<int>(i + 1)? n1 ^= i + 1: n2 ^= i + 1;
            diffBit & nums[i]? n1 ^= nums[i]: n2 ^= nums[i];
        }
        
        // Figure out which is which (n1 = repeat or missing?)
        return {
            std::find(nums.begin(), nums.end(), n1) != nums.end()? 
            std::vector<int>{n1, n2}: std::vector<int>{n2, n1}
        };
    }
};
