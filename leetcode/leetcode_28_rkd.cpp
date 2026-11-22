#include <string>
using namespace std;

class Solution
{
public:
    int strStr(string T, string P)
    {
        int n = T.length();
        int m = P.length();
        if (m > n)
            return -1;

        long long d1 = 256, q1 = 1000000007;
        long long d2 = 257, q2 = 1000000009;

        long long p_hash1 = 0, t_hash1 = 0, h1 = 1;
        long long p_hash2 = 0, t_hash2 = 0, h2 = 1;

        for (int i = 0; i < m - 1; i++)
        {
            h1 = (h1 * d1) % q1;
            h2 = (h2 * d2) % q2;
        }

        for (int i = 0; i < m; i++)
        {
            p_hash1 = (d1 * p_hash1 + P[i]) % q1;
            t_hash1 = (d1 * t_hash1 + T[i]) % q1;

            p_hash2 = (d2 * p_hash2 + P[i]) % q2;
            t_hash2 = (d2 * t_hash2 + T[i]) % q2;
        }

        for (int i = 0; i <= n - m; i++)
        {
            if (p_hash1 == t_hash1 && p_hash2 == t_hash2)
            {
                return i;
            }

            if (i < n - m)
            {
                t_hash1 = (d1 * (t_hash1 - T[i] * h1) + T[i + m]) % q1;
                if (t_hash1 < 0)
                    t_hash1 += q1;

                t_hash2 = (d2 * (t_hash2 - T[i] * h2) + T[i + m]) % q2;
                if (t_hash2 < 0)
                    t_hash2 += q2;
            }
        }

        return -1;
    }
};
