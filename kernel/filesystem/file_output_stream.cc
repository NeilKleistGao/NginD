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

/// @file file_output_stream.h

#include "file_output_stream.h"

#include "exceptions/game_exception.h"

namespace ngind::filesystem {
FileOutputStream::FileOutputStream(const std::string& filename) : FileOutputStream(filename, false) {
}

FileOutputStream::FileOutputStream(const std::string& filename, const bool& append) : _fp(nullptr), _filename(filename) {
    this->open(filename, append);
}

void FileOutputStream::open(const std::string& filename) {
    this->open(filename, false);
}

void FileOutputStream::open(const std::string& filename, const bool& append) {
    if (_fp != nullptr) {
        this->close();
    }

    _filename = filename;
    _fp = fopen(filename.c_str(), append ? "ab" : "wb");

    if (_fp == nullptr) {
        throw exceptions::GameException("filesystem::FileOutputStream",
                                        "open",
                                        "can't open file " + filename);
    }
}

void FileOutputStream::write(const char& c) {
    if (_fp == nullptr) {
        throw exceptions::GameException("filesystem::FileOutputStream",
                                        "write",
                                        "can't write file " + _filename);
    }

    fputc(c, _fp);
}

void FileOutputStream::flush() {
    if (_fp == nullptr) {
        throw exceptions::GameException("filesystem::FileOutputStream",
                                        "flush",
                                        "can't flush file " + _filename);
    }

    fflush(_fp);
}

void FileOutputStream::close() {
    if (_fp == nullptr) {
        throw exceptions::GameException("filesystem::FileOutputStream",
                                        "flush",
                                        "can't close file " + _filename);
    }

    fclose(_fp);
}

void FileOutputStream::write(const std::string& str) {
    for (const auto& c : str) {
        write(c);
    }
}

} // namespace ngind::filesystem