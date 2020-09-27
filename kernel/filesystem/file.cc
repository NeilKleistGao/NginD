// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: file.cc
// LAST MODIFY: 2020/9/27

#include "file.h"

#include <utility>

namespace ngind {
File::File() : _fp(nullptr), _open(false), _writeable(false), _readable(false), _binary(false) {
}

File::File(const std::string& filename) : File(filename, "r+") {
}

File::File(const std::string& filename, const std::string& open_type) : File() {
    this->open(filename, open_type);
}

File::~File() {
    this->close();
}

void File::writeLine(const std::string& content) {
    this->write(content + "\n"); // TODO: win & unix
}

std::string File::readLine() {
    if (!this->_readable || !this->_open) {
        return "";
    }

    std::string res;
    char ch = fgetc(this->_fp);
    while (ch != EOF) {
        res += ch;
        if (ch == '\n') {
            break;;
        }

        ch = fgetc(this->_fp);
    }

    return res;
}

void File::write(const std::string& content) {
    this->write(content.c_str(), content.length());
}

void File::write(const char* content, const size_t& length) {
    if (!this->_writeable || !this->_open) {
        return;
    }

    fwrite(content, sizeof(char), length, this->_fp);
}

char* File::read(const size_t& length) {
    if (!this->_readable || !this->_open) {
        return nullptr;
    }

    char* buff = new(std::nothrow) char[length];
    if (buff == nullptr) {
        return buff;
    }

    fread(buff, sizeof(char), length, this->_fp);
    return buff;
}

void File::open(const std::string& filename) {
    this->open(filename, "r+");
}

void File::open(const std::string& filename, const std::string& open_type) {
    this->_fp = fopen(filename.c_str(), open_type.c_str());
    this->_open = (this->_fp != nullptr);
    int plus = open_type.find('+');
    this->_readable = (open_type.find('r') > -1 || plus > -1);
    this->_writeable = (open_type.find('w') || open_type.find('a') > -1 || plus > -1);
    this->_binary = (open_type.find('b') > -1);
}

void File::close() {
    if (this->_open) {
        fclose(this->_fp);
        this->_open = false;
    }
}

Coroutine<char*, const size_t&> File::readAsync(
        const size_t& length,
        typename Coroutine<char*, const size_t&>::callback callback) {
    auto coroutine = Coroutine<char*, const size_t&>([this](const size_t& length) -> char* {
        return this->read(length);
    }, std::move(callback));
    coroutine.run(length);
    return coroutine;
}

Coroutine<void, const std::string&>
        File::writeAsync(const std::string& content,
                         typename Coroutine<void, const std::string&>::callback callback) {
    auto coroutine = Coroutine<void, const std::string&>([this](const std::string& content) {
        this->write(content);
    }, std::move(callback));
    coroutine.run(content);
    return coroutine;
}

Coroutine<void, const char*, const size_t&>
        File::writeAsync(const char* content,
                         const size_t& length,
                         typename Coroutine<void, const char*, const size_t&>::callback callback) {
    auto coroutine = Coroutine<void, const char*, const size_t&>([this](const char* content, const size_t& length) {
        this->write(content, length);
    }, std::move(callback));
    coroutine.run(content, length);
    return coroutine;
}

}