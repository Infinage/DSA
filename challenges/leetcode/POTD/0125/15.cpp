#include <iostream>

class Solution {
    public:
        int minimizeXor(int num1, int num2) {
            // Count no of set bits in num2            
            int bits {0};
            while (num2) {
                bits += num2 & 1;
                num2 >>= 1;
            }

            // Go from left to right
            int mask {1 << 30};
            int result {0};
            while (bits && mask) {
                if (mask & num1) {
                    result += mask;
                    bits--;
                }
                mask >>= 1;
            }

            // Go from right to left
            mask = 1;
            while (bits) {
                if (!(mask & num1)) {
                    result += mask;
                    bits--;
                }
                mask <<= 1;
            }

            return result;
        }
};

int main() {
    int T;
    std::cin >> T;
    Solution sol;
    while(T--) {
        int n1, n2;
        std::cin >> n1 >> n2;
        std::cout << sol.minimizeXor(n1, n2) << "\n";
    }
    return 0;
}
