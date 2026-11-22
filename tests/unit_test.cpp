// Chương trình đọc bộ test nhỏ để kiểm tra tính đúng đắn.

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "../src/utils.h"

using namespace std;

int main()
{
    cout << "=== KIEM TRA TINH DUNG DAN TREN BO TEST NHO CO DAP AN BIET TRUOC ===\n\n";

    ifstream in("tests/small_test.txt");
    if (!in.is_open())
    {
        cerr << "Loi: Khong tim thay tep tests/small_test.txt! Hay chay gen_tests.cpp truoc.\n";
        return 1;
    }

    int num_tests;
    in >> num_tests;

    for (int t = 1; t <= num_tests; t++)
    {
        int n, m, expected_ans;
        string T, P;

        in >> n >> m >> expected_ans;
        in.ignore();
        getline(in, T);
        getline(in, P);

        int res_naive = naive_string_match(T, P).match_count;
        int res_kmp = kmp_string_match(T, P).match_count;
        int res_rk = rabin_karp_double(T, P).match_count;
        int res_bmh = bmh_string_match(T, P).match_count;

        assert(res_naive == expected_ans && "Sai o thuat toan Vet can!");
        assert(res_kmp == expected_ans && "Sai o thuat toan KMP!");
        assert(res_rk == expected_ans && "Sai o thuat toan Rabin-Karp!");
        assert(res_bmh == expected_ans && "Sai o thuat toan BMH!");

        cout << "[PASS] Test nho " << t << " (N=" << n << ", M=" << m
             << ") -> Dap an chuan: " << expected_ans << " | Ca 4 thuat toan deu khop!\n";
    }

    in.close();
    cout << "\n=== TAT CA CAC THUAT TOAN DEU DAT CHUAN 100% ===\n";
    return 0;
}
