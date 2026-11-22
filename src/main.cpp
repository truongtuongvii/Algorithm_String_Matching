#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <filesystem>
#include "utils.h"

using namespace std;
namespace fs = std::filesystem;

double calculate_mean(const vector<long long> &data)
{
    double sum = 0.0;
    for (long long val : data)
    {
        sum += val;
    }
    return sum / data.size();
}

double calculate_stddev(const vector<long long> &data, double mean)
{
    double variance = 0.0;
    for (long long val : data)
    {
        variance += pow(val - mean, 2);
    }
    return sqrt(variance / data.size());
}

bool read_test_file(const string &filepath, string &T, string &P)
{
    ifstream in(filepath);
    if (!in.is_open())
    {
        cerr << "Khong the mo tep du lieu: " << filepath << "\n";
        return false;
    }
    int n, m;
    in >> n >> m;
    in.ignore();
    getline(in, T);
    getline(in, P);
    in.close();
    return true;
}

void run_scenario_benchmark(const string &prefix, const string &output_csv)
{
    ofstream out(output_csv);
    if (!out.is_open())
    {
        cerr << "Khong the tao tep ket qua: " << output_csv << "\n";
        return;
    }

    out << "Size_N,"
        << "Naive_Time_Avg,Naive_Time_Std,Naive_Ops,"
        << "KMP_Time_Avg,KMP_Time_Std,KMP_Ops,"
        << "RK_Time_Avg,RK_Time_Std,RK_Ops,"
        << "BMH_Time_Avg,BMH_Time_Std,BMH_Ops\n";

    vector<int> sizes = {500, 1000, 5000, 10000, 50000, 100000, 250000, 500000};
    int num_runs = 5;

    cout << "Dang chay thuc nghiem kich ban [" << prefix << "]...\n";

    for (int n : sizes)
    {
        string filepath = "tests/inputs/" + prefix + "_" + to_string(n) + ".txt";
        string T, P;

        if (!read_test_file(filepath, T, P))
        {
            return;
        }

        vector<long long> n_times, k_times, r_times, b_times;
        long long n_ops = 0, k_ops = 0, r_ops = 0, b_ops = 0;

        for (int run = 0; run < num_runs; run++)
        {
            RunResult res_n = naive_string_match(T, P);
            RunResult res_k = kmp_string_match(T, P);
            RunResult res_r = rabin_karp_double(T, P);
            RunResult res_b = bmh_string_match(T, P);

            if (res_n.match_count != res_k.match_count ||
                res_n.match_count != res_r.match_count ||
                res_n.match_count != res_b.match_count)
            {
                cerr << "Sai lech ket qua tim kiem tai tep: " << filepath << "\n";
                return;
            }

            n_times.push_back(res_n.execution_time_ns);
            k_times.push_back(res_k.execution_time_ns);
            r_times.push_back(res_r.execution_time_ns);
            b_times.push_back(res_b.execution_time_ns);

            n_ops = res_n.basic_operations;
            k_ops = res_k.basic_operations;
            r_ops = res_r.basic_operations;
            b_ops = res_b.basic_operations;
        }

        double n_avg = calculate_mean(n_times), n_std = calculate_stddev(n_times, n_avg);
        double k_avg = calculate_mean(k_times), k_std = calculate_stddev(k_times, k_avg);
        double r_avg = calculate_mean(r_times), r_std = calculate_stddev(r_times, r_avg);
        double b_avg = calculate_mean(b_times), b_std = calculate_stddev(b_times, b_avg);

        out << n << ","
            << n_avg << "," << n_std << "," << n_ops << ","
            << k_avg << "," << k_std << "," << k_ops << ","
            << r_avg << "," << r_std << "," << r_ops << ","
            << b_avg << "," << b_std << "," << b_ops << "\n";

        cout << " Hoan thanh muc N = " << n << "\n";
    }

    out.close();
    cout << "Da xuat ket qua ra: " << output_csv << "\n\n";
}

int main()
{
    cout << "=== CHUONG TRINH DO DAC THUC NGHIEM SO KHOP CHUOI ===\n\n";

    fs::create_directories("data/raw");

    run_scenario_benchmark("1_dna", "data/raw/results_1_dna.csv");
    run_scenario_benchmark("2_binary", "data/raw/results_2_binary.csv");
    run_scenario_benchmark("3_english", "data/raw/results_3_english.csv");
    run_scenario_benchmark("4_best", "data/raw/results_4_best.csv");
    run_scenario_benchmark("5_worst", "data/raw/results_5_worst.csv");

    cout << "=== HOAN TAT TOAN BO QUA TRINH DO DAC! ===\n";
    return 0;
}
