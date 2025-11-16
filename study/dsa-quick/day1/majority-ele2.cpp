// https://leetcode.com/problems/majority-element-ii
#include <vector>

class Solution {
public:
    // Same as majority element - I, only intution required is that 
    // there can only be a max of 2 elements that satisfy the criteria
    std::vector<int> majorityElement(std::vector<int>& nums) {
        // Bayer Moore's voting algorithm extended for 2 elements
        int ele1 {nums[0]}, ele2 {nums[1]}; 
        std::size_t cnt1 {}, cnt2 {};
        for (int n: nums) {
            if (n == ele1) ++cnt1;
            else if (n == ele2) ++cnt2;
            else if (cnt1 == 0) ele1 = n, cnt1 = 1;
            else if (cnt2 == 0) ele2 = n, cnt2 = 1;
            else --cnt1, --cnt2;
        }

        // Check if indeed these two are majority elements
        cnt1 = cnt2 = 0;
        for (int n: nums) {
            if (n == ele1) ++cnt1;
            else if (n == ele2) ++cnt2;
        }

        std::vector<int> res;
        if (cnt1 > nums.size() / 3) res.push_back(static_cast<int>(ele1));
        if (cnt2 > nums.size() / 3) res.push_back(static_cast<int>(ele2));
        return res;
    }
};
