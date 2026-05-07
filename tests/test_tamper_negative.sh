#!/usr/bin/env bash
# Test negative case: tamper ciphertext and verify decrypted result differs.
set -euo pipefail

PLAINTEXT="00010010001101000101011001111000100110101011110011011110111100011010101010101010"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

CIPHERTEXT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ./des | grep -oE '[01]{64,}' | tail -n 1)
LAST_BIT=${CIPHERTEXT: -1}
if [[ "$LAST_BIT" == "0" ]]; then
  FLIPPED=1
else
  FLIPPED=0
fi
TAMPERED="${CIPHERTEXT:0:${#CIPHERTEXT}-1}$FLIPPED"
DECRYPTED=$(printf "2\n%s\n%s\n" "$TAMPERED" "$KEY" | ./des | grep -oE '[01]{64,}' | tail -n 1)

if [[ "$DECRYPTED" == "$PLAINTEXT" ]]; then
  echo "Tamper negative test failed: tampered ciphertext decrypted to original plaintext"
  echo "Ciphertext: $CIPHERTEXT"
  echo "Tampered:    $TAMPERED"
  echo "Decrypted:   $DECRYPTED"
  exit 1
fi

echo "PASS: Tamper negative test succeeded."
