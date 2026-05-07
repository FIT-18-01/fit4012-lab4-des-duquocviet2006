#!/usr/bin/env bash
# Test sample DES encryption via stdin contract.
set -euo pipefail
source .github/grading/common.sh

PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

OUTPUT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY" | ./des 2>&1 || true)
ACTUAL=$(extract_last_binary "$OUTPUT")

if [[ -z "$ACTUAL" ]]; then
  fail "No valid binary output from mode 1 DES encrypt"
fi

if [[ ${#ACTUAL} -ne 64 ]]; then
  fail "Expected 64-bit output, got ${#ACTUAL} bits"
fi

pass "Sample DES encryption produced valid 64-bit output."
