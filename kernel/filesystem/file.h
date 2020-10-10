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
// FILENAME: file.h
// LAST MODIFY: 2020/10/10


#ifndef NGIND_FILE_H
#define NGIND_FILE_H

#include <iostream>
#include <cstdio>

#include "coroutine/coroutine.h"

namespace ngind {

class File {
public:
    File();
    explicit File(const std::string&);
    File(const std::string&, const std::string&);
    File(const File&) = delete;
    File(File&&) = delete;
    ~File();

    const static std::string STDIN, STDOUT, STDERR;

    void writeLine(const std::string&);
    std::string readLine();
    void write(const std::string&);
    void write(const char*, const size_t&);
    char* read(const size_t&);
    std::string readToEnd();

    inline void flush() {
        fflush(this->_fp);
    }

    inline bool isOpen() const {
        return this->_open;
    }

    inline bool isReadable() const {
        return this->_readable;
    }

    inline bool isWriteable() const {
        return this->_writeable;
    }

    inline bool isBinary() const {
        return this->_binary;
    }

    void open(const std::string&);
    void open(const std::string&, const std::string&);

    void close();

    Coroutine<char*, const size_t&> readAsync(const size_t&, typename Coroutine<char*, const size_t&>::callback);
    Coroutine<void, const std::string&> writeAsync(const std::string&, typename Coroutine<void, const std::string&>::callback);
    Coroutine<void, const char*, const size_t&> writeAsync(const char*, const size_t&, typename Coroutine<void, const char*, const size_t&>::callback);

private:
    FILE* _fp;
    bool _open, _readable, _writeable, _binary, _redirect;
};

} // namespace ngind

#endif //NGIND_FILE_H
