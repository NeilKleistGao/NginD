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

/// @file input_stream.h

#include <cstdio>

#include "output_stream.h"

#ifndef NGIND_INPUT_STREAM_H
#define NGIND_INPUT_STREAM_H

namespace ngind::filesystem {
/**
 * General input stream. Make sure that all other input stream classes inherit from
 * this. Though "stream" its name is, no C++ stream will be used in all stream classes.
 */
class InputStream {
public:
    InputStream() = default;
    ~InputStream() = default;

    /**
     * Read a character.
     * @return char, character read.
     */
    virtual char read() = 0;

    /**
     * Read data and write into buff as possible.
     * @param buff: buffer to store the data
     * @return size_t, the length of data read
     */
    inline size_t read(char* buff) {
        return read(buff, 0, MAX_BUFF_SIZE);
    }

    /**
     * Read data and write into buff with given offset and length
     * @param buff: buffer to store the data
     * @param offset: offset of buffer. Head of data would be written in buffer[offset]
     * @param len: how many characters you hope it reads
     * @return size_t, the actual length of data
     */
    size_t read(char* buff, const size_t& offset, const size_t& len);

    /**
     * Read all characters. The length must be less than max buff size.
     * @return char*, the buffer pointer. Delete it using delete[].
     */
    inline char* readAllCharacters() {
        return this->readNCharacters(MAX_BUFF_SIZE);
    }

    /**
     * Read some characters.
     * @param n: the number of characters.
     * @return char*, the buffer pointer. Delete it using delete[].
     */
    char* readNCharacters(const size_t& n);

    /**
     * Skip some characters.
     * @param n: the number of characters that would be skipped.
     * @return size_t, the actual number skipped.
     */
    size_t skip(const size_t& n);

    /**
     * Close this stream.
     */
    virtual void close() {};

    /**
     * Mark a position if this stream supports.
     * @param pos: where to mark
     */
    virtual void mark(const size_t& pos) {};

    /**
     * Reset to mark.
     */
    virtual void reset() {};

    /**
     * If this stream supports mark
     * @return bool, true if it supports.
     */
    virtual bool isMarkSupported() { return false;};

    /**
     * Read data and write into output stream
     * @param output pointer of output stream
     * @return size_t, length of data
     */
    size_t transferTo(OutputStream* output);

private:
    /**
     * Max buffer size.
     */
    static constexpr size_t MAX_BUFF_SIZE = 1073741824;
protected:
};
} // namespace ngind::filesystem

#endif //NGIND_INPUT_STREAM_H
