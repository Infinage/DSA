// https://leetcode.com/problems/majority-element-ii
#include <cmath>
#include <vector>

class Solution {
public:
    // Same as majority element - I, only intution required is that 
    // there can only be a max of 2 elements that satisfy the criteria
    std::vector<int> majorityElement(std::vector<int>& nums) {
        // Apply algo as majority ele 1
        int maxi1 {}, maxi2 {}, maxc1 {}, maxc2 {};
        for (int n: nums) {
            if (maxc1 == 0 && maxi2 != n) { maxi1 = n; maxc1 = 1; }
            else if (maxc2 == 0 && maxi1 != n) { maxi2 = n; maxc2 = 1; }
            else if (maxi1 == n) ++maxc1;
            else if (maxi2 == n) ++maxc2;
            else { --maxc1; --maxc2; }
        }

        // Check if counts > floor(N / 3)
        maxc1 = 0; maxc2 = 0;
        for (int n: nums) {
            if (n == maxi1) ++maxc1;
            if (n == maxi2) ++maxc2;
        }

        // Only return if counts are okay
        std::vector<int> res;
        auto expected {std::floor(nums.size() / 3)};
        if (maxc1 > expected) res.push_back(maxi1);
        if (maxc2 > expected) res.push_back(maxi2);
        return res;
    }
};
