#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    int firstCompleteIndex(std::vector<int>& arr, std::vector<std::vector<int>>& mat) {
        std::size_t M {mat.size()}, N {mat[0].size()};

        // Quicker lookups
        std::unordered_map<int, std::pair<std::size_t, std::size_t>> mapping;
        for (std::size_t i {0}; i < M; i++) {
            for (std::size_t j {0}; j < N; j++) {
                int val {mat[i][j]};
                mapping[val] = {i, j};
            }
        }

        // Counters
        std::vector<std::size_t> rows(M, 0UL), cols(N, 0UL);

        // Start painting
        for (std::size_t i {0}; i < arr.size(); i++) {
           std::size_t row, col; 
           int val {arr[i]};
           std::tie(row, col) = mapping[val];
           rows[row]++; cols[col]++;
           if (rows[row] == N || cols[col] == M) 
               return static_cast<int>(i);
        }

        return -1;
    }
};
