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

/// @file file.cc
/// @file 2020/10/25

/// @brief This file includes the implementation of File class' functions.

#include "file.h"

#include <utility>
#include <cstring>

namespace ngind {
const std::string File::STDIN = "__STDIN__";
const std::string File::STDOUT = "__STDOUT__";
const std::string File::STDERR = "__STDERR__";

File::File() : _fp(nullptr), _open(false), _writeable(false), _readable(false), _binary(false), _redirect(false) {
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
    this->write(content + "\n"); /// @todo win & unix
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
    std::memset(buff, 0, sizeof(char) * length);

    size_t real_size = fread(buff, sizeof(char), length - 1, this->_fp);
    return (real_size == 0) ? nullptr : buff;
}

void File::open(const std::string& filename) {
    this->open(filename, "r+");
}

void File::open(const std::string& filename, const std::string& open_type) {
    if (filename == STDIN) {
        this->_fp = stdin;
        this->_open = this->_readable = this->_redirect = true;
    }
    else if (filename == STDOUT) {
        this->_fp = stdout;
        this->_open = this->_writeable = this->_redirect = true;
    }
    else if (filename == STDERR) {
        this->_fp = stderr;
        this->_open = this->_writeable = this->_redirect = true;
    }
    else {
        this->_fp = fopen(filename.c_str(), open_type.c_str());
        this->_open = (this->_fp != nullptr);
        int plus = open_type.find('+');
        this->_readable = (open_type.find('r') != -1 || plus != -1);
        this->_writeable = (open_type.find('w') != -1 || open_type.find('a') != -1 || plus != -1);
        this->_binary = (open_type.find('b') != -1);
    }
}

std::string File::readToEnd() {
    const size_t BUFF_SIZE = 256;
    char* buff = read(BUFF_SIZE);

    std::string res;
    while (buff != nullptr) {
        res += buff;
        buff = read(BUFF_SIZE);
    }

    return res;
}

void File::close() {
    if (this->_open && !this->_redirect) {
        fclose(this->_fp);
    }

    this->_fp = nullptr;
    this->_open = false;
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