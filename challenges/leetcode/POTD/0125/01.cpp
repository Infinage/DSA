#include <algorithm>
#include <string>
#include <iostream>

class Solution {
public:
    int maxScore(std::string &s) {
        std::size_t zeroes {0}, max {0}; 
        std::size_t ones {static_cast<std::size_t>(std::count(s.begin(), s.end(), '1'))};
        for (std::size_t i {0}; i < s.size() - 1; i++) {
            if (s[i] == '0') zeroes++;
            else ones--;
            max = std::max(max, zeroes + ones);
        }

        return static_cast<int>(max);
    }
};

int main() {
    int T;
    std::cin >> T;
    Solution sol;
    while (T--) {
        std::string str;
        std::cin >> str;
        std::cout << sol.maxScore(str) << "\n";
    }
    return 0;
}
