#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool kiemTraTonTaiBMH(const string& vanBan, const string& mau) {
        int n = vanBan.size();
        int m = mau.size();
        if (m > n) return false;

        vector<int> bangNhay(256, m);
        for (int i = 0; i < m - 1; ++i) {
            bangNhay[static_cast<unsigned char>(mau[i])] = m - 1 - i;
        }

        int viTri = 0;
        while (viTri <= n - m) {
            int j = m - 1;
            while (j >= 0 && mau[j] == vanBan[viTri + j]) {
                j--;
            }
            if (j < 0) return true;
            
            viTri += bangNhay[static_cast<unsigned char>(vanBan[viTri + m - 1])];
        }
        return false;
    }

public:
    bool repeatedSubstringPattern(string s) {
        if (s.size() <= 1) return false;
        
        string chuoiNhanDoi = s + s;
        string vungTimKiem = chuoiNhanDoi.substr(1, chuoiNhanDoi.size() - 2);
        
        return kiemTraTonTaiBMH(vungTimKiem, s);
    }
};
