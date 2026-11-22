// LeetCode 28: Find the Index of the First Occurrence in a String
// Giai thuat: Vet can (Brute Force) - O(n * m)
#include <string>

class Solution {
public:
    int strStr(std::string haystack, std::string needle) {
        const int n = static_cast<int>(haystack.length());
        const int m = static_cast<int>(needle.length());

        if (m == 0) return 0;
        if (m > n) return -1;

        for (int i = 0; i <= n - m; ++i) {
            int j = 0;
            while (j < m && haystack[i + j] == needle[j]) {
                ++j;
            }
            if (j == m) {
                return i;
            }
        }
        return -1;
    }
};
