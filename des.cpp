#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

string convert_decimal_to_binary(int decimal) {
    return bitset<4>(decimal).to_string();
}

int convert_binary_to_decimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

string Xor(const string& a, const string& b) {
    string result = "";
    for (size_t i = 0; i < b.size(); i++) {
        result += (a[i] != b[i]) ? '1' : '0';
    }
    return result;
}

string hexToBinary(const string& hex) {
    string binary = "";
    for (char c : hex) {
        switch (toupper(c)) {
            case '0': binary += "0000"; break;
            case '1': binary += "0001"; break;
            case '2': binary += "0010"; break;
            case '3': binary += "0011"; break;
            case '4': binary += "0100"; break;
            case '5': binary += "0101"; break;
            case '6': binary += "0110"; break;
            case '7': binary += "0111"; break;
            case '8': binary += "1000"; break;
            case '9': binary += "1001"; break;
            case 'A': binary += "1010"; break;
            case 'B': binary += "1011"; break;
            case 'C': binary += "1100"; break;
            case 'D': binary += "1101"; break;
            case 'E': binary += "1110"; break;
            case 'F': binary += "1111"; break;
            default: break;
        }
    }
    return binary;
}

string binaryToHex(const string& binary) {
    string hex = "";
    for (size_t i = 0; i < binary.length(); i += 4) {
        string nibble = binary.substr(i, 4);
        int val = stoi(nibble, nullptr, 2);
        hex += "0123456789ABCDEF"[val];
    }
    return hex;
}

string initial_permutation(const string& input) {
    const int ip[64] = {
        58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
    };
    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += input[ip[i] - 1];
    }
    return permuted;
}

string inverse_initial_permutation(const string& input) {
    const int fp[64] = {
        40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
    };
    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += input[fp[i] - 1];
    }
    return permuted;
}

class KeyGenerator {
private:
    string key;
    vector<string> roundKeys;
    const int pc1[56] = {
        57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4
    };
    const int pc2[48] = {
        14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,
        41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
    };
    string shift_left_once(const string& s) { return s.substr(1) + s[0]; }
    string shift_left_twice(string s) { return shift_left_once(shift_left_once(s)); }

public:
    KeyGenerator(const string& input_key) : key(input_key) {}
    void generateRoundKeys() {
        roundKeys.clear();
        string permutedKey = "";
        for (int i = 0; i < 56; i++) permutedKey += key[pc1[i] - 1];
        string left = permutedKey.substr(0, 28);
        string right = permutedKey.substr(28, 28);
        for (int i = 0; i < 16; i++) {
            if (i == 0 || i == 1 || i == 8 || i == 15) {
                left = shift_left_once(left);
                right = shift_left_once(right);
            } else {
                left = shift_left_twice(left);
                right = shift_left_twice(right);
            }
            string combined = left + right;
            string roundKey = "";
            for (int j = 0; j < 48; j++) roundKey += combined[pc2[j] - 1];
            roundKeys.push_back(roundKey);
        }
    }
    const vector<string>& getRoundKeys() const { return roundKeys; }
};

class DES {
private:
    const int expansion_table[48] = {
        32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1
    };
    const int permutation_tab[32] = {
        16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
    };
    const int sbox[8][4][16] = {{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },{
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },{
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },{
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },{
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },{
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },{
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },{
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};
    vector<string> round_keys;
    
    string feistel_core(const string& input, const vector<string>& keys) {
        string perm = initial_permutation(input);
        string left = perm.substr(0, 32);
        string right = perm.substr(32, 32);
        for (int r = 0; r < 16; r++) {
            string expanded = "";
            for (int i = 0; i < 48; i++) expanded += right[expansion_table[i] - 1];
            string xored = Xor(keys[r], expanded);
            string sbox_result = "";
            for (int i = 0; i < 8; i++) {
                string row_str = string(1, xored[i*6]) + string(1, xored[i*6+5]);
                string col_str = xored.substr(i*6+1, 4);
                int row = stoi(row_str, nullptr, 2);
                int col = stoi(col_str, nullptr, 2);
                int val = sbox[i][row][col];
                sbox_result += bitset<4>(val).to_string();
            }
            string permuted = "";
            for (int i = 0; i < 32; i++) permuted += sbox_result[permutation_tab[i] - 1];
            string new_right = Xor(permuted, left);
            left = right;
            right = new_right;
        }
        return inverse_initial_permutation(right + left);
    }

public:
    DES(const vector<string>& keys) : round_keys(keys) {}
    string encrypt_block(const string& block) { return feistel_core(block, round_keys); }
    string decrypt_block(const string& block) {
        vector<string> rev = round_keys;
        std::reverse(rev.begin(), rev.end());
        return feistel_core(block, rev);
    }
    string encrypt(const string& plaintext) {
        string result = "";
        for (size_t i = 0; i < plaintext.length(); i += 64) {
            string block = plaintext.substr(i, 64);
            if (block.length() < 64) block.append(64 - block.length(), '0');
            result += encrypt_block(block);
        }
        return result;
    }
    string decrypt(const string& ciphertext) {
        string result = "";
        for (size_t i = 0; i < ciphertext.length(); i += 64) {
            string block = ciphertext.substr(i, 64);
            result += decrypt_block(block);
        }
        while (result.length() > 0 && result.back() == '0') result.pop_back();
        return result;
    }
};

bool isValidBinary(const string& s, int length) {
    if ((int)s.length() != length) return false;
    for (char c : s) if (c != '0' && c != '1') return false;
    return true;
}

int main(int argc, char* argv[]) {
    string mode;
    bool hexInput = false;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-e") mode = "encrypt";
        else if (arg == "-d") mode = "decrypt";
        else if (arg == "-hex") hexInput = true;
    }
    if (mode.empty()) {
        cout << "1. Encrypt\n2. Decrypt\nChoice: ";
        int choice; cin >> choice; cin.ignore();
        mode = (choice == 1) ? "encrypt" : "decrypt";
        cout << "format (binary/hex): ";
        string fmt; cin >> fmt; cin.ignore();
        hexInput = (fmt == "hex");
    }
    cout << "Key (64bit binary" << (hexInput ? " or 16 hex" : "") << "): ";
    string key; getline(cin, key);
    if (hexInput && key.length() == 16) key = hexToBinary(key);
    if (!isValidBinary(key, 64)) { cerr << "Invalid key\n"; return 1; }
    cout << (mode == "encrypt" ? "Plaintext" : "Ciphertext") << ": ";
    string input; getline(cin, input);
    if (hexInput && input.length() % 16 == 0) input = hexToBinary(input);
    KeyGenerator kg(key); kg.generateRoundKeys();
    DES des(kg.getRoundKeys());
    string output = (mode == "encrypt") ? des.encrypt(input) : des.decrypt(input);
    cout << "\nResult (binary): " << output << "\n";
    if (output.length() % 4 == 0) cout << "Result (hex): " << binaryToHex(output) << "\n";
    return 0;
}
