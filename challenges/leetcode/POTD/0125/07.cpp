#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

class Solution {
    public:
        std::vector<std::string> stringMatching(std::vector<std::string>& words) {
            // Sort in asc order
            std::sort(words.begin(), words.end(), [](const std::string &w1, const std::string &w2) { 
                return w1.size() < w2.size(); 
            });

            std::vector<std::string> result;
            for (std::size_t i {0}; i < words.size() - 1; i++) {
                for (std::size_t j {i + 1}; j < words.size(); j++) {
                    if (words[j].find(words[i]) != std::string::npos) {
                        result.push_back(words[i]); 
                        break;
                    }
                } 
            }

            return result;
        }
};

int main() {
    int T;
    std::cin >> T;
    Solution sol;
    while (T--) {
        std::size_t wordLen;
        std::cin >> wordLen;
        std::vector<std::string> words(wordLen);
        for (std::size_t i {0}; i < wordLen; i++)
            std::cin >> words[i];

        // Solve and print the result
        std::vector<std::string> result {sol.stringMatching(words)};
        for (const std::string &word: result)
            std::cout << word << ", ";
        std::cout << "\n";
    }
    return 0;
}
