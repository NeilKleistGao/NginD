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

/// @file output_stream.h

#ifndef NGIND_OUTPUT_STREAM_H
#define NGIND_OUTPUT_STREAM_H

#include <string>
#include <cstring>

namespace ngind::filesystem {

/**
 * General output stream. Make sure that all other output stream classes inherit from
 * this. Though "stream" its name is, no C++ stream will be used in all stream classes.
 */
class OutputStream {
public:
    OutputStream() = default;
    ~OutputStream() = default;

    /**
     * Write a character.
     * @param c: character to be written.
     */
    virtual void write(const char& c) = 0;

    /**
     * Write buffer in a file.
     * @param buff: buffer to be written
     */
    inline void write(const char* buff) {
        this->write(buff, 0, std::strlen(buff));
    }

    /**
     * Write a string in a file.
     * @param str: string to be written.
     */
    inline void write(const std::string& str) {
        this->write(str.c_str(), 0, str.length());
    }

    /**
     * Write buffer in a file with given offset and length.
     * @param buff: buffer to be written
     * @param offset: offset of buffer. Head of data would be written in buffer[offset]
     * @param len: how many characters you hope it writes
     */
    void write(const char* buff, const size_t& offset, const size_t& len);

    /**
     * Save all modification immediately.
     */
    virtual void flush() {};

    /**
     * Save and close the file.
     */
    virtual void close() {};
};

} // namespace ngind::filesystem

#endif //NGIND_OUTPUT_STREAM_H
