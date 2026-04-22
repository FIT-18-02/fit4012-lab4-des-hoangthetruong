#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

// --- CÁC BẢNG HOÁN VỊ CỐ ĐỊNH (Standard DES Tables) ---
const int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };
const int FP[] = { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25 };
const int E[] = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

// (Lưu ý: Bạn cần điền thêm bảng S-Boxes và PC1, PC2 từ tài liệu Lab để hoàn thiện)

// --- CÁC HÀM TIỆN ÍCH ---

// Hàm hoán vị tổng quát
string permute(string k, const int* table, int n) {
    string per = "";
    for (int i = 0; i < n; i++) {
        per += k[table[i] - 1];
    }
    return per;
}

// Dịch trái vòng
string shift_left(string k, int shifts) {
    string s = "";
    for (int i = 0; i < shifts; i++) {
        for (int j = 1; j < k.length(); j++) s += k[j];
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}

// Phép toán XOR
string xor_func(string a, string b) {
    string res = "";
    for (int i = 0; i < a.length(); i++) {
        res += (a[i] == b[i]) ? "0" : "1";
    }
    return res;
}

// --- THUẬT TOÁN CHÍNH ---

void generate_keys(string key, string subkeys[16]) {
    // 1. PC-1 Permutation
    // 2. Chia đôi C0, D0
    // 3. 16 vòng dịch trái và PC-2 để tạo subkeys
}

string des_encrypt(string block, string subkeys[16]) {
    // 1. Initial Permutation (IP)
    string permuted_block = permute(block, IP, 64);
    string L = permuted_block.substr(0, 32);
    string R = permuted_block.substr(32, 32);

    // 2. 16 vòng Feistel
    for (int i = 0; i < 16; i++) {
        string oldR = R;
        // Mở rộng R (E-box) -> XOR với subkey -> S-box -> P-box -> XOR với L
        // L = oldR; R = newR;
    }

    // 3. Hoán vị nghịch đảo (FP)
    return permute(R + L, FP, 64);
}

int main() {
    // Đọc input từ file hoặc stdin theo yêu cầu bài lab
    // Thực hiện Padding nếu cần
    // Gọi hàm encrypt/decrypt
    return 0;
}
