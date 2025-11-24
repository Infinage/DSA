#include <string>
#include <vector>

class Solution {
private:
    static bool canPlace(const auto &board, std::size_t row, std::size_t col) {
        std::size_t N {board.size()};
        for (std::size_t i {}; i < N; ++i) 
            if (board[row][i] == 'Q') return false;
        for (std::size_t i {}; i < N; ++i) 
            if (board[i][col] == 'Q') return false;
        for (std::size_t i {row}, j {col}; i-- > 0 && j-- > 0;)
            if (board[i][j] == 'Q') return false;
        for (std::size_t i {row}, j {col}; i-- > 0 && j++ < N;)
            if (board[i][j] == 'Q') return false;
        return true;
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(std::size_t N) {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> board(N, std::string(N, '.'));
        auto backtrack {[&board, &res] (auto &&self, std::size_t row) {
            if (row >= board.size()) { res.push_back(board); return; }
            for (std::size_t col {}; col < board.size(); ++col) {
                if (canPlace(board, row, col)) {
                    board[row][col] = 'Q';
                    self(self, row + 1);
                    board[row][col] = '.';
                }
            }
        }};
        backtrack(backtrack, 0); return res;
    }
};
