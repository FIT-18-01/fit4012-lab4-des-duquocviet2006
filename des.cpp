#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& value) {
    string result = value;
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    result.erase(find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), result.end());
    return result;
}

string remove_non_bits(const string& value) {
    string result;
    for (char ch : value) {
        if (ch == '0' || ch == '1') {
            result.push_back(ch);
        }
    }
    return result;
}

int convert_binary_to_decimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

string convert_decimal_to_binary(int decimal) {
    return bitset<4>(decimal).to_string();
}

string xor_bits(const string& a, const string& b) {
    string result;
    result.reserve(min(a.size(), b.size()));
    for (size_t i = 0; i < a.size() && i < b.size(); ++i) {
        result.push_back(a[i] == b[i] ? '0' : '1');
    }
    return result;
}

string initial_permutation(const string& input) {
    const int initial_permutation[64] = {
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    };

    string permuted;
    permuted.reserve(64);
    for (int i = 0; i < 64; ++i) {
        permuted.push_back(input[initial_permutation[i] - 1]);
    }
    return permuted;
}

string inverse_initial_permutation(const string& input) {
    const int inverse_permutation[64] = {
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    };

    string permuted;
    permuted.reserve(64);
    for (int i = 0; i < 64; ++i) {
        permuted.push_back(input[inverse_permutation[i] - 1]);
    }
    return permuted;
}

class KeyGenerator {
private:
    string key;
    vector<string> roundKeys;

    const int pc1[56] = {
        57,49,41,33,25,17,9,
        1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,
        19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,
        7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,
        21,13,5,28,20,12,4
    };

    const int pc2[48] = {
        14,17,11,24,1,5,
        3,28,15,6,21,10,
        23,19,12,4,26,8,
        16,7,27,20,13,2,
        41,52,31,37,47,55,
        30,40,51,45,33,48,
        44,49,39,56,34,53,
        46,42,50,36,29,32
    };

    string shift_left_once(const string& key_chunk) {
        return key_chunk.substr(1) + key_chunk[0];
    }

    string shift_left_twice(string key_chunk) {
        key_chunk = shift_left_once(key_chunk);
        return shift_left_once(key_chunk);
    }

public:
    KeyGenerator(const string& input_key) : key(input_key) {}

    void generateRoundKeys() {
        roundKeys.clear();

        string permutedKey;
        permutedKey.reserve(56);
        for (int i = 0; i < 56; ++i) {
            permutedKey.push_back(key[pc1[i] - 1]);
        }

        string left = permutedKey.substr(0, 28);
        string right = permutedKey.substr(28, 28);

        for (int i = 0; i < 16; ++i) {
            if (i == 0 || i == 1 || i == 8 || i == 15) {
                left = shift_left_once(left);
                right = shift_left_once(right);
            } else {
                left = shift_left_twice(left);
                right = shift_left_twice(right);
            }

            string combinedKey = left + right;
            string roundKey;
            roundKey.reserve(48);
            for (int j = 0; j < 48; ++j) {
                roundKey.push_back(combinedKey[pc2[j] - 1]);
            }
            roundKeys.push_back(roundKey);
            cout << "Key " << i + 1 << ": " << roundKey << endl;
        }
    }

    const vector<string>& getRoundKeys() const {
        return roundKeys;
    }
};

class DES {
private:
    const int expansion_table[48] = {
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };

    const int permutation_tab[32] = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    const int substitution_boxes[8][4][16] = {{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    }, {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    }, {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    }, {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    }, {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    }, {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    }, {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    }, {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};

    vector<string> round_keys;

public:
    DES(const vector<string>& keys) : round_keys(keys) {}

    string process(const string& input, const vector<string>& roundKeys) {
        string permuted = initial_permutation(input);
        string left = permuted.substr(0, 32);
        string right = permuted.substr(32, 32);

        for (int round = 0; round < 16; ++round) {
            string expanded;
            expanded.reserve(48);
            for (int idx = 0; idx < 48; ++idx) {
                expanded.push_back(right[expansion_table[idx] - 1]);
            }

            string xored = xor_bits(expanded, roundKeys[round]);
            string substituted;
            substituted.reserve(32);

            for (int box = 0; box < 8; ++box) {
                string row_bits;
                row_bits.push_back(xored[box * 6]);
                row_bits.push_back(xored[box * 6 + 5]);
                int row = convert_binary_to_decimal(row_bits);

                string col_bits = xored.substr(box * 6 + 1, 4);
                int col = convert_binary_to_decimal(col_bits);

                int value = substitution_boxes[box][row][col];
                substituted += convert_decimal_to_binary(value);
            }

            string permuted_sbox;
            permuted_sbox.reserve(32);
            for (int idx = 0; idx < 32; ++idx) {
                permuted_sbox.push_back(substituted[permutation_tab[idx] - 1]);
            }

            string new_right = xor_bits(left, permuted_sbox);
            left = right;
            right = new_right;
        }

        string combined = right + left;
        return inverse_initial_permutation(combined);
    }

    string encrypt_block(const string& block) {
        return process(block, round_keys);
    }

    string decrypt_block(const string& block) {
        vector<string> reversed_keys(round_keys.rbegin(), round_keys.rend());
        return process(block, reversed_keys);
    }
};

vector<string> split_blocks(const string& bits, size_t block_size) {
    vector<string> blocks;
    for (size_t i = 0; i < bits.size(); i += block_size) {
        blocks.push_back(bits.substr(i, block_size));
    }
    return blocks;
}

string pad_zero(const string& bits) {
    string padded = bits;
    size_t remainder = bits.size() % 64;
    if (remainder != 0) {
        padded.append(64 - remainder, '0');
    }
    return padded;
}

string read_input_line() {
    string line;
    if (!getline(cin, line)) {
        return string();
    }
    return remove_non_bits(trim(line));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode_line;
    if (!getline(cin, mode_line)) {
        cerr << "Missing mode selection." << endl;
        return 1;
    }
    string mode = trim(mode_line);

    if (mode == "1") {
        string plaintext = read_input_line();
        string key = read_input_line();
        if (plaintext.empty() || key.empty()) {
            cerr << "Mode 1 requires plaintext and key." << endl;
            return 1;
        }
        plaintext = pad_zero(plaintext);
        if (key.size() != 64) {
            cerr << "DES key must be 64 bits." << endl;
            return 1;
        }

        KeyGenerator keygen(key);
        keygen.generateRoundKeys();
        DES des(keygen.getRoundKeys());

        string result;
        for (const string& block : split_blocks(plaintext, 64)) {
            result += des.encrypt_block(block);
        }

        cout << "Ciphertext: " << result << endl;
        return 0;
    }

    if (mode == "2") {
        string ciphertext = read_input_line();
        string key = read_input_line();
        if (ciphertext.empty() || key.empty()) {
            cerr << "Mode 2 requires ciphertext and key." << endl;
            return 1;
        }
        if (ciphertext.size() % 64 != 0) {
            cerr << "Ciphertext length must be a multiple of 64 bits." << endl;
            return 1;
        }
        if (key.size() != 64) {
            cerr << "DES key must be 64 bits." << endl;
            return 1;
        }

        KeyGenerator keygen(key);
        keygen.generateRoundKeys();
        DES des(keygen.getRoundKeys());

        string result;
        for (const string& block : split_blocks(ciphertext, 64)) {
            result += des.decrypt_block(block);
        }

        cout << "Plaintext: " << result << endl;
        return 0;
    }

    if (mode == "3") {
        string plaintext = read_input_line();
        string k1 = read_input_line();
        string k2 = read_input_line();
        string k3 = read_input_line();
        if (plaintext.empty() || k1.empty() || k2.empty() || k3.empty()) {
            cerr << "Mode 3 requires plaintext and three keys." << endl;
            return 1;
        }
        if (plaintext.size() % 64 != 0) {
            cerr << "TripleDES plaintext must be a multiple of 64 bits." << endl;
            return 1;
        }
        if (k1.size() != 64 || k2.size() != 64 || k3.size() != 64) {
            cerr << "TripleDES keys must each be 64 bits." << endl;
            return 1;
        }

        KeyGenerator keygen1(k1);
        keygen1.generateRoundKeys();
        DES des1(keygen1.getRoundKeys());

        KeyGenerator keygen2(k2);
        keygen2.generateRoundKeys();
        DES des2(keygen2.getRoundKeys());

        KeyGenerator keygen3(k3);
        keygen3.generateRoundKeys();
        DES des3(keygen3.getRoundKeys());

        string result;
        for (const string& block : split_blocks(plaintext, 64)) {
            string stage1 = des1.encrypt_block(block);
            string stage2 = des2.decrypt_block(stage1);
            string stage3 = des3.encrypt_block(stage2);
            result += stage3;
        }

        cout << "TripleDES Ciphertext: " << result << endl;
        return 0;
    }

    if (mode == "4") {
        string ciphertext = read_input_line();
        string k1 = read_input_line();
        string k2 = read_input_line();
        string k3 = read_input_line();
        if (ciphertext.empty() || k1.empty() || k2.empty() || k3.empty()) {
            cerr << "Mode 4 requires ciphertext and three keys." << endl;
            return 1;
        }
        if (ciphertext.size() % 64 != 0) {
            cerr << "TripleDES ciphertext must be a multiple of 64 bits." << endl;
            return 1;
        }
        if (k1.size() != 64 || k2.size() != 64 || k3.size() != 64) {
            cerr << "TripleDES keys must each be 64 bits." << endl;
            return 1;
        }

        KeyGenerator keygen1(k1);
        keygen1.generateRoundKeys();
        DES des1(keygen1.getRoundKeys());

        KeyGenerator keygen2(k2);
        keygen2.generateRoundKeys();
        DES des2(keygen2.getRoundKeys());

        KeyGenerator keygen3(k3);
        keygen3.generateRoundKeys();
        DES des3(keygen3.getRoundKeys());

        string result;
        for (const string& block : split_blocks(ciphertext, 64)) {
            string stage1 = des3.decrypt_block(block);
            string stage2 = des2.encrypt_block(stage1);
            string stage3 = des1.decrypt_block(stage2);
            result += stage3;
        }

        cout << "TripleDES Plaintext: " << result << endl;
        return 0;
    }

    cerr << "Invalid mode. Use 1, 2, 3 or 4." << endl;
    return 1;
}

    






