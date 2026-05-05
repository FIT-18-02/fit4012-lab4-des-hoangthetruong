## How to run

Compile:
g++ -std=c++17 des.cpp -o des

Run:
./des

Input format:

Mode 1: DES encrypt
1
<plaintext (binary)>
<key (64-bit binary)>

Mode 2: DES decrypt
2
<ciphertext (binary)>
<key (64-bit binary)>

Mode 3: TripleDES encrypt
3
<plaintext>
<K1>
<K2>
<K3>

Mode 4: TripleDES decrypt
4
<ciphertext>
<K1>
<K2>
<K3>
## Output

Chương trình in ra kết quả cuối cùng dưới dạng chuỗi nhị phân.

- Mã hóa: in ciphertext dạng binary
- Giải mã: in plaintext dạng binary
- Độ dài output là bội số của 64 bit

---

The program outputs the final result as a binary string.

- For encryption: ciphertext in binary format.
- For decryption: plaintext in binary format.
- Output length is a multiple of 64 bits.
