/** MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file aes.cc

#include "aes.h"

#include <iostream>
#include <cassert>

#include "math/galois_field.h"

namespace ngind::crypto {
AES* AES::_instance = nullptr;

AES::AES() : _password() {
    _password = "{{{{PASSWORD}}}}";
    assert(_password.length() <= 16);

    while (_password.length() < 16) {
        _password += '\0';
    }

    extendKey();
}

AES* AES::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) AES();

        if (_instance == nullptr) {
            // TODO:
        }
    }

    return _instance;
}

void AES::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

std::string AES::encrypt(std::string content) {
    for (unsigned int i = content.length() % 16; i < 16 && i != 0; ++i) {
        content += '\0';
    }

    return aes(content, true);
}

std::string AES::decrypt(const std::string& content) {
    std::string res = aes(content, false);
    for (int i = res.length() - 1; ; --i) {
        if (res[i] != 0) {
            res = res.substr(0, i);
            break;
        }
    }

    return res;
}

void AES::extendKey() {
    for (int i = 0; i < 4; ++i) {
        _ex_key[i] = (static_cast<unsigned int>(_password[(i << 2)]) << 24) |
                (static_cast<unsigned int>(_password[(i << 2) + 1]) << 16) |
                (static_cast<unsigned int>(_password[(i << 2) + 2]) << 8) |
                (static_cast<unsigned int>(_password[(i << 2) + 3]));
    }

    for (int i = 4, j = 0; i < 44; ++i) {
        if (i & 3) {
            _ex_key[i] = _ex_key[i - 4] ^ _ex_key[i - 1];
        }
        else {
            _ex_key[i] = _ex_key[i - 4];
            unsigned int arr[4] = {
                    ((_ex_key[i - 1] >> 16) & 0xff),
                    ((_ex_key[i - 1] >> 8) & 0xff),
                    ((_ex_key[i - 1]) & 0xff),
                    ((_ex_key[i - 1] >> 24) & 0xff)
            };

            for (int k = 0; k < 4; ++k) {
                arr[k] = replace(arr[k]);
            }

            unsigned int temp = (arr[0] << 24) | (arr[1] << 16) |
                    (arr[2] << 8) | (arr[3]);
            temp ^= ROUND_CONST[j];
            _ex_key[i] ^= temp;
            ++j;
        }
    }
}

void AES::replace(unsigned int mat[4][4], const bool& enc) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mat[i][j] = replace(mat[i][j], enc);
        }
    }
}

void AES::shift(unsigned int mat[4][4], const bool& enc) {
    unsigned int temp[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp[i][j] = mat[i][j];
        }
    }

    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mat[i][j] = temp[i][enc ? (i + j) & 3 : (j - i + 4) & 3];
        }
    }
}

void AES::mix(unsigned int mat[4][4], const bool& enc) {
    const auto& mm = enc ? MIX_MAT : RE_MIX_MAT;
    int temp[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp[i][j] = mat[i][j];
        }
    }

    using GF = math::GaloisField;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mat[i][j] = GF::multiply(mm[i][0], temp[0][j]) ^
                    GF::multiply(mm[i][1], temp[1][j]) ^
                    GF::multiply(mm[i][2], temp[2][j])
                    ^ GF::multiply(mm[i][3], temp[3][j]);
        }
    }
}

void AES::addRoundKey(unsigned int mat[4][4], const int& round) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mat[j][i] ^= (_ex_key[(round << 2) + i] >> (8 * (3 - j))) & 0xff;
        }
    }
}

unsigned int AES::replace(const unsigned int& num, const bool& enc) const {
    if (enc) {
        return S_BOX[(num & 0b11110000) >> 4][num & 0b1111];
    }
    else {
        return RS_BOX[(num & 0b11110000) >> 4][num & 0b1111];
    }
}

std::string AES::aes(const std::string& content, const bool& enc) {
    std::string res;
    for (int i = 0; i < content.length(); i += 16) {
        unsigned int mat[4][4] = {
                {static_cast<unsigned int>(content[i + 0]) & 0xff, static_cast<unsigned int>(content[i + 4]) & 0xff,
                        static_cast<unsigned int>(content[i + 8]) & 0xff, static_cast<unsigned int>(content[i + 12]) & 0xff},
                {static_cast<unsigned int>(content[i + 1]) & 0xff, static_cast<unsigned int>(content[i + 5]) & 0xff,
                        static_cast<unsigned int>(content[i + 9]) & 0xff, static_cast<unsigned int>(content[i + 13]) & 0xff},
                {static_cast<unsigned int>(content[i + 2]) & 0xff, static_cast<unsigned int>(content[i + 6]) & 0xff,
                        static_cast<unsigned int>(content[i + 10]) & 0xff, static_cast<unsigned int>(content[i + 14]) & 0xff},
                {static_cast<unsigned int>(content[i + 3]) & 0xff, static_cast<unsigned int>(content[i + 7]) & 0xff,
                        static_cast<unsigned int>(content[i + 11]) & 0xff, static_cast<unsigned int>(content[i + 15]) & 0xff}
        };

        addRoundKey(mat, enc ? 0 : 10);

        for (int j = 1; j < 10; ++j) {
            replace(mat, enc);
            shift(mat, enc);
            mix(mat, enc);
            if (enc) {
                addRoundKey(mat, j);
            }
            else {
                unsigned int reverse[4][4];
                calculateReverse(reverse, 10 - j);
                mix(reverse, enc);

                for (int k = 0; k < 4; ++k) {
                    for (int m = 0; m < 4; ++m) {
                        mat[k][m] ^= reverse[k][m];
                    }
                }
            }
        }

        replace(mat, enc);
        shift(mat, enc);
        addRoundKey(mat, enc ? 10 : 0);

        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                res += static_cast<char>(mat[k][j]);
            }
        }
    }

    return res;
}

void AES::calculateReverse(unsigned int mat[4][4], const int& round) {
    for (int i = 0; i < 4; ++i) {
        mat[i][0] = (_ex_key[(round << 2) + 0] >> ((3 - i) << 3)) & 0xff;
        mat[i][1] = (_ex_key[(round << 2) + 1] >> ((3 - i) << 3)) & 0xff;
        mat[i][2] = (_ex_key[(round << 2) + 2] >> ((3 - i) << 3)) & 0xff;
        mat[i][3] = (_ex_key[(round << 2) + 3] >> ((3 - i) << 3)) & 0xff;
    }
}

} // namespace ngind::crypto