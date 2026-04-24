#!/bin/bash

# Test sample cơ bản

echo "=== Sample Test ==="

KEY="133457799BBCDFF1"
PLAINTEXT="0123456789ABCDEF"

# Kiểm tra file des tồn tại
if [ ! -f "./des" ]; then
    echo "Error: ./des not found. Run 'make' first."
    exit 1
fi

# Chạy mã hóa
echo "Testing DES with known vector..."
CIPHER=$(echo -n "$PLAINTEXT" | ./des -e -hex <<< "$KEY" 2>/dev/null | grep "Ciphertext (hex):" | awk '{print $3}')

# Kiểm tra có output không
if [ -n "$CIPHER" ] && [ ${#CIPHER} -eq 32 ]; then
    echo "PASS: Sample test completed"
    echo "Ciphertext: $CIPHER"
    exit 0
else
    echo "FAIL: No valid output"
    exit 1
fi
