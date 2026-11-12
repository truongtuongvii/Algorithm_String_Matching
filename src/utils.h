#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <random>

using namespace std;

struct RunResult
{
    long long execution_time_ns;
    long long basic_operations;
    int match_count;
};

// 2. Khai báo nguyên mẫu (Prototype) các hàm thuật toán
RunResult naive_string_match(const string &T, const string &P);
RunResult kmp_string_match(const string &T, const string &P);

RunResult rabin_karp_double(const string &T, const string &P);

RunResult bmh_string_match(const string &T, const string &P);

inline string generate_random_string(int length, const string &alphabet)
{
    string res;
    res.reserve(length); // Cấp phát trước bộ nhớ để sinh chuỗi lớn cực nhanh

    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(0, alphabet.length() - 1);

    for (int i = 0; i < length; i++)
    {
        res += alphabet[dis(gen)];
    }
    return res;
}

inline pair<string, string> generate_worst_case(int n, int m)
{
    string T(n, 'A');
    string P(m - 1, 'A');
    P += 'B';
    return {T, P};
}

#endif
