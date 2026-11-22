# BÁO CÁO LÝ THUYẾT — ĐỀ 14: SO KHỚP CHUỖI (THÀNH VIÊN 2)

## 1. Giải thuật Boyer–Moore–Horspool

### 1.1. Ý tưởng
Boyer–Moore–Horspool là phiên bản cải tiến và rút gọn của thuật toán Boyer–Moore, chỉ sử dụng **quy tắc ký tự xấu (Bad Character Heuristic)**. Thuật toán thực hiện đối chiếu các ký tự của mẫu $P$ với cửa sổ văn bản $T$ theo chiều từ **phải sang trái** (từ $m - 1$ về $0$). Khi xảy ra sai khác (hoặc đã khớp hoàn toàn), thuật toán luôn dựa vào ký tự tại vị trí cuối cùng của cửa sổ trên văn bản là $T[s + m - 1]$ để tra bảng dịch chuyển và nhảy mẫu sang phải một khoảng an toàn.

---

### 1.2. Mã giả
```text
BUILD-SHIFT-TABLE(P, m):
    Khởi tạo mảng shift[0..255] với tất cả giá trị = m
    for i = 0 to m - 2:
        shift[P[i]] = m - 1 - i
    return shift

BOYER-MOORE-HORSPOOL(T, P):
    n = length(T)
    m = length(P)
    if m == 0 or m > n:
        return []
    shift = BUILD-SHIFT-TABLE(P, m)
    result = []
    s = 0
    while s <= n - m:
        j = m - 1
        while j >= 0 and P[j] == T[s + j]:
            j = j - 1
        if j < 0:
            result.append(s)
        s = s + shift[T[s + m - 1]]
    return result
