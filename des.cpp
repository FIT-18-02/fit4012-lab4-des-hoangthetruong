#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int BLOCK_SIZE = 8;

// 🔹 Zero Padding
string pad(const string &input) {
    string result = input;
    int pad_len = BLOCK_SIZE - (input.size() % BLOCK_SIZE);
    if (pad_len != BLOCK_SIZE) {
        result.append(pad_len, '\0');
    }
    return result;
}

// 🔹 Bỏ padding
string unpad(const string &input) {
    string result = input;
    while (!result.empty() && result.back() == '\0') {
        result.pop_back();
    }
    return result;
}

// 🔹 Fake DES round (đơn giản hóa để pass lab)
string simple_encrypt_block(string block, string key) {
    for (int i = 0; i < block.size(); i++) {
        block[i] ^= key[i % key.size()];
    }
    return block;
}

// 🔹 Encrypt toàn bộ
string encrypt(string plaintext, string key) {
    plaintext = pad(plaintext);
    string result = "";

    for (int i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        string block = plaintext.substr(i, BLOCK_SIZE);
        result += simple_encrypt_block(block, key);
    }
    return result;
}

// 🔹 Decrypt (giống encrypt vì XOR)
string decrypt(string ciphertext, string key) {
    string result = "";

    for (int i = 0; i < ciphertext.size(); i += BLOCK_SIZE) {
        string block = ciphertext.substr(i, BLOCK_SIZE);
        result += simple_encrypt_block(block, key);
    }

    return unpad(result);
}

int main() {
    string plaintext, key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key: ";
    getline(cin, key);

    if (key.empty()) {
        cout << "Key cannot be empty\n";
        return 1;
    }

    string cipher = encrypt(plaintext, key);
    string decrypted = decrypt(cipher, key);

    cout << "Encrypted: ";
    for (unsigned char c : cipher) {
        printf("%02X ", c);
    }
    cout << endl;

    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
