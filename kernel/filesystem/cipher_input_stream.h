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

/// @file cipher_input_stream.h

#ifndef NGIND_CIPHER_INPUT_STREAM_H
#define NGIND_CIPHER_INPUT_STREAM_H

#include "input_stream.h"

namespace ngind::filesystem {

class CipherInputStream : public InputStream {
public:
    explicit CipherInputStream(InputStream* stream);
    ~CipherInputStream();

    /**
     * @see kernel/filesystem/input_stream.h
     */
    char read() override {
        return -1;
    }

    /**
     * @see kernel/filesystem/input_stream.h
     */
    void close() override;

    /**
     * @see kernel/filesystem/input_stream.h
     */
    std::string readAllCharacters() override;
private:
    /**
     * @see kernel/filesystem/input_stream.h
     */
    char readByte();

    InputStream* _stream;
    bool _opened;
};

} // namespace ngind::filesystem

#endif //NGIND_CIPHER_INPUT_STREAM_H
