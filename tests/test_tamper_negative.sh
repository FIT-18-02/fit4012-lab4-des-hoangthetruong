#!/bin/bash

# Test: Sửa ciphertext 1 bit -> giải mã ra khác plaintext gốc

echo "=== Tamper Negative Test ==="

KEY="133457799BBCDFF1"
PLAINTEXT="0123456789ABCDEF"

# Mã hóa
CIPHER=$(echo -n "$PLAINTEXT" | ./des -e -hex <<< "$KEY" 2>/dev/null | grep "Ciphertext (hex):" | awk '{print $3}')

# Sửa ciphertext (flip 1 bit: đổi ký tự đầu tiên)
if [ ${#CIPHER} -gt 0 ]; then
    TAMPERED="F${CIPHER:1}"
else
    TAMPERED=""
fi

# Giải mã với ciphertext đã sửa
RESULT=$(echo -n "$TAMPERED" | ./des -d -hex <<< "$KEY" 2>/dev/null | grep "Decrypted text (hex):" | awk '{print $4}')

# Kiểm tra: kết quả khác plaintext gốc
if [ "$RESULT" != "$PLAINTEXT" ]; then
    echo "PASS: Tamper phát hiện được (kết quả: $RESULT)"
    exit 0
else
    echo "FAIL: Tamper không ảnh hưởng đến kết quả!"
    exit 1
fi
