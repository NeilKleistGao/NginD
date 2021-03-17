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

/// @file main.cc

#include <iostream>

#include "aes.h"

int main(int argc, char* argv[]) {
    if (argc == 3) {
        using namespace ngind::crypto;
        std::string in = argv[1], out = argv[2];
        std::string str;
        FILE* fp = fopen(in.c_str(), "rb");
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        for (int i = 0; i < size; i++) {
            char c = fgetc(fp);
            str += c;
        }
        fclose(fp);

        fp = fopen(out.c_str(), "wb");

        auto aes = AES::getInstance();
        std::string res = aes->encrypt(str);
        for (const auto& c : res) {
            fputc(c, fp);
        }
        fclose(fp);

        fp = fopen("test2.jpg", "wb");
        res = aes->decrypt(res);
        for (const auto& c : res) {
            fputc(c, fp);
        }
        fclose(fp);
    }

    return 0;
}