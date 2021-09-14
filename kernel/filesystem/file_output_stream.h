/** MIT License
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

/// @file file_output_stream.h

#ifndef NGIND_FILE_OUTPUT_STREAM_H
#define NGIND_FILE_OUTPUT_STREAM_H

#include "output_stream.h"

namespace ngind::filesystem {

/**
 * Text file output class.
 */
class FileOutputStream : public OutputStream {
public:
    /**
     * @param filename: name of file to be opened.
     */
    explicit FileOutputStream(const std::string& filename);

    /**
     * @param filename: name of file to be opened.
     * @param append: true if append text at end of file.
     */
    FileOutputStream(const std::string& filename, const bool& append);

    FileOutputStream(const FileOutputStream&) = delete;
    FileOutputStream& operator= (const FileOutputStream&) = delete;

    /**
     * Open a file.
     * @param filename: file's name
     */
    void open(const std::string& filename);

    /**
     * Open a file.
     * @param filename: file's name
     * @param append:true if append text at end of file.
     */
    void open(const std::string& filename, const bool& append);

    /**
     * @see kernel/filesystem/output_stream.h
     */
    void write(const char& c) override;

    /**
     * Write a string into the file.
     * @param str: string to be written.
     */
    void write(const std::string& str) override;

    /**
     * @see kernel/filesystem/output_stream.h
     */
    void flush() override;

    /**
     * @see kernel/filesystem/output_stream.h
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

#endif //NGIND_FILE_OUTPUT_STREAM_H
