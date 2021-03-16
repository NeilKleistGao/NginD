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

/// @file galois_field.cc

#include "galois_field.h"

namespace ngind::math {

unsigned int GaloisField::multiply(const unsigned int& n, const unsigned int& s) {
    unsigned int res;
    switch (n) {
        case 1:
            res = s;
            break;
        case 2:
            res = multiplyBy2(s);
            break;
        case 3:
            res = multiplyBy3(s);
            break;
        case 4:
            res = multiplyBy4(s);
            break;
        case 8:
            res = multiplyBy8(s);
            break;
        case 9:
            res = multiplyBy9(s);
            break;
        case 11:
            res = multiplyBy11(s);
            break;
        case 12:
            res = multiplyBy12(s);
            break;
        case 13:
            res = multiplyBy13(s);
            break;
        case 14:
            res = multiplyBy14(s);
            break;
        default:
            //TODO:
            break;
    }

    return res;
}

unsigned int GaloisField::multiplyBy2(const unsigned int& s) {
    auto res = s << 1;
    if (res & 0x100) {
        res &= 0xff;
        res ^= 0x1b;
    }

    return res;
}

} // namespace ngind::math
