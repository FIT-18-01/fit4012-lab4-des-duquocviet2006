#!/usr/bin/env bash
# Test negative case: s? d?ng wrong key d? decrypt
set -euo pipefail

echo "Testing wrong key detection..."

PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
CORRECT_KEY="0001001100110100010101110111100110011011101111001101111111110001"
WRONG_KEY="1111000011001100101010101111010101010110011001111000111100001111"

if [[ ! -x ../des ]]; then
  cd ..
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
  cd tests
fi

# Encrypt v?i key d�ng
CIPHER_OUTPUT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$CORRECT_KEY" | ../des 2>&1)
CIPHER=$(echo "$CIPHER_OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

echo "Ciphertext: $CIPHER"

# Decrypt với key sai
WRONG_OUTPUT=$(printf "2\n%s\n%s\n" "$CIPHER" "$WRONG_KEY" | ../des 2>&1)
WRONG_DECRYPTED=$(echo "$WRONG_OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

echo "Decrypted with wrong key: $WRONG_DECRYPTED"

# Kiểm tra xem có khác với plaintext gốc không
if [[ "$WRONG_DECRYPTED" == "$PLAINTEXT" ]]; then
  echo "FAIL: Wrong key test failed - should not decrypt correctly"
  exit 1
fi

echo "PASS: Wrong key detection works - cannot decrypt with incorrect key"
echo "Original plaintext: $PLAINTEXT"
echo "Wrong key decrypt:  $WRONG_DECRYPTED"