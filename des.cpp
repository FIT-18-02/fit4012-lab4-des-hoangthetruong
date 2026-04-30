#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>

// ====================== DES Tables ======================

// Initial Permutation (IP)
const int IP[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

// Final Permutation (FP = IP^{-1})
const int FP[64] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

// Expansion table (E)
const int E[48] = {
    32,1,2,3,4,5, 4,5,6,7,8,9,
    8,9,10,11,12,13, 12,13,14,15,16,17,
    16,17,18,19,20,21, 20,21,22,23,24,25,
    24,25,26,27,28,29, 28,29,30,31,32,1
};

// S-Boxes (8 boxes, mỗi box 4x16)
const uint8_t S[8][4][16] = {
    // S1
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
    // S2
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
    // S3
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
    // S4
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
    // S5
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
    // S6
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
    // S7
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
    // S8
    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
     {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
     {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
     {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

// Permutation P (32-bit)
const int P[32] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

// PC-1 (Key schedule - 56 bit)
const int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

// PC-2 (48 bit)
const int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

// Shift schedule (số bit shift cho mỗi round)
const int shift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

// ====================== Helper functions ======================

// Convert hex string to bytes
std::vector<uint8_t> hex_to_bytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

// Bytes to hex string
std::string bytes_to_hex(const uint8_t* data, size_t len) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < len; ++i) {
        ss << std::setw(2) << static_cast<int>(data[i]);
    }
    return ss.str();
}

// Bit manipulation helpers
uint64_t permute(uint64_t input, const int* table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; ++i) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}

// ====================== Key Schedule ======================
void generate_subkeys(const uint8_t* key, uint64_t subkeys[16]) {
    // Key 64-bit -> 56-bit using PC-1
    uint64_t key56 = 0;
    for (int i = 0; i < 56; ++i) {
        key56 <<= 1;
        key56 |= (key[PC1[i]/8] >> (7 - (PC1[i] % 8))) & 1;
    }

    uint32_t C = (key56 >> 28) & 0xFFFFFFF;
    uint32_t D = key56 & 0xFFFFFFF;

    for (int round = 0; round < 16; ++round) {
        // Shift
        int shifts = shift[round];
        C = ((C << shifts) | (C >> (28 - shifts))) & 0xFFFFFFF;
        D = ((D << shifts) | (D >> (28 - shifts))) & 0xFFFFFFF;

        uint64_t CD = ((uint64_t)C << 28) | D;

        // PC-2 -> 48-bit subkey
        uint64_t subkey = 0;
        for (int i = 0; i < 48; ++i) {
            subkey <<= 1;
            subkey |= (CD >> (56 - PC2[i])) & 1;
        }
        subkeys[round] = subkey;
    }
}

// ====================== Feistel function f ======================
uint32_t feistel(uint32_t R, uint64_t subkey) {
    // Expansion 32 -> 48
    uint64_t expanded = 0;
    for (int i = 0; i < 48; ++i) {
        expanded <<= 1;
        expanded |= (R >> (32 - E[i])) & 1;
    }

    // XOR with subkey
    expanded ^= subkey;

    // S-boxes
    uint32_t sbox_output = 0;
    for (int i = 0; i < 8; ++i) {
        uint8_t chunk = (expanded >> (42 - i*6)) & 0x3F;  // 6 bits
        int row = ((chunk & 0x20) >> 4) | (chunk & 0x01);     // first and last bit
        int col = (chunk >> 1) & 0x0F;                        // middle 4 bits
        uint8_t val = S[i][row][col];
        sbox_output = (sbox_output << 4) | val;
    }

    // Permutation P
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result <<= 1;
        result |= (sbox_output >> (32 - P[i])) & 1;
    }
    return result;
}

// ====================== DES Encrypt / Decrypt single block ======================
void des_encrypt_block(const uint8_t* input, uint8_t* output, const uint64_t subkeys[16]) {
    uint64_t block = 0;
    for (int i = 0; i < 8; ++i) {
        block = (block << 8) | input[i];
    }

    // Initial Permutation
    uint64_t perm = permute(block, IP, 64);

    uint32_t L = (perm >> 32) & 0xFFFFFFFF;
    uint32_t R = perm & 0xFFFFFFFF;

    for (int round = 0; round < 16; ++round) {
        uint32_t temp = R;
        R = L ^ feistel(R, subkeys[round]);
        L = temp;
    }

    // Swap L and R
    uint64_t pre_final = ((uint64_t)R << 32) | L;

    // Final Permutation
    uint64_t cipher = permute(pre_final, FP, 64);

    for (int i = 0; i < 8; ++i) {
        output[7 - i] = (cipher >> (i * 8)) & 0xFF;   // big-endian
    }
}

void des_decrypt_block(const uint8_t* input, uint8_t* output, const uint64_t subkeys[16]) {
    uint64_t subkeys_rev[16];
    for (int i = 0; i < 16; ++i) {
        subkeys_rev[i] = subkeys[15 - i];
    }
    des_encrypt_block(input, output, subkeys_rev);   // Decrypt = Encrypt with reversed keys
}

// ====================== Multi-block + Zero Padding ======================
std::vector<uint8_t> des_encrypt(const std::vector<uint8_t>& plaintext, const uint8_t* key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);

    std::vector<uint8_t> ciphertext;
    size_t len = plaintext.size();
    size_t padded_len = ((len + 7) / 8) * 8;

    for (size_t i = 0; i < padded_len; i += 8) {
        uint8_t block_in[8] = {0};
        for (size_t j = 0; j < 8 && (i + j) < len; ++j) {
            block_in[j] = plaintext[i + j];
        }
        // zero padding tự động vì khởi tạo = 0

        uint8_t block_out[8];
        des_encrypt_block(block_in, block_out, subkeys);
        for (int k = 0; k < 8; ++k) {
            ciphertext.push_back(block_out[k]);
        }
    }
    return ciphertext;
}

// ====================== Triple DES (EDE - 3 keys, 24 bytes) ======================
void triple_des_encrypt(const uint8_t* in, uint8_t* out, const uint8_t* key24) {
    uint8_t temp1[8], temp2[8];

    // E K1
    uint64_t sk1[16]; generate_subkeys(key24, sk1);
    des_encrypt_block(in, temp1, sk1);

    // D K2
    uint64_t sk2[16]; generate_subkeys(key24 + 8, sk2);
    des_decrypt_block(temp1, temp2, sk2);

    // E K3
    uint64_t sk3[16]; generate_subkeys(key24 + 16, sk3);
    des_encrypt_block(temp2, out, sk3);
}

// ====================== Main (nhập từ bàn phím) ======================
int main() {
    std::string key_hex, pt_hex;

    std::cout << "Enter KEY (16 hex chars for DES, 48 hex chars for 3DES): ";
    std::cin >> key_hex;

    std::cout << "Enter PLAINTEXT (hex): ";
    std::cin >> pt_hex;

    auto key_bytes = hex_to_bytes(key_hex);
    auto pt_bytes  = hex_to_bytes(pt_hex);

    if (key_bytes.size() == 8) {                    // Single DES
        auto ct = des_encrypt(pt_bytes, key_bytes.data());
        std::cout << "Ciphertext (hex): " << bytes_to_hex(ct.data(), ct.size()) << std::endl;
    } 
    else if (key_bytes.size() == 24) {              // Triple DES
        std::vector<uint8_t> ct;
        size_t len = pt_bytes.size();
        for (size_t i = 0; i < len; i += 8) {
            uint8_t block_in[8] = {0};
            for (int j = 0; j < 8 && i+j < len; ++j) block_in[j] = pt_bytes[i+j];

            uint8_t block_out[8];
            triple_des_encrypt(block_in, block_out, key_bytes.data());
            for (int k = 0; k < 8; ++k) ct.push_back(block_out[k]);
        }
        std::cout << "TripleDES Ciphertext (hex): " << bytes_to_hex(ct.data(), ct.size()) << std::endl;
    } 
    else {
        std::cout << "Key length not supported (8 or 24 bytes)" << std::endl;
    }

    return 0;
}
