// FFO sử dụng giải thuật Boyer-Moore-Horspool
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<int> taoBangDichChuyen(const string& mau) {
        int doDaiMau = mau.size();
        vector<int> bangNhay(256, doDaiMau);
        
        for (int i = 0; i < doDaiMau - 1; ++i) {
            unsigned char kyTu = static_cast<unsigned char>(mau[i]);
            bangNhay[kyTu] = doDaiMau - 1 - i;
        }
        return bangNhay;
    }

public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        
        if (m == 0) return 0;
        if (m > n) return -1;

        vector<int> bangNhay = taoBangDichChuyen(needle);
        int viTri = 0;

        while (viTri <= n - m) {
            int j = m - 1;
            while (j >= 0 && needle[j] == haystack[viTri + j]) {
                j--;
            }
            
            if (j < 0) {
                return viTri;
            }
            
            unsigned char kyTuCuoiCuaSo = static_cast<unsigned char>(haystack[viTri + m - 1]);
            viTri += bangNhay[kyTuCuoiCuaSo];
        }

        return -1;
    }
};
