// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: logger.h
// LAST MODIFY: 2020/10/10

#ifndef NGIND_LOGGER_H
#define NGIND_LOGGER_H

#include <iostream>
#include <cstdio>

#include "log_level.h"
#include "filesystem/output_stream.h"

namespace ngind {
class Logger {
public:
    explicit Logger(const std::string&);
    ~Logger();

    template<typename T>
    void log(const T& msg, const LogLevel& level = LogLevel::LOG_LEVEL_DEBUG) {
        std::string format;
        switch (level) {
            case LOG_LEVEL_INFO:
                format = _info_format;
                break;
            case LOG_LEVEL_DEBUG:
                format = _debug_format;
                break;
            case LOG_LEVEL_WARNING:
                format = _warning_format;
                break;
            case LOG_LEVEL_ERROR:
                format = _error_format;
                break;
        }

        if (format.empty()) {
            _stream << msg << std::endl;
        }
        else {
            int pos = format.find('%');
            _stream << format.substr(0,pos) << msg << format.substr(pos + 1);
        }
    }

    constexpr static LogLevel LOG_LEVEL = LogLevel::LOG_LEVEL_DEBUG;

    inline void close() {
        if (_stream.isOpen()) {
            _stream.close();
        }
    }
private:
    constexpr static char STD_INFO_FORMAT[] = "\033[34m[info]\033[0m %\n";
    constexpr static char STD_DEBUG_FORMAT[] = "\033[35m[debug]\033[0m %\n";
    constexpr static char STD_WARNING_FORMAT[] = "\033[33m[warning] %\033[0m\n";
    constexpr static char STD_ERROR_FORMAT[] = "\033[31m[error] %\033[0m\n";

    constexpr static char INFO_FORMAT[] = "[info] %\n";
    constexpr static char DEBUG_FORMAT[] = "[debug] %\n";
    constexpr static char WARNING_FORMAT[] = "[warning] %\n";
    constexpr static char ERROR_FORMAT[] = "[error] %\n";

    char* _info_format;
    char* _debug_format;
    char* _warning_format;
    char* _error_format;

    OutputStream _stream;
};
} // namespace ngind

#endif //NGIND_LOGGER_H
