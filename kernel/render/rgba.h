/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// FILENAME: rgba.h
// LAST MODIFY: 2020/10/25

#ifndef NGIND_RGBA_H
#define NGIND_RGBA_H

#include "utils/converter.h"

namespace ngind {

struct RGBA {
    RGBA() = default;
    explicit RGBA(const std::string& code) {
        auto color = Converter::convertHexString(code.substr(1));
        r = (color & 0xFF000000) >> 24;
        g = (color & 0x00FF0000) >> 16;
        b = (color & 0x0000FF00) >> 8;
        a = color & 0x000000FF;
    }

    unsigned char r, g, b, a;
};

} // namespace ngind

#endif //NGIND_RGBA_H
