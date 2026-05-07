#!/usr/bin/env bash
set -euo pipefail
source .github/grading/common.sh

echo "=== Wrong Key Negative Test ==="

# Test vectors
PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"
KEY_CORRECT="0001001100110100010101110111100110011011101111001101111111110001"
KEY_WRONG="1111000011001100101010101111010101010110011001111000111100001111"

# Compile if needed
if [[ ! -x ./des ]]; then
  g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
fi

# Bước 1: Mã hóa với key đúng
ENC_OUTPUT=$(printf "1\n%s\n%s\n" "$PLAINTEXT" "$KEY_CORRECT" | ./des 2>&1)
CIPHER=$(extract_last_binary "$ENC_OUTPUT")

if [[ -z "$CIPHER" ]]; then
  fail "Không lấy được ciphertext từ mode 1 (DES Encrypt)"
fi

# Bước 2: Giải mã với key SAI
DEC_OUTPUT=$(printf "2\n%s\n%s\n" "$CIPHER" "$KEY_WRONG" | ./des 2>&1)
PLAIN_WRONG=$(extract_last_binary "$DEC_OUTPUT")

if [[ -z "$PLAIN_WRONG" ]]; then
  fail "Không đọc được output khi giải mã với key sai"
fi

# Kiểm tra: Phải KHÔNG khôi phục được plaintext gốc
if [[ "$PLAIN_WRONG" != "$PLAINTEXT" ]]; then
  pass "Negative test (wrong key) đạt: Giải mã với key sai KHÔNG khôi phục được plaintext gốc."
else
  echo "--- Output khi decrypt với key sai ---"
  echo "$DEC_OUTPUT"
  fail "Negative test thất bại: Giải mã với key sai vẫn ra plaintext đúng."
fi
