/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/// @file log_stream.h
/// @date 2020/10/16

/**
@brief
    This file includes an output object based on stream only used in log system.
    Don't use it in general file output. Use File class instead.
*/

#ifndef NGIND_OUTPUT_STREAM_H
#define NGIND_OUTPUT_STREAM_H

#include <iostream>
#include <fstream>

namespace ngind {

/**
@class
    This class is specially defined for log system so it can only write and without any
function about reading.
    Don't use it in general file output. Use File class instead.
*/
class OutputStream {
public:
    /// @public
    /// @static
    /// @property The names of some special files such as stdout and stderr
    const static std::string STDOUT, STDERR;

    /// @public
    /// @param std::string The filename of log file
    explicit OutputStream(std::string);
    /// @public
    ~OutputStream();

    OutputStream(const OutputStream&) = delete;
    OutputStream& operator= (const OutputStream&) = delete;

    /// @public
    /// @fn Write log information to the file
    /// @tparam Type: The type of information
    /// @param const Type& content: information to be output
    /// @return void
    template<typename Type>
    void output(const Type& content) {
        if (_filename == STDOUT) {
            std::cout << content;
        }
        else if (_filename == STDERR) {
            std::cerr << content;
        }
        else {
            _stream << content;
        }
    }

    /// @public
    /// @fn Close this stream
    /// @param void
    /// @return void
    inline void close() {
        if (_stream.is_open()) {
            _stream.close();
        }
    }

    /// @public
    /// @fn Get if this stream is open
    /// @param void
    /// @return bool, true if this stream is still open
    inline bool isOpen() {
        return _stream.is_open();
    }
private:
    /// @private
    /// @property The real output stream object
    std::ofstream _stream;
    /// @private
    /// @property The name of log file
    std::string _filename;
};

/// @overload Overload stream output operator for easier stream use
/// @tparam Type: The type of output content
/// @param OutputStream& stream: The reference of OutputStream Object
/// @param const Type& content: The content to be output
/// @return OutputStream&, the same reference as param stream
template<typename Type>
OutputStream& operator<< (OutputStream& stream, const Type& content) {
    stream.output(content);
    return stream;
}

} // namespace ngind

#endif //NGIND_OUTPUT_STREAM_H
