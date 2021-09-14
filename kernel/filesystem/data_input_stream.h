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

/// @file data_input_stream.h

#ifndef NGIND_DATA_INPUT_STREAM_H
#define NGIND_DATA_INPUT_STREAM_H

#include "input_stream.h"

namespace ngind::filesystem {

/**
 * Data input class, used to read plain data from file.
 */
class [[maybe_unused]] DataInputStream : public InputStream {
public:
    /**
     * @param stream: another input stream that data come from.
     */
    explicit DataInputStream(InputStream* stream);
    ~DataInputStream() override;

    /**
     * @see kernel/filesystem/input_stream.h
     */
    char read() override;

    /**
     * @see kernel/filesystem/input_stream.h
     */
    void close() override;

    /**
     * Read bytes filling the whole buffer.
     * @param buffer: where the data would be stored.
     * @param len: length of bytes
     */
    void readFully(char buffer[], const size_t& len);

    /**
     * Read bytes filling the whole buffer.
     * @param buffer: where the data would be stored.
     * @param offset: start position of buffer
     * @param len: length of bytes
     */
    void readFully(char buffer[], const size_t& offset, const size_t& len);

    /**
     * Read a boolean variable.
     * @return bool.
     */
    bool readBool();

    /**
     * Read a byte variable.
     * @return char.
     */
    char readByte();

    /**
     * Read an unsigned byte variable.
     * @return unsigned char.
     */
    unsigned char readUnsignedByte();

    /**
     * Read a short variable.
     * @return short.
     */
    short readShort();

    /**
     * Read an unsigned short variable.
     * @return unsigned short.
     */
    unsigned short readUnsignedShort();

    /**
     * Read an integer variable.
     * @return int.
     */
    int readInt();

    /**
     * Read an unsigned integer variable.
     * @return unsigned int.
     */
    unsigned int readUnsignedInt();

    /**
     * Read a long variable.
     * @return long.
     */
    long readLong();

    /**
     * Read an unsigned long variable.
     * @return unsigned long.
     */
    unsigned long readUnsignedLong();

    /**
     * Read a long long variable.
     * @return long long.
     */
    long long readLongLong();

    /**
     * Read an unsigned long long variable.
     * @return unsigned long long.
     */
    unsigned long long readUnsignedLongLong();

    /**
     * Read a float variable.
     * @return float.
     */
    float readFloat();

    /**
     * Read a double variable.
     * @return double.
     */
    double readDouble();

private:
    /**
     * another input stream that data come from.
     */
    InputStream* _stream;
};

} // namespace ngingd::filesystem

#endif //NGIND_DATA_INPUT_STREAM_H
