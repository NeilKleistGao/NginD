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

/// @file file_input_stream.cc

#include <filesystem>

#include "file_input_stream.h"
#include "exceptions/game_exception.h"

namespace ngind::filesystem {

FileInputStream::FileInputStream(const std::string& filename) : InputStream(), _fp(nullptr), _filename(filename) {
    this->open(filename);
}

FileInputStream::~FileInputStream() {

}

void FileInputStream::open(const std::string& filename) {
    this->_filename = filename;

    if (_fp != nullptr) {
        this->close();
    }

    _fp = fopen(filename.c_str(), "rb");
    if (_fp == nullptr) {
        throw exceptions::GameException("filesystem::FileInputStream",
                                        "open",
                                        "can't open file " + filename);
    }
}

char FileInputStream::read() {
    if (_fp == nullptr) {
        throw exceptions::GameException("filesystem::FileInputStream",
                                        "read",
                                        "can't read file " + this->_filename);
    }

    auto c = fgetc(_fp);
    return c;
}

std::string FileInputStream::read(const size_t& size) {
    std::string str;
    for (int i = 0; i < size; i++) {
        char c = read();
        str += c;
    }

    return str;
}

void FileInputStream::close() {
    if (_fp != nullptr) {
        fclose(_fp);
        _fp = nullptr;
    }
}

std::string FileInputStream::readAllCharacters() {
    std::filesystem::path path{_filename};
    int size = std::filesystem::file_size(path);
    return this->readNCharacters(size);
}

} // namespace ngind::filesystem
