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
