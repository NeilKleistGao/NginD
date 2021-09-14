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

/// @file cipher_output_stream.h

#ifndef NGIND_CIPHER_OUTPUT_STREAM_H
#define NGIND_CIPHER_OUTPUT_STREAM_H

#include "output_stream.h"

namespace ngind::filesystem {

/**
 * Output stream used for encrypted file.
 */
class CipherOutputStream : public OutputStream {
public:
    /**
     * @param stream: the general output stream
     */
    explicit CipherOutputStream(OutputStream* stream);
    ~CipherOutputStream() override;

    /**
     * @see kernel/filesystem/output_stream.h
     */
    void write(const char& c) override;

    /**
     * @see kernel/filesystem/output_stream.h
     */
    void write(const std::string& str) override;

    /**
     * @see kernel/filesystem/output_stream.h
     */
    void flush() override {
        _stream->flush();
    };

    /**
     * @see kernel/filesystem/output_stream.h
     */
    void close() override;
private:
    /**
     * The general output stream. We will encrypt the content before we put them into this stream object.
     */
    OutputStream* _stream;

    /**
     * Store output string temporally. When the buffer is full, the encrypting function will be executed.
     */
    std::string _buffer;

    /**
     * Has the stream been opened.
     */
    bool _opened;
};

} // namespace ngind::filesystem

#endif //NGIND_CIPHER_OUTPUT_STREAM_H
