#!/usr/bin/env bash
# Test DES sample t? code g?c v?i input/output chu?n
set -euo pipefail

echo "Testing DES sample encryption..."

# Test vectors t? code g?c
PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
KEY="0001001100110100010101110111100110011011101111001101111111110001"
EXPECTED="0111111010111111010001001001001100100011111110101111101011111000"

if [[ ! -x ../des ]]; then
  cd ..
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
  cd tests
fi

OUTPUT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ../des 2>&1)
ACTUAL=$(echo "$OUTPUT" | grep -oE "[01]{64,}" | tail -n 1)

if [[ "$ACTUAL" != "$EXPECTED" ]]; then
  echo "FAIL: DES sample test failed"
  echo "Expected: $EXPECTED"
  echo "Actual: $ACTUAL"
  echo "Full output:"
  echo "$OUTPUT"
  exit 1
fi

echo "PASS: DES sample encryption works correctly"
echo "Input: "
echo "Key: "
echo "Output: "