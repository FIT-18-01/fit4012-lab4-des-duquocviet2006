#!/usr/bin/env bash
# Test negative case: tamper v?i ciphertext (flip 1 bit)
set -euo pipefail

echo "Testing tamper detection - flipping 1 bit in ciphertext..."

PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

if [[ ! -x ../des ]]; then
  cd ..
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
  cd tests
fi

# Encrypt d? c� ciphertext h?p l?
CIPHER_OUTPUT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ../des 2>&1)
CIPHER=$(echo "$CIPHER_OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

echo "Original ciphertext: $CIPHER"

# Flip bit đầu tiên (0->1 hoặc 1->0)
if [[ "${CIPHER:0:1}" == "0" ]]; then
  TAMPERED="1${CIPHER:1}"
else
  TAMPERED="0${CIPHER:1}"
fi

echo "Tampered ciphertext: $TAMPERED"

# Decrypt ciphertext d� b? tamper
TAMPER_OUTPUT=$(printf "2\n%s\n%s\n" "$TAMPERED" "$KEY" | ../des 2>&1)
TAMPER_DECRYPTED=$(echo "$TAMPER_OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

echo "Decrypted tampered: $TAMPER_DECRYPTED"

# Kiểm tra xem có khác với plaintext gốc không
if [[ "$TAMPER_DECRYPTED" == "$PLAINTEXT" ]]; then
  echo "FAIL: Tamper test failed - decrypted result should be different"
  exit 1
fi

echo "PASS: Tamper detection works - decrypted result differs from original"
echo "Original plaintext:  $PLAINTEXT"
echo "Tampered decrypt:    $TAMPER_DECRYPTED"