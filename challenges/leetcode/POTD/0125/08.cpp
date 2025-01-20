#include <vector>
#include <string>

class Solution {
private:
    bool isPrefixAndSuffix(std::string &w1, std::string &w2) {
        std::size_t N1 {w1.size()}, N2 {w2.size()};
        if (N1 > N2) return false; 
        else {
            // Check prefix & suffix
            for (std::size_t i {0}; i < N1; i++) {
                if (w1[i] != w2[i]) return false;
                if (w1[i] != w2[N2 - N1 + i]) return false;
            }

            return true;
        }
    }

public:
    int countPrefixSuffixPairs(std::vector<std::string>& words) {
        int result {0};
        for (std::size_t i {0}; i < words.size(); i++) {
            for (std::size_t j {i + 1}; j < words.size(); j++) {
                if (isPrefixAndSuffix(words[i], words[j])) 
                    result++;
            }
        }
        return result;
    }
};
