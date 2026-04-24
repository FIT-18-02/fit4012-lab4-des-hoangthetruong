#!/bin/bash

# Test: Round-trip encrypt -> decrypt phải ra đúng plaintext

echo "=== Encrypt-Decrypt Roundtrip Test ==="

KEY="133457799BBCDFF1"
TEST_CASES=(
    "0123456789ABCDEF"
    "0000000000000000"
    "FFFFFFFFFFFFFFFF"
    "AABBCCDDEEFF0011"
    "48656C6C6F576F726C64"
)

PASSED=0
FAILED=0

for PLAINTEXT in "${TEST_CASES[@]}"; do
    echo -n "Testing: $PLAINTEXT ... "
    
    # Mã hóa
    CIPHER=$(echo -n "$PLAINTEXT" | ./des -e -hex <<< "$KEY" 2>/dev/null | grep "Ciphertext (hex):" | awk '{print $3}')
    
    # Giải mã
    DECRYPTED=$(echo -n "$CIPHER" | ./des -d -hex <<< "$KEY" 2>/dev/null | grep "Decrypted text (hex):" | awk '{print $4}')
    
    if [ "$DECRYPTED" == "$PLAINTEXT" ]; then
        echo "PASS"
        ((PASSED++))
    else
        echo "FAIL (expected $PLAINTEXT, got $DECRYPTED)"
        ((FAILED++))
    fi
done

echo "=== Results: $PASSED passed, $FAILED failed ==="

if [ $FAILED -eq 0 ]; then
    exit 0
else
    exit 1
fi
