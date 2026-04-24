#!/bin/bash

# Test: Multi-block và padding

echo "=== Multi-block Padding Test ==="

KEY="133457799BBCDFF1"
PASSED=0
FAILED=0

# Test 1: Dữ liệu đúng 1 block (8 byte)
PLAINTEXT1="0123456789ABCDEF"
echo "Test 1: Single block (16 hex chars)"
RESULT1=$(echo -n "$PLAINTEXT1" | ./des -e -hex <<< "$KEY" 2>/dev/null | ./des -d -hex <<< "$KEY" 2>/dev/null | grep "Decrypted text (hex):" | awk '{print $4}')
if [ "$RESULT1" == "$PLAINTEXT1" ]; then
    echo "  PASS: Single block"
    ((PASSED++))
else
    echo "  FAIL: Single block"
    ((FAILED++))
fi

# Test 2: Dữ liệu 1.5 block (24 hex chars = 12 byte)
PLAINTEXT2="0123456789ABCDEF0123"
echo "Test 2: Multi-block (24 hex chars)"
RESULT2=$(echo -n "$PLAINTEXT2" | ./des -e -hex <<< "$KEY" 2>/dev/null | ./des -d -hex <<< "$KEY" 2>/dev/null | grep "Decrypted text (hex):" | awk '{print $4}')
if [ "$RESULT2" == "$PLAINTEXT2" ]; then
    echo "  PASS: Multi-block with padding"
    ((PASSED++))
else
    echo "  FAIL: Multi-block with padding"
    ((FAILED++))
fi

# Test 3: Dữ liệu 2 block (16 byte)
PLAINTEXT3="0123456789ABCDEF0123456789ABCDEF"
echo "Test 3: Exactly 2 blocks (32 hex chars)"
RESULT3=$(echo -n "$PLAINTEXT3" | ./des -e -hex <<< "$KEY" 2>/dev/null | ./des -d -hex <<< "$KEY" 2>/dev/null | grep "Decrypted text (hex):" | awk '{print $4}')
if [ "$RESULT3" == "$PLAINTEXT3" ]; then
    echo "  PASS: Exactly 2 blocks"
    ((PASSED++))
else
    echo "  FAIL: Exactly 2 blocks"
    ((FAILED++))
fi

# Test 4: Dữ liệu rỗng
PLAINTEXT4=""
echo "Test 4: Empty input"
RESULT4=$(echo -n "$PLAINTEXT4" | ./des -e -hex <<< "$KEY" 2>/dev/null | ./des -d -hex <<< "$KEY" 2>/dev/null | grep "Decrypted text (hex):" | awk '{print $4}')
if [ -z "$RESULT4" ]; then
    echo "  PASS: Empty input"
    ((PASSED++))
else
    echo "  FAIL: Empty input"
    ((FAILED++))
fi

echo "=== Results: $PASSED passed, $FAILED failed ==="

if [ $FAILED -eq 0 ]; then
    exit 0
else
    exit 1
fi
