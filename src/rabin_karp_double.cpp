#include "utils.h"
#include <string>
#include <chrono>

using namespace std;

RunResult rabin_karp_double_hash_perfect(const string &T, const string &P)
{
    long long ops = 0;
    int n = T.length();
    int m = P.length();
    int count = 0;

    if (m > n)
        return {0, 0, 0};

    auto start = chrono::high_resolution_clock::now();

    long long d1 = 256;
    long long d2 = 313;
    long long q1 = 1000000007;
    long long q2 = 1000000009;

    long long p_hash1 = 0, p_hash2 = 0;
    long long t_hash1 = 0, t_hash2 = 0;
    long long h1 = 1, h2 = 1;

    for (int i = 0; i < m - 1; i++)
    {
        h1 = (h1 * d1) % q1;
        h2 = (h2 * d2) % q2;
    }

    for (int i = 0; i < m; i++)
    {
        p_hash1 = (d1 * p_hash1 + P[i]) % q1;
        p_hash2 = (d2 * p_hash2 + P[i]) % q2;

        t_hash1 = (d1 * t_hash1 + T[i]) % q1;
        t_hash2 = (d2 * t_hash2 + T[i]) % q2;
    }

    for (int i = 0; i <= n - m; i++)
    {
        if (p_hash1 == t_hash1 && p_hash2 == t_hash2)
        {
            bool match = true;
            for (int j = 0; j < m; j++)
            {
                ops++;
                if (T[i + j] != P[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
                count++;
        }

        // Cuộn băm kép với công thức riêng cho từng cặp (d, q)
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

    auto end = chrono::high_resolution_clock::now();
    long long duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    return {duration, ops, count};
}
