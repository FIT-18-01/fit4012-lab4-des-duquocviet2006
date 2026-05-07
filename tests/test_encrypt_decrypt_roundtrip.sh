#!/usr/bin/env bash
# Test DES round-trip: encrypt -> decrypt should restore original plaintext
set -euo pipefail

echo "Testing DES round-trip encryption/decryption..."

# Test vector
PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

if [[ ! -x ../des ]]; then
  cd ..
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
  cd tests
fi

# Encrypt
CIPHER_OUTPUT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ../des 2>&1)
CIPHER=$(echo "$CIPHER_OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

echo "Encrypted: "

# Decrypt
PLAIN_OUTPUT=$(printf "2\n%s\n%s\n" "$CIPHER" "$KEY" | ../des 2>&1)
DECRYPTED=$(echo "$PLAIN_OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

echo "Decrypted: "

if [[ "$DECRYPTED" != "$PLAINTEXT" ]]; then
  echo "FAIL: Round-trip test failed"
  echo "Original:  $PLAINTEXT"
  echo "Decrypted: $DECRYPTED"
  exit 1
fi

echo "PASS: DES round-trip works correctly"