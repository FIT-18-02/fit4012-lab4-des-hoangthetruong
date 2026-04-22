#include <iostream>
#include <iomanip>
#include <string>
#include <openssl/des.h>

// Zero padding cho block 8 bytes
std::string padZero(const std::string &data) {
    size_t padLen = 8 - (data.size() % 8);
    if (padLen == 8) return data;
    return data + std::string(padLen, '\0');
}

std::string unpadZero(const std::string &data) {
    size_t end = data.find_last_not_of('\0');
    if (end == std::string::npos) return "";
    return data.substr(0, end + 1);
}

// DES Encrypt
std::string desEncrypt(const std::string &keyStr, const std::string &plaintext) {
    DES_cblock key;
    DES_key_schedule schedule;
    memcpy(key, keyStr.data(), 8);
    DES_set_key_unchecked(&key, &schedule);

    std::string padded = padZero(plaintext);
    std::string ciphertext(padded.size(), '\0');

    for (size_t i = 0; i < padded.size(); i += 8) {
        DES_ecb_encrypt((DES_cblock*)(padded.data() + i),
                        (DES_cblock*)(ciphertext.data() + i),
                        &schedule, DES_ENCRYPT);
    }
    return ciphertext;
}

// DES Decrypt
std::string desDecrypt(const std::string &keyStr, const std::string &ciphertext) {
    DES_cblock key;
    DES_key_schedule schedule;
    memcpy(key, keyStr.data(), 8);
    DES_set_key_unchecked(&key, &schedule);

    std::string plaintext(ciphertext.size(), '\0');
    for (size_t i = 0; i < ciphertext.size(); i += 8) {
        DES_ecb_encrypt((DES_cblock*)(ciphertext.data() + i),
                        (DES_cblock*)(plaintext.data() + i),
                        &schedule, DES_DECRYPT);
    }
    return unpadZero(plaintext);
}

// TripleDES Encrypt (EDE mode)
std::string tripleDesEncrypt(const std::string &keyStr, const std::string &plaintext) {
    DES_cblock key1, key2, key3;
    DES_key_schedule ks1, ks2, ks3;
    memcpy(key1, keyStr.data(), 8);
    memcpy(key2, keyStr.data() + 8, 8);
    memcpy(key3, keyStr.data() + 16, 8);
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    std::string padded = padZero(plaintext);
    std::string ciphertext(padded.size(), '\0');

    for (size_t i = 0; i < padded.size(); i += 8) {
        DES_cblock block;
        memcpy(block, padded.data() + i, 8);
        DES_ecb_encrypt(&block, &block, &ks1, DES_ENCRYPT);
        DES_ecb_encrypt(&block, &block, &ks2, DES_DECRYPT);
        DES_ecb_encrypt(&block, &block, &ks3, DES_ENCRYPT);
        memcpy(ciphertext.data() + i, block, 8);
    }
    return ciphertext;
}

// TripleDES Decrypt
std::string tripleDesDecrypt(const std::string &keyStr, const std::string &ciphertext) {
    DES_cblock key1, key2, key3;
    DES_key_schedule ks1, ks2, ks3;
    memcpy(key1, keyStr.data(), 8);
    memcpy(key2, keyStr.data() + 8, 8);
    memcpy(key3, keyStr.data() + 16, 8);
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    std::string plaintext(ciphertext.size(), '\0');

    for (size_t i = 0; i < ciphertext.size(); i += 8) {
        DES_cblock block;
        memcpy(block, ciphertext.data() + i, 8);
        DES_ecb_encrypt(&block, &block, &ks3, DES_DECRYPT);
        DES_ecb_encrypt(&block, &block, &ks2, DES_ENCRYPT);
        DES_ecb_encrypt(&block, &block, &ks1, DES_DECRYPT);
        memcpy(plaintext.data() + i, block, 8);
    }
    return unpadZero(plaintext);
}

int main() {
    std::string key = "12345678"; // 8 bytes cho DES
    std::string tripleKey = "123456781234567812345678"; // 24 bytes cho TripleDES
    std::string plaintext = "Hello DES World!";

    std::cout << "Plaintext: " << plaintext << "\n";

    // DES
    std::string ciphertext = desEncrypt(key, plaintext);
    std::cout << "DES Ciphertext (hex): ";
    for (unsigned char c : ciphertext)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    std::cout << "\n";
    std::string recovered = desDecrypt(key, ciphertext);
    std::cout << "DES Decrypted: " << recovered << "\n";

    // TripleDES
    std::string ciphertext2 = tripleDesEncrypt(tripleKey, plaintext);
    std::cout << "TripleDES Ciphertext (hex): ";
    for (unsigned char c : ciphertext2)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    std::cout << "\n";
    std::string recovered2 = tripleDesDecrypt(tripleKey, ciphertext2);
    std::cout << "TripleDES Decrypted: " << recovered2 << "\n";

    return 0;
}
