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

DataInputStream::DataInputStream(InputStream*) {

}

DataInputStream::~DataInputStream() {

}

char DataInputStream::read() {

}

void DataInputStream::close() {

}

void DataInputStream::readFully(char buffer[], const size_t& len) {

}

void DataInputStream::readFully(char buffer[], const size_t& offset, const size_t& len) {

}

bool DataInputStream::readBool() {

}

char DataInputStream::readByte() {

}

unsigned char DataInputStream::readUnsignedByte() {

}

short DataInputStream::readShort() {

}

unsigned short DataInputStream::readUnsignedShort() {

}

int DataInputStream::readInt() {

}

unsigned int DataInputStream::readUnsignedInt() {

}

long DataInputStream::readLong() {

}

unsigned long DataInputStream::readUnsignedLong() {

}

long long DataInputStream::readLongLong() {

}

unsigned long long DataInputStream::readUnsignedLongLong() {

}

float DataInputStream::readFloat() {

}

double DataInputStream::readDouble() {

}

} // namespace ngind::filesystem