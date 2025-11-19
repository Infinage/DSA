#include <unordered_map>
#include <vector>

class Solution{
public:
    int subarraySum(std::vector<int> &nums, int k){
        std::unordered_map<int, int> prefixes {{0, 1}}; 
        int res {};
        for (int sum{}; int n: nums) {
            sum += n; 
            res += prefixes[sum - k];
            ++prefixes[sum];
        }
        return res;
    }
};
