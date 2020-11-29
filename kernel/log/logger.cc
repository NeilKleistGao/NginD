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

/// @file logger.cc
/// @date 2020/10/16

/** @brief This file includes the implementations of logger class and initializes
the static reference.
*/

#include "logger.h"

namespace ngind {
//const std::string& Logger::STDOUT = OutputStream::STDOUT;
//const std::string& Logger::STDERR = OutputStream::STDERR;

Logger::Logger(const std::string& filename, const LogLevel& level) : /*_stream(filename),*/ _level(level) {
//    if (filename == OutputStream::STDOUT ||
//        filename == OutputStream::STDERR) {
//        this->_info_format = const_cast<char*>(STD_INFO_FORMAT);
//        this->_debug_format = const_cast<char*>(STD_DEBUG_FORMAT);
//        this->_warning_format = const_cast<char*>(STD_WARNING_FORMAT);
//        this->_error_format = const_cast<char*>(STD_ERROR_FORMAT);
//    }
//    else {
//        this->_info_format = const_cast<char*>(INFO_FORMAT);
//        this->_debug_format = const_cast<char*>(DEBUG_FORMAT);
//        this->_warning_format = const_cast<char*>(WARNING_FORMAT);
//        this->_error_format = const_cast<char*>(ERROR_FORMAT);
//    }

    this->_info_format = const_cast<char*>(INFO_FORMAT);
    this->_debug_format = const_cast<char*>(DEBUG_FORMAT);
    this->_warning_format = const_cast<char*>(WARNING_FORMAT);
    this->_error_format = const_cast<char*>(ERROR_FORMAT);
}

Logger::~Logger() {
    this->close();
}
} // namespace ngind