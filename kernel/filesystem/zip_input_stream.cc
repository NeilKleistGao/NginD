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

/// @file zip_input_stream.cc

#include "zip_input_stream.h"

#include "snappy/snappy.h"

namespace ngind::filesystem {

ZipInputStream::ZipInputStream(InputStream* stream) : InputStream(), _stream(stream) {
    if (stream != nullptr) {
        _opened = true;
        _stream->addReference();
    }
}

ZipInputStream::~ZipInputStream() {
    if (_stream != nullptr) {
        if (_opened) {
            _stream->close();
            _opened = false;
        }

        _stream->removeReference();
    }
}

void ZipInputStream::close() {
    if (_opened) {
        _stream->close();
        _opened = false;
    }
}

std::string ZipInputStream::readAllCharacters() {
    std::string content = _stream->readAllCharacters();
    std::string res;
    snappy::Uncompress(content.data(), content.size(), &res);
    return res;
}

} // namespace ngind::filesystem