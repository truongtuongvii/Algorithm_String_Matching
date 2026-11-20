#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::string generate_random_string(int length, const std::string& alphabet, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, static_cast<int>(alphabet.size()) - 1);
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(alphabet[dist(rng)]);
    }
    return result;
}

void write_test_file(const std::string& filepath, const std::string& T, const std::string& P) {
    std::ofstream out(filepath);
    if (!out.is_open()) {
        std::cerr << "[ERROR] Khong the ghi file: " << filepath << "\n";
        return;
    }
    out << T << "\n" << P << "\n";
}

int main() {
    const std::string output_dir = "data";
    fs::create_directories(output_dir);

    std::mt19937 rng(42);
    const std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000};
    constexpr int pattern_length = 100;

    const std::string ALPHA_TEXT = "abcdefghijklmnopqrstuvwxyz ";
    const std::string ALPHA_DNA  = "ACGT";
    const std::string ALPHA_BIN  = "01";

    for (int n : sizes) {
        const std::string suffix = "_" + std::to_string(n) + ".txt";

        // 1. Van ban tieng Anh ngau nhien
        std::string t_text = generate_random_string(n, ALPHA_TEXT, rng);
        write_test_file(output_dir + "/text_random" + suffix, t_text, t_text.substr(n / 2, pattern_length));

        // 2. Chuoi DNA (4 ky tu A, C, G, T)
        std::string t_dna = generate_random_string(n, ALPHA_DNA, rng);
        write_test_file(output_dir + "/dna_random" + suffix, t_dna, t_dna.substr(n / 2, pattern_length));

        // 3. Chuoi nhi phan (0, 1)
        std::string t_bin = generate_random_string(n, ALPHA_BIN, rng);
        write_test_file(output_dir + "/bin_random" + suffix, t_bin, t_bin.substr(n / 2, pattern_length));

        // 4. Truong hop xau nhat cho Vet can (T toan 'a', P = 'a...ab')
        std::string t_worst(n, 'a');
        std::string p_worst(pattern_length - 1, 'a');
        p_worst.push_back('b');
        write_test_file(output_dir + "/worst_case" + suffix, t_worst, p_worst);
    }

    std::cout << "[OK] Da sinh thanh cong 32 bo du lieu trong thu muc '" << output_dir << "/'.\n";
    return 0;
}
