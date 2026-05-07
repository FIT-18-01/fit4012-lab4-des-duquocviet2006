#!/usr/bin/env bash
# Test round-trip DES encrypt then decrypt.
set -euo pipefail

PLAINTEXT="1100110011001100110011001100110011001100110011001100110011001100"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

CIPHERTEXT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ./des | grep -oE '[01]{64,}' | tail -n 1)
DECRYPTED=$(printf "2\n%s\n%s\n" "$CIPHERTEXT" "$KEY" | ./des | grep -oE '[01]{64,}' | tail -n 1)

if [[ "$DECRYPTED" != "$PLAINTEXT" ]]; then
  echo "Round-trip failed"
  echo "Plaintext:  $PLAINTEXT"
  echo "Ciphertext: $CIPHERTEXT"
  echo "Decrypted:  $DECRYPTED"
  exit 1
fi

echo "PASS: DES encrypt/decrypt round-trip succeeded."
