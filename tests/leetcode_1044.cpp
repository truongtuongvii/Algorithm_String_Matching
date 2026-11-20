// LeetCode 1044: Longest Duplicate Substring
// Giai thuat: Rabin-Karp (Double Rolling Hash) + Binary Search - O(n log n)
#include <cstdint>
#include <string>
#include <unordered_set>

class Solution {
private:
    int findDuplicateOfLength(int len, const std::string& s) {
        const int n = static_cast<int>(s.length());
        constexpr long long BASE1 = 31, MOD1 = 1000000007LL;
        constexpr long long BASE2 = 37, MOD2 = 1000000009LL;

        long long h1 = 0, h2 = 0, p1 = 1, p2 = 1;
        for (int i = 0; i < len; ++i) {
            int val = s[i] - 'a' + 1;
            h1 = (h1 * BASE1 + val) % MOD1;
            h2 = (h2 * BASE2 + val) % MOD2;
            if (i > 0) {
                p1 = (p1 * BASE1) % MOD1;
                p2 = (p2 * BASE2) % MOD2;
            }
        }

        std::unordered_set<uint64_t> seen;
        seen.reserve(n - len + 1);
        seen.insert((static_cast<uint64_t>(h1) << 32) | static_cast<uint64_t>(h2));

        for (int i = len; i < n; ++i) {
            int out_val = s[i - len] - 'a' + 1;
            int in_val  = s[i] - 'a' + 1;

            h1 = ((h1 - out_val * p1) % MOD1 + MOD1) % MOD1;
            h1 = (h1 * BASE1 + in_val) % MOD1;

            h2 = ((h2 - out_val * p2) % MOD2 + MOD2) % MOD2;
            h2 = (h2 * BASE2 + in_val) % MOD2;

            uint64_t combined = (static_cast<uint64_t>(h1) << 32) | static_cast<uint64_t>(h2);
            if (seen.count(combined)) {
                return i - len + 1;
            }
            seen.insert(combined);
        }
        return -1;
    }

public:
    std::string longestDupSubstring(std::string s) {
        int low = 1, high = static_cast<int>(s.length()) - 1;
        int start = -1, maxLen = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int idx = findDuplicateOfLength(mid, s);
            if (idx != -1) {
                maxLen = mid;
                start = idx;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return (start == -1) ? "" : s.substr(start, maxLen);
    }
};
