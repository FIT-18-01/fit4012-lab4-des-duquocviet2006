# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

Hoàn thiện implementation DES và TripleDES từ code base có sẵn, hỗ trợ cả encryption và decryption với multi-block input và zero padding.

## Cách làm / Method

- Bổ sung hàm `decrypt()` cho class DES bằng cách sử dụng round keys theo thứ tự đảo ngược
- Thêm hàm `pad_binary_string()` để xử lý zero padding cho multi-block
- Cập nhật hàm `main()` để nhận input từ stdin theo 4 modes: DES encrypt/decrypt, TripleDES encrypt/decrypt
- Implement TripleDES với EDE (Encrypt-Decrypt-Encrypt) và reverse EDE cho decryption
- Test với các test vectors từ file grading để đảm bảo tính chính xác

## Kết quả / Result

- ✅ DES encryption/decryption hoạt động chính xác
- ✅ Multi-block encryption với zero padding
- ✅ TripleDES EDE encryption/decryption với round-trip verification
- ✅ Input từ stdin theo contract thống nhất
- ✅ Output ciphertext/plaintext dưới dạng binary strings
- ✅ Tất cả test Q2 và Q4 pass

Ví dụ kết quả DES encrypt:
```
Input: 0001001000110100010101100111100010011010101111001101111011110001
Key: 0001001100110100010101110111100110011011101111001101111111110001
Output: 0111111010111111010001001001001100100011111110101111101011111000
```

## Kết luận / Conclusion

Đã hoàn thành implementation DES/TripleDES cơ bản với các tính năng:
- DES single-block và multi-block encryption/decryption
- TripleDES EDE với 3 keys độc lập
- Zero padding cho multi-block
- Input/output handling qua stdin

**Hạn chế hiện tại:**
- Zero padding không an toàn cho production use
- Không có error handling cho invalid input
- Không hỗ trợ CBC mode hay IV

**Hướng mở rộng:**
- Thêm PKCS#7 padding
- Implement CBC mode với IV
- Hỗ trợ file input/output
- Thêm validation cho input keys và data