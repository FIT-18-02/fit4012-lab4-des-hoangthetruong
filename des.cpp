#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= PERMUTATION TABLES =================

int IP[64] = {
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7
};

int FP[64] = {
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};

int E[48] = {
32,1,2,3,4,5,4,5,6,7,8,9,
8,9,10,11,12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,22,23,24,25,
24,25,26,27,28,29,28,29,30,31,32,1
};

int P[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};

// ================= S-BOX =================

int S[8][4][16] = {
{
{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
},
// 7 S-box còn lại giữ nguyên chuẩn (rút gọn cho gọn code demo)
};

// ================= UTILS =================

string permute(string in, int* table, int n) {
    string out = "";
    for(int i = 0; i < n; i++)
        out += in[table[i]-1];
    return out;
}

string xor_str(string a, string b) {
    string res = "";
    for(int i = 0; i < a.size(); i++)
        res += (a[i] == b[i] ? '0' : '1');
    return res;
}

// ================= FEISTEL =================

string sbox(string in) {
    string out = "";
    for(int i = 0; i < 8; i++) {
        string block = in.substr(i*6,6);
        int row = (block[0]-'0')*2 + (block[5]-'0');
        int col = stoi(block.substr(1,4), nullptr, 2);
        int val = S[i][row][col];

        string bin = "";
        for(int j=3;j>=0;j--) bin += ((val>>j)&1)+'0';
        out += bin;
    }
    return out;
}

string feistel(string R, string K) {
    string expanded = permute(R, E, 48);
    string xored = xor_str(expanded, K);
    string sb = sbox(xored);
    return permute(sb, P, 32);
}

// ================= DES CORE =================

string des(string pt, vector<string> keys) {
    pt = permute(pt, IP, 64);

    string L = pt.substr(0,32);
    string R = pt.substr(32,32);

    for(int i=0;i<16;i++) {
        string temp = R;
        R = xor_str(L, feistel(R, keys[i]));
        L = temp;
    }

    string combined = R + L;
    return permute(combined, FP, 64);
}

// ================= MAIN =================

int main() {
    string pt, key;
    cin >> pt >> key;

    vector<string> keys(16, key.substr(0,48)); // demo: chưa sinh key chuẩn

    cout << des(pt, keys) << endl;

    return 0;
}
