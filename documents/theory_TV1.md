# BÁO CÁO LÝ THUYẾT — ĐỀ 14: SO KHỚP CHUỖI (THÀNH VIÊN 1)

## 1. Phát biểu bài toán hình thức
* **Đầu vào (Input):**
  * Văn bản $T[0..n-1]$ có độ dài $n$.
  * Chuỗi mẫu $P[0..m-1]$ có độ dài $m$.
  * Các ký tự của $T$ và $P$ thuộc cùng một bảng chữ cái hữu hạn $\Sigma$.
* **Ràng buộc:** $1 \le m \le n$.
* **Đầu ra (Output):** Tập hợp tất cả các chỉ số dịch chuyển $s \in [0, n - m]$ thỏa mãn $T[s + j] = P[j]$ với mọi $0 \le j \le m - 1$.
* **Kích thước đầu vào:** Được đo bằng cặp $(n, m)$, trong đó $n = \vert{}T\vert{}$ và $m = \vert{}P\vert{}$.

---

## 2. Giải thuật Vét cạn (Naive / Brute Force)

### 2.1. Ý tưởng
Kiểm tra tuần tự mọi vị trí dịch chuyển hợp lệ $i \in [0, n - m]$. Tại mỗi vị trí $i$, so sánh trực tiếp từng ký tự của $P$ với đoạn con $T[i..i+m-1]$ từ trái sang phải. Khi phát hiện ký tự không khớp, dừng kiểm tra tại $i$ và dịch sang vị trí $i + 1$.

### 2.2. Mã giả
```text
NAIVE-STRING-MATCHER(T, P):
  n = length(T)
  m = length(P)
  result = []
  for i = 0 to n - m:
      j = 0
      while j < m and T[i + j] == P[j]:
          j = j + 1
      if j == m:
          result.append(i)
  return result
