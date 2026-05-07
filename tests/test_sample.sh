#!/usr/bin/env bash
set -euo pipefail

EXPECTED="0111111010111111010001001001001100100011111110101111101011111000"

g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des_test
OUTPUT=$(printf "1\n0001001000110100010101100111100010011010101111001101111011110001\n0001001100110100010101110111100110011011101111001101111111110001\n" | ./des_test)
LAST_LINE=$(printf "%s\n" "$OUTPUT" | tail -n 1)

if [[ "$LAST_LINE" != "$EXPECTED" ]]; then
  echo "[FAIL] Unexpected ciphertext output"
  echo "Expected: $EXPECTED"
  echo "Actual:   $LAST_LINE"
  exit 1
fi

echo "[PASS] Sample DES program produced the expected ciphertext."
rm -f des_test