#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        std::ranges::sort(candidates);
        std::size_t N {candidates.size()};
        std::vector<std::vector<int>> res; std::vector<int> curr;
        auto backtrack {[&res, &curr, N, &candidates] (auto &&self, std::size_t idx, int pending) {
            if (idx >= N) { if (pending == 0) res.push_back(curr); return; }
            else if (pending < 0) return;

            // Pick portion
            curr.push_back(candidates[idx]);
            self(self, idx + 1, pending - candidates[idx]);
            curr.pop_back();

            // No pick portion (if we decide not to pick a num, don't 
            // pick any other num that we may encounter)
            std::size_t next {idx + 1};
            while (next < N && candidates[idx] == candidates[next]) ++next;
            self(self, next, pending);
        }};
        backtrack(backtrack, 0, target);
        return res;
    }
};
