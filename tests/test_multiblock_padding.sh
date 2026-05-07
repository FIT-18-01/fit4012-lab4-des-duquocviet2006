#!/usr/bin/env bash
# Test multi-block encryption v?i zero padding
set -euo pipefail

echo "Testing multi-block encryption with zero padding..."

# Test v?i plaintext > 64 bits (74 bits)
LONG_PLAINTEXT="00010010001101000101011001111000100110101011110011011110111100011010101010101010"
KEY="0001001100110100010101110111100110011011101111001101111111110001"
EXPECTED="01111110101111110100010010010011001000111111101011111010111110000100000010010001101001000010011111010110110001100000111000110100"

if [[ ! -x ../des ]]; then
  cd ..
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
  cd tests
fi

OUTPUT=$(printf "1\n%s\n%s\n" "$LONG_PLAINTEXT" "$KEY" | ../des 2>&1)
ACTUAL=$(echo "$OUTPUT" | grep -oE "[01]{128,}" | tail -n 1)

if [[ "$ACTUAL" != "$EXPECTED" ]]; then
  echo "FAIL: Multi-block test failed"
  echo "Expected: $EXPECTED"
  echo "Actual:   $ACTUAL"
  exit 1
fi

echo "PASS: Multi-block encryption with zero padding works correctly"
echo "Input length:  bits"
echo "Output length:  bits"