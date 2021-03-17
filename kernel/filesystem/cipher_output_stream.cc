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

/// @file cipher_output_stream.cc

#include "cipher_output_stream.h"
#include "crypto/aes.h"

namespace ngind::filesystem {

CipherOutputStream::CipherOutputStream(OutputStream* stream) : OutputStream(), _stream(stream), _opened(false), _buffer() {
    if (_stream != nullptr) {
        _opened = true;
        _stream->addReference();
    }
}

CipherOutputStream::~CipherOutputStream() {
    if (_stream != nullptr) {
        if (_opened) {
            _stream->close();
            _opened = false;
        }

        _stream->removeReference();
    }
}

void CipherOutputStream::write(const char& c) {
    if (_opened) {
        _buffer += c;
    }
}

void CipherOutputStream::write(const std::string& str) {
    if (_opened) {
        _buffer += str;
    }
}


void CipherOutputStream::close() {
    if (!_buffer.empty() && _opened) {
        _stream->write(crypto::AES::getInstance()->encrypt(_buffer));
        _stream->close();
        _opened = false;
        _buffer = "";
    }
}

} // namespace ngind::filesystem