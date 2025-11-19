#include <print>
#include <queue>
#include <vector>

class Solution {
public:
    double median(const std::vector<int> &arr1, const std::vector<int> &arr2) {
        std::size_t i {}, j {}, N1 {arr1.size()}, N2 {arr2.size()}, 
            N {(N1 + N2 + 1) / 2};

        auto push{[&N](auto &pq, int n) {
            pq.push(n); 
            if (pq.size() > N) 
                pq.pop();
        }};

        std::priority_queue<int> maxPq;
        std::priority_queue<int, std::vector<int>, std::greater<>> minPq; 

        while (i < N1 || j < N2) {
             if (j >= N2 || (i < N1 && arr1[i] < arr2[j])) {
                 push(minPq, arr1[i]); push(maxPq, arr1[i]); ++i;
             } else {
                 push(minPq, arr2[j]); push(maxPq, arr2[j]); ++j;
             }
        }

        return (maxPq.top() + minPq.top()) / 2.;
    }
};

int main() {
    Solution sol; 
    std::println("{}", sol.median({2, 4, 6}, {1, 3, 5}));
}
