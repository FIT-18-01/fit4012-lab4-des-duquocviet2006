[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/BJH8GGf3)
# FIT4012 - Lab 4: DES / TripleDES Implementation

Repo này chứa mã nguồn cho bài Lab 4 của FIT4012, bao gồm DES và TripleDES theo contract nhập/xuất từ stdin.

## 1. Cấu trúc repo

```text
.
├── .github/
│   ├── grading/
│   ├── scripts/
│   └── workflows/
├── logs/
│   ├── .gitkeep
│   └── 01-sample-output.txt
├── scripts/
│   └── run_sample.sh
├── tests/
│   ├── test_des_sample.sh
│   ├── test_encrypt_decrypt_roundtrip.sh
│   ├── test_multiblock_padding.sh
│   ├── test_tamper_negative.sh
│   └── test_wrong_key_negative.sh
├── .gitignore
├── CMakeLists.txt
├── Makefile
├── README.md
├── des.cpp
└── report-1page.md
```

## 2. Cách chạy chương trình (How to run)

### Biên dịch

```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
```

### Chạy chương trình

```bash
./des
```

### Ví dụ chạy mode DES encrypt

```bash
printf "1\n00010010001101000101011001111000100110101011110011011110111100011010101010101010\n0001001100110100010101110111100110011011101111001101111111110001\n" | ./des
```

## 3. Input / Đầu vào

Chương trình đọc từ stdin theo mode sau:
- `1` = DES encrypt
- `2` = DES decrypt
- `3` = TripleDES encrypt
- `4` = TripleDES decrypt

Với mode 1 và 2, chương trình đọc lần lượt:
1. mode
2. plaintext hoặc ciphertext nhị phân
3. DES key 64-bit

Với mode 3 và 4, chương trình đọc lần lượt:
1. mode
2. plaintext hoặc ciphertext 64-bit
3. key `K1` 64-bit
4. key `K2` 64-bit
5. key `K3` 64-bit

## 4. Output / Đầu ra

Chương trình in ra kết quả cuối cùng dưới dạng chuỗi nhị phân:
- DES encrypt (mode 1): `Ciphertext: <binary>`
- DES decrypt (mode 2): `Plaintext: <binary>`
- TripleDES encrypt (mode 3): `TripleDES Ciphertext: <binary>`
- TripleDES decrypt (mode 4): `TripleDES Plaintext: <binary>`

CI sẽ trích xuất giá trị nhị phân cuối cùng từ output để so sánh với testcase.

## 5. Padding đang dùng

Chương trình sử dụng **zero padding** cho DES encrypt (mode 1):
- Nếu plaintext không chia hết cho 64 bit, phần còn thiếu sẽ được điền `0`.
- Dữ liệu được xử lý theo block 64 bit tuần tự.
- Zero padding phù hợp cho bài học DES nhập môn nhưng không phải cơ chế an toàn sản xuất, bởi vì plaintext kết thúc bằng nhiều `0` sẽ gây nhầm lẫn khi giải mã.

## 6. Tests bắt buộc

Repo này đã hoàn thành 5 test:
- `tests/test_des_sample.sh`
- `tests/test_encrypt_decrypt_roundtrip.sh`
- `tests/test_multiblock_padding.sh`
- `tests/test_tamper_negative.sh`
- `tests/test_wrong_key_negative.sh`

Các test kiểm tra DES cơ bản, round-trip encrypt/decrypt, multi-block padding, trường hợp tamper và sai key.

## 7. Logs / Minh chứng

`logs/01-sample-output.txt` chứa minh chứng đầu ra của chương trình khi chạy sample DES và TripleDES.

## 8. Ethics & Safe use

- Chỉ chạy và kiểm thử trên dữ liệu học tập, dữ liệu giả lập hoặc các trường hợp mẫu.
- Không dùng repo này để tấn công hệ thống thật.
- Không trình bày đây là một giải pháp bảo mật sẵn sàng triển khai.
- Nếu tham khảo code, tài liệu hoặc AI, phải nêu rõ nguồn.
- Tôn trọng nguyên tắc trung thực học thuật và chỉ nộp kết quả do chính mình thực hiện.

## 9. Checklist nộp bài

- `des.cpp` đã hoàn chỉnh theo contract stdin/out.
- `README.md` đã mô tả rõ cách chạy, input, output, padding và ethics.
- `report-1page.md` đã hoàn thành.
- `tests/` có ít nhất 5 test.
- Có negative test cho `tamper` và `wrong key`.
- `logs/` có ít nhất 1 file minh chứng thật.
- Không còn placeholder `TODO_STUDENT`.
