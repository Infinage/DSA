#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
public:
    std::vector<int> findThePrefixCommonArray(std::vector<int>& A, std::vector<int>& B) {
        std::unordered_set<int> distinct;
        std::size_t N {A.size()};
        std::vector<int> result;
        for (std::size_t i {0}; i < N; i++) {
            int curr {result.empty()? 0: result.back()}, n1 {A[i]}, n2 {B[i]};
            if (distinct.find(n1) != distinct.end()) curr++;
            if (distinct.find(n2) != distinct.end()) curr++;
            if (n1 == n2) curr++;

            distinct.insert(n1);
            distinct.insert(n2);

            result.push_back(curr);
        }

        return result;
    }
};

int main() {
    int T;
    std::cin >> T;
    Solution sol;
    while (T--) {
        std::size_t N; 
        std::cin >> N;
        std::vector<int> arr1(N), arr2(N);
        for (std::size_t i {0}; i < N; i++)
            std::cin >> arr1[i];
        for (std::size_t i {0}; i < N; i++)
            std::cin >> arr2[i];

        std::vector<int> result {sol.findThePrefixCommonArray(arr1, arr2)};
        for (std::size_t i {0}; i < N; i++)
            std::cout << result[i] << " ";
        std::cout << "\n";
    }
    return 0;
}
