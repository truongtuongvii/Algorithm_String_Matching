#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "../src/utils.h"

using namespace std;

// Hàm ghi cặp chuỗi (T, P) ra tệp .txt theo chuẩn
void save_test_to_file(const string &filepath, const string &T, const string &P)
{
    ofstream out(filepath);
    if (!out.is_open())
    {
        cerr << "Loi: Khong the tao tep " << filepath << " (Kiem tra thu muc tests/inputs/)\n";
        return;
    }
    out << T.length() << " " << P.length() << "\n";
    out << T << "\n";
    out << P << "\n";

    out.close();
}

void create_known_small_test()
{
    ofstream out("tests/small_test.txt");
    if (!out.is_open())
        return;

    out << "3\n"; // Số lượng test case trong tệp

    // Test 1: Văn bản thường (Đáp án biết trước: 2)
    out << "19 4 2\n";
    out << "ABABDABACDABABCABAB\n";
    out << "ABAB\n";

    // Test 2: Chuỗi DNA chồng lấn (Đáp án biết trước: 4)
    out << "6 3 4\n";
    out << "AAAAAA\n";
    out << "AAA\n";

    // Test 3: Không tìm thấy (Đáp án biết trước: 0)
    out << "8 4 0\n";
    out << "ATCGATCG\n";
    out << "GGGG\n";

    out.close();
    cout << "Da tao tep test nho co dap an biet truoc: tests/small_test.txt\n\n";
}

int main()
{
    cout << "=== SINH TOAN BO DU LIEU KIEM THU ===\n\n";

    // Tạo bộ test nhỏ có đáp án đã biết
    std::filesystem::create_directories("tests/inputs");
    create_known_small_test();

    // Sinh 8 mức kích thước đầu vào (từ 500 đến 500,000)
    vector<int> sizes = {500, 1000, 5000, 10000, 50000, 100000, 250000, 500000};
    int m = 15;

    for (int n : sizes)
    {
        string s = to_string(n);

        // Bộ 1: Ngẫu nhiên - Chuỗi DNA (4 ký tự)
        save_test_to_file("tests/inputs/1_dna_" + s + ".txt",
                          generate_random_string(n, "ATCG"),
                          generate_random_string(m, "ATCG"));

        // Bộ 2: Ngẫu nhiên - Chuỗi Nhị phân (2 ký tự)
        save_test_to_file("tests/inputs/2_binary_" + s + ".txt",
                          generate_random_string(n, "01"),
                          generate_random_string(m, "01"));

        // Bộ 3: Ngẫu nhiên - Văn bản Tiếng Anh (27 ký tự)
        save_test_to_file("tests/inputs/3_english_" + s + ".txt",
                          generate_random_string(n, "abcdefghijklmnopqrstuvwxyz "),
                          generate_random_string(m, "abcdefghijklmnopqrstuvwxyz "));

        // Bộ 4: Trường hợp tốt nhất (Best-case)
        pair<string, string> bc = generate_best_case(n, m);
        save_test_to_file("tests/inputs/4_best_" + s + ".txt", bc.first, bc.second);

        // Bộ 5: Trường hợp xấu nhất (Worst-case)
        pair<string, string> wc = generate_worst_case(n, m);
        save_test_to_file("tests/inputs/5_worst_" + s + ".txt", wc.first, wc.second);

        cout << "Da sinh du 5 bo du lieu cho muc kich thuoc N = " << n << "\n";
    }

    cout << "\n=== HOAN TAT! Da tao 1 tep test nho va 40 tep du lieu thuc nghiem ===\n";
    return 0;
}
