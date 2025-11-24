#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(const std::vector<int> &candidates, int target) {
        std::size_t N {candidates.size()};
        std::vector<std::vector<int>> res; std::vector<int> curr;
        auto backtrack {[&res, &curr, N, &candidates] (auto &&self, std::size_t idx, int pending) {
            if (idx >= N) { if (pending == 0) res.push_back(curr); return; }
            else if (pending < 0) return;
            curr.push_back(candidates[idx]);
            self(self, idx, pending - candidates[idx]); // Pick
            curr.pop_back();
            self(self, idx + 1, pending); // No pick
        }};
        backtrack(backtrack, 0, target);
        return res;
    }
};
