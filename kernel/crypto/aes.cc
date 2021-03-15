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

namespace ngind::crypto {
AES* AES::_instance = nullptr;

AES::AES() : _password() {
    _password = "{{PASSWORD}}";
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
    for (unsigned int i = content.length() % 16; i < 16; ++i) {
        content += '\0';
    }

    return aes(content, true);
}

std::string AES::decrypt(const std::string& content) {
    return aes(content, false);
}

void AES::extendKey() {
    for (int i = 0; i < 4; ++i) {
        _ex_key[i] = (static_cast<unsigned int>(_password[i * 4]) << 24) |
                (static_cast<unsigned int>(_password[i * 4 + 1]) << 16) |
                (static_cast<unsigned int>(_password[i * 4 + 2]) << 8) |
                (static_cast<unsigned int>(_password[i * 4 + 3]));
    }

    for (int i = 4, j = 0; i < 44; ++i) {
        if (i & 3) {
            _ex_key[i] = _ex_key[i - 4] ^ _ex_key[i - 1];
        }
        else {
            _ex_key[i] = _ex_key[i - 4];
            unsigned int arr[4] = {
                    ((_ex_key[i - 1] >> 16) & 0b11111111),
                    ((_ex_key[i - 1] >> 8) & 0b11111111),
                    ((_ex_key[i - 1]) & 0b11111111),
                    ((_ex_key[i - 1] >> 24) & 0b11111111)
            };

            for (int k = 0; k < 4; ++k) {
                arr[k] = replace(arr[k]);
            }

            unsigned int temp = (arr[0] << 24) | (arr[1] << 16) |
                    (arr[2] << 8) | (arr[0]);
            temp ^= ROUND_CONST[j];
            _ex_key[i] ^= temp;
            ++j;
        }
    }
}

void AES::replace(unsigned int mat[4][4], const bool& enc) {

}

void AES::shift(unsigned int mat[4][4], const bool& enc) {

}

void AES::mix(unsigned int mat[4][4], const bool& enc) {

}

void AES::addRoundKey(unsigned int mat[4][4], const int& round) {

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
                {static_cast<unsigned int>(content[i + 0]), static_cast<unsigned int>(content[i + 4]),
                        static_cast<unsigned int>(content[i + 8]), static_cast<unsigned int>(content[i + 12])},
                {static_cast<unsigned int>(content[i + 1]), static_cast<unsigned int>(content[i + 5]),
                        static_cast<unsigned int>(content[i + 9]), static_cast<unsigned int>(content[i + 13])},
                {static_cast<unsigned int>(content[i + 2]), static_cast<unsigned int>(content[i + 6]),
                        static_cast<unsigned int>(content[i + 10]), static_cast<unsigned int>(content[i + 14])},
                {static_cast<unsigned int>(content[i + 3]), static_cast<unsigned int>(content[i + 7]),
                        static_cast<unsigned int>(content[i + 11]), static_cast<unsigned int>(content[i + 15])}
        };

        addRoundKey(mat, 0);

        for (int j = 1; j < 10; ++j) {
            replace(mat, enc);
            shift(mat, enc);
            mix(mat, enc);
            addRoundKey(mat, j);
        }

        replace(mat, enc);
        shift(mat, enc);
        addRoundKey(mat, 10);

        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                res += static_cast<char>(mat[k][j]);
            }
        }
    }

    return res;
}

} // namespace ngind::crypto