// DNA sử dụng giải thuật Rabin-karp double

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        int n = s.length();
        int m = 10;
        vector<string> res;
        if (n <= m)
            return res;

        long long d1 = 256, q1 = 1000000007;
        long long d2 = 257, q2 = 1000000009;

        long long hash1 = 0, h1 = 1;
        long long hash2 = 0, h2 = 1;

        for (int i = 0; i < m - 1; i++)
        {
            h1 = (h1 * d1) % q1;
            h2 = (h2 * d2) % q2;
        }

        for (int i = 0; i < m; i++)
        {
            hash1 = (d1 * hash1 + s[i]) % q1;
            hash2 = (d2 * hash2 + s[i]) % q2;
        }

        unordered_map<long long, int> count;

        long long combined_hash = (hash1 << 32) | hash2;
        count[combined_hash] = 1;

        for (int i = 0; i < n - m; i++)
        {
            hash1 = (d1 * (hash1 - s[i] * h1) + s[i + m]) % q1;
            if (hash1 < 0)
                hash1 += q1;

            hash2 = (d2 * (hash2 - s[i] * h2) + s[i + m]) % q2;
            if (hash2 < 0)
                hash2 += q2;

            combined_hash = (hash1 << 32) | hash2;
            count[combined_hash]++;

            if (count[combined_hash] == 2)
            {
                res.push_back(s.substr(i + 1, m));
            }
        }

        return res;
    }
};
