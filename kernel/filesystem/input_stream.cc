/**
 * @copybrief
 * MIT License
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

/// @file input_stream.cc

#include "input_stream.h"

#include <iostream>
#include <cstring>

namespace ngind::filesystem {

size_t InputStream::read(char* buff, const size_t& offset, const size_t& len) {
    for (size_t i = 0; i < len; i++) {
        buff[offset + i] = this->read();

        if (buff[offset + i] == 0) {
            return i + 1;
        }
    }

    return len;
}

char* InputStream::readNCharacters(const size_t& n) {
    if (n == 0) {
        /// @todo throw
    }

    char* buff = new(std::nothrow) char[n];
    if (buff == nullptr) {
        /// @todo throw
    }

    std::memset(buff, 0, sizeof(char) * n);
    this->read(buff, 0, n);
    return buff;
}

size_t InputStream::skip(const size_t& n) {
    if (n == 0) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        char c = this->read();
        if (c == 0) {
            return i + 1;
        }
    }

    return n;
}

size_t InputStream::transferTo(OutputStream* output) {
    return 0; /// @todo redesign output stream
}

} // namespace ngind::filesystem

