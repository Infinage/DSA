// https://leetcode.com/problems/minimum-length-of-string-after-operations/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int minimumLength(std::string &str) {
        // Compute the freq
        std::vector<int> freq(26, 0);                 
        for (const char ch: str)
            freq[static_cast<std::size_t>(ch - 'a')]++;

        // If odd we are left with 1, else 2
        int removed {0};
        for (int n: freq)
            removed += n % 2? std::max(0, n - 1): std::max(0, n - 2);
        return static_cast<int>(str.size()) - removed;
    }
};

int main() {
    int T;
    std::cin >> T;
    Solution sol;
    while (T--) {
        std::string str;
        std::cin >> str;
        std::cout << sol.minimumLength(str) << "\n";
    }
    return 0;
}
