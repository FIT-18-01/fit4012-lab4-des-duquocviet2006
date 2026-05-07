#!/usr/bin/env bash
# Test negative case: decrypt with wrong key should not recover original plaintext.
set -euo pipefail

PLAINTEXT="00010010001101000101011001111000100110101011110011011110111100011010101010101010"
KEY="0001001100110100010101110111100110011011101111001101111111110001"
WRONG_KEY="1111000011001100101010101111010101010110011001111000111100001111"

if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

CIPHERTEXT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ./des | grep -oE '[01]{64,}' | tail -n 1)
DECRYPTED=$(printf "2\n%s\n%s\n" "$CIPHERTEXT" "$WRONG_KEY" | ./des | grep -oE '[01]{64,}' | tail -n 1)

if [[ "$DECRYPTED" == "$PLAINTEXT" ]]; then
  echo "Wrong key negative test failed: wrong key recovered original plaintext"
  exit 1
fi

echo "PASS: Wrong key negative test succeeded."
