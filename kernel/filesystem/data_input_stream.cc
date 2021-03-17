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

/// @file data_input_stream.cc

#include "data_input_stream.h"

namespace ngind::filesystem {

DataInputStream::DataInputStream(InputStream* stream) : InputStream(), _stream{stream} {
}

DataInputStream::~DataInputStream() {
    close();
}

char DataInputStream::read() {
    return _stream->read();
}

void DataInputStream::close() {
    _stream->close();
}

void DataInputStream::readFully(char buffer[], const size_t& len) {
    this->readFully(buffer, 0, len);
}

void DataInputStream::readFully(char buffer[], const size_t& offset, const size_t& len) {
    for (int i = 0; i < len; i++) {
        buffer[i + offset] = this->read();
    }
}

bool DataInputStream::readBool() {
    return (read() == 0) ? false : true;
}

char DataInputStream::readByte() {
    return read();
}

unsigned char DataInputStream::readUnsignedByte() {
    return static_cast<unsigned char>(read());
}

short DataInputStream::readShort() {
    auto h = static_cast<short>(read()), l = static_cast<short>(read());
    return (h << 8) | l;
}

unsigned short DataInputStream::readUnsignedShort() {
    return static_cast<unsigned short>(readShort());
}

int DataInputStream::readInt() {
    auto n1 = static_cast<int>(read()),
         n2 = static_cast<int>(read()),
         n3 = static_cast<int>(read()),
         n4 = static_cast<int>(read());
    return (n1 << 24) | (n2 << 16) | (n3 << 8) | n4;
}

unsigned int DataInputStream::readUnsignedInt() {
    return static_cast<unsigned int>(readInt());
}

long DataInputStream::readLong() {
    if constexpr (sizeof(long) == 8) {
        auto n1 = static_cast<long>(read()),
             n2 = static_cast<long>(read()),
             n3 = static_cast<long>(read()),
             n4 = static_cast<long>(read()),
             n5 = static_cast<long>(read()),
             n6 = static_cast<long>(read()),
             n7 = static_cast<long>(read()),
             n8 = static_cast<long>(read());
        return (n1 << 56) | (n2 << 48) | (n3 << 40) | (n4 << 32) |
                (n5 << 24) | (n6 << 16) | (n7 << 8) | n8;
    }
    else {
        auto n1 = static_cast<long>(read()),
                n2 = static_cast<long>(read()),
                n3 = static_cast<long>(read()),
                n4 = static_cast<long>(read());
        return (n1 << 24) | (n2 << 16) | (n3 << 8) | n4;
    }
}

unsigned long DataInputStream::readUnsignedLong() {
    return static_cast<unsigned long>(readLong());
}

long long DataInputStream::readLongLong() {
    auto n1 = static_cast<long long>(read()),
         n2 = static_cast<long long>(read()),
         n3 = static_cast<long long>(read()),
         n4 = static_cast<long long>(read()),
         n5 = static_cast<long long>(read()),
         n6 = static_cast<long long>(read()),
         n7 = static_cast<long long>(read()),
         n8 = static_cast<long long>(read());
    return (n1 << 56) | (n2 << 48) | (n3 << 40) | (n4 << 32) |
           (n5 << 24) | (n6 << 16) | (n7 << 8) | n8;
}

unsigned long long DataInputStream::readUnsignedLongLong() {
    return static_cast<unsigned long long>(readLongLong());
}

float DataInputStream::readFloat() {
    auto n1 = static_cast<int>(read()),
         n2 = static_cast<int>(read()),
         n3 = static_cast<int>(read()),
         n4 = static_cast<int>(read());
    union {
        int i;
        float f;
    } u;
    u.i = (n1 << 24) | (n2 << 16) | (n3 << 8) | n4;
    return u.f;
}

double DataInputStream::readDouble() {
    auto n1 = static_cast<int>(read()),
         n2 = static_cast<int>(read()),
         n3 = static_cast<int>(read()),
         n4 = static_cast<int>(read()),
         n5 = static_cast<int>(read()),
         n6 = static_cast<int>(read()),
         n7 = static_cast<int>(read()),
         n8 = static_cast<int>(read());
    union {
        long long i;
        double d;
    } u;
    u.i = (n1 << 56) | (n2 << 48) | (n3 << 40) | (n4 << 32) |
            (n5 << 24) | (n6 << 16) | (n7 << 8) | n8;
    return u.d;
}

} // namespace ngind::filesystem