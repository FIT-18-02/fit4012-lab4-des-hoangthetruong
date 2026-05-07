#include <bits/stdc++.h>
using namespace std;

// ================= BẢNG HOÁN VỊ & S-BOX CHUẨN =================
int IP[64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
              62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
              57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
              61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};

int FP[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
              38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
              36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
              34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};

int PC1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,
               59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,
               31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,
               29,21,13,5,28,20,12,4};

int PC2[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,
               16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,
               48,44,49,39,56,34,53,46,42,50,36,29,32};

int E[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,
             15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,
             26,27,28,29,28,29,30,31,32,1};

int P[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
             2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};

int S[8][4][16] = {
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1}, {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4}, {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6}, {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14}, {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8}, {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

// ================= HÀM BỔ TRỢ =================
string cleanBinary(string s) {
    string res = "";
    for(char c : s) if(c=='0' || c=='1') res += c;
    return res;
}

string permute(string in, int* table, int n) {
    string out = "";
    for(int i = 0; i < n; i++) out += in[table[i]-1];
    return out;
}

string xor_str(string a, string b) {
    string res = "";
    for(size_t i = 0; i < a.size(); i++) res += (a[i] == b[i] ? '0' : '1');
    return res;
}

string binTo4(int n) {
    string s = "";
    for(int i=3; i>=0; i--) s += ((n>>i)&1) ? '1' : '0';
    return s;
}

// ================= SINH KHÓA VÒNG =================
vector<string> generateRoundKeys(string key64) {
    string key56 = permute(key64, PC1, 56);
    string left = key56.substr(0, 28), right = key56.substr(28, 28);
    vector<string> roundKeys;
    int shifts[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    for(int r = 0; r < 16; r++) {
        left = left.substr(shifts[r]) + left.substr(0, shifts[r]);
        right = right.substr(shifts[r]) + right.substr(0, shifts[r]);
        roundKeys.push_back(permute(left + right, PC2, 48));
    }
    return roundKeys;
}

// ================= HÀM FEISTEL =================
string feistel(string R, string K) {
    string expanded = permute(R, E, 48);
    string xored = xor_str(expanded, K);
    string sb_out = "";
    for(int i = 0; i < 8; i++) {
        string b = xored.substr(i*6, 6);
        int r = (b[0]-'0')*2 + (b[5]-'0'), c = stoi(b.substr(1,4), nullptr, 2);
        sb_out += binTo4(S[i][r][c]);
    }
    return permute(sb_out, P, 32);
}

// ================= DES CORE =================
string desEncrypt(string pt64, vector<string>& keys) {
    string ip = permute(pt64, IP, 64);
    string L = ip.substr(0,32), R = ip.substr(32,32);
    for(int i = 0; i < 16; i++) {
        string nextL = R;
        R = xor_str(L, feistel(R, keys[i]));
        L = nextL;
    }
    return permute(R + L, FP, 64);
}

string desDecrypt(string ct64, vector<string>& keys) {
    vector<string> revKeys = keys;
    reverse(revKeys.begin(), revKeys.end());
    return desEncrypt(ct64, revKeys);
}

// ================= TRIPLE DES (3DES) =================
string tripleDESEncrypt(string pt64, string k1, string k2, string k3) {
    auto rk1 = generateRoundKeys(k1), rk2 = generateRoundKeys(k2), rk3 = generateRoundKeys(k3);
    return desEncrypt(desDecrypt(desEncrypt(pt64, rk1), rk2), rk3);
}

string tripleDESDecrypt(string ct64, string k1, string k2, string k3) {
    auto rk1 = generateRoundKeys(k1), rk2 = generateRoundKeys(k2), rk3 = generateRoundKeys(k3);
    return desDecrypt(desEncrypt(desDecrypt(ct64, rk3), rk2), rk1);
}

// ================= MAIN =================
int main() {
    int mode; cin >> mode;
    string line; getline(cin, line); // consume newline

    if(mode == 1 || mode == 2) { // DES
        string pt, key; 
        getline(cin, pt); pt = cleanBinary(pt);
        getline(cin, key); key = cleanBinary(key);
        if(key.length() != 64) { cout << "Invalid key length" << endl; return 0; }
        while(pt.length() % 64 != 0) pt += '0'; // Padding

        vector<string> rk = generateRoundKeys(key);
        for(size_t i = 0; i < pt.length(); i += 64)
            cout << (mode == 1 ? desEncrypt(pt.substr(i,64), rk) : desDecrypt(pt.substr(i,64), rk));
        cout << endl;
    } 
    else if(mode == 3 || mode == 4) { // 3DES
        string pt, k1, k2, k3;
        getline(cin, pt); pt = cleanBinary(pt);
        getline(cin, k1); k1 = cleanBinary(k1);
        getline(cin, k2); k2 = cleanBinary(k2);
        getline(cin, k3); k3 = cleanBinary(k3);
        while(pt.length() % 64 != 0) pt += '0';

        for(size_t i = 0; i < pt.length(); i += 64)
            cout << (mode == 3 ? tripleDESEncrypt(pt.substr(i,64), k1, k2, k3) : tripleDESDecrypt(pt.substr(i,64), k1, k2, k3));
        cout << endl;
    }
    return 0;
}
