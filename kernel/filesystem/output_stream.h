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
// FILENAME: log_stream.h
// LAST MODIFY: 2020/10/10

#ifndef NGIND_OUTPUT_STREAM_H
#define NGIND_OUTPUT_STREAM_H

#include <iostream>
#include <fstream>

namespace ngind {

class OutputStream {
public:
    const static std::string STDOUT, STDERR;

    explicit OutputStream(std::string);
    ~OutputStream();

    OutputStream(const OutputStream&) = delete;
    OutputStream& operator= (const OutputStream&) = delete;

    template<typename Type>
    OutputStream& operator<< (const Type& content) {
        _stream << content;
        return *this;
    }

    inline void close() {
        if (_stream.is_open()) {
            _stream.close();
        }
    }

    inline bool isOpen() {
        return _stream.is_open();
    }
private:
    std::ofstream _stream;
    std::string _filename;
};

} // namespace ngind

#endif //NGIND_OUTPUT_STREAM_H
