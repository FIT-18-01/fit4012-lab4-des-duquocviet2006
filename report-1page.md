# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

Xây dựng chương trình DES và TripleDES theo contract nhập/xuất từ stdin. Mục tiêu cụ thể là:
- Thực hiện DES encrypt/decrypt với dữ liệu dạng nhị phân.
- Hỗ trợ mã hóa đa block với zero padding.
- Thực hiện TripleDES theo chuỗi E(K3, D(K2, E(K1, P))) và giải mã tương ứng.
- Đảm bảo CI có thể kiểm tra tự động Q2 và Q4.

## Cách làm / Method

- Hoàn thiện `des.cpp` để chương trình đọc mode từ stdin và xử lý lần lượt các dòng input.
- Triển khai `KeyGenerator` sinh 16 round key theo PC-1/PC-2 và dịch trái theo chuẩn DES.
- Xây dựng lớp `DES` để thực hiện 16 round Feistel, mở rộng E-bit, S-box và phép hoán vị P.
- Với mode 1, chia plaintext nhị phân thành block 64 bit và zero pad nếu cần.
- Với mode 2, giải mã ciphertext bằng round keys đảo ngược.
- Với mode 3/4, thực hiện TripleDES theo chuẩn EDE.
- Hoàn thiện test script trong `tests/` và bổ sung log chạy mẫu.

## Kết quả / Result

- Chương trình đã chạy đúng contract stdin mode 1/2/3/4.
- Q2 pass trên vector mẫu: multi-block DES encrypt với zero padding.
- Q4 pass trên vector TripleDES: encrypt và decrypt đúng theo EDE.
- `tests/` bao gồm 5 script, trong đó có test tamper và wrong key.
- `logs/01-sample-output.txt` chứa kết quả chạy mẫu làm minh chứng.

## Kết luận / Conclusion

- Đã nắm được cách tổ chức DES: hoán vị IP/IP-1, E-bit, S-box, P, round key.
- Hiểu rõ giới hạn của zero padding: không đủ để nhận biết độ dài ban đầu khi decrypt.
- TripleDES được triển khai đúng theo E(K3, D(K2, E(K1, P))) và giải mã ngược lại.
- Có thể mở rộng tiếp bằng các cơ chế padding an toàn hơn hoặc thêm giao diện file input/output.
