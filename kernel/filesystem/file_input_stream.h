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

/// @file file_input_stream.h

#ifndef NGIND_FILE_INPUT_STREAM_H
#define NGIND_FILE_INPUT_STREAM_H

#include "input_stream.h"

namespace ngind::filesystem {
/**
 * Text file input class, used to read configuration files, text files vice versa.
 */
class FileInputStream : public InputStream {
public:
    /**
     * @param filename: file's name
     */
    FileInputStream(const std::string& filename);
    ~FileInputStream();

    FileInputStream(const FileInputStream&) = delete;
    FileInputStream& operator=(const FileInputStream&) = delete;

    /**
     * Open a file.
     * @param filename: file's name
     */
    void open(const std::string& filename);

    /**
     * @see kernel/filesystem/input_stream.h
     */
    char read() override;

    /**
     * Read a string from file.
     * @param size: how many characters would be read.
     * @return std::string, the string read from file.
     */
    std::string read(const size_t& size);

    /**
     * @see kernel/filesystem/input_stream.h
     */
    void close() override;
private:
    /**
     * File's name. If no file is opened, it's a blank string.
     */
    std::string _filename;

    /**
     * File pointer of C.
     */
    FILE* _fp;
};
} // namespace ngind::filesystem

#endif //NGIND_FILE_INPUT_STREAM_H
