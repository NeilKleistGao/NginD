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
// LAST MODIFY: 2020/10/1

#ifndef NGIND_LOGGER_H
#define NGIND_LOGGER_H

#include <iostream>
#include <cstdio>

#include "log_level.h"

namespace ngind {
class Logger {
public:
    explicit Logger(const std::string&);
    ~Logger();

    void log();

    constexpr static LogLevel LOG_LEVEL = LogLevel::LOG_LEVEL_DEBUG;

    constexpr static char STDIN_INFO_FORMAT[] = "\033[34m[info]\033[0m %s\n";
    constexpr static char STDIN_DEBUG_FORMAT[] = "\033[35m[debug]\033[0m %s\n";
    constexpr static char STDIN_WARNING_FORMAT[] = "\033[33m[warning] %s\033[0m\n";
    constexpr static char STDIN_ERROR_FORMAT[] = "\033[31m[error] %s\033[0m\n";

    constexpr static char INFO_FORMAT[] = "[info] %s\n";
    constexpr static char DEBUG_FORMAT[] = "[debug] %s\n";
    constexpr static char WARNING_FORMAT[] = "[warning] %s\n";
    constexpr static char ERROR_FORMAT[] = "[error] %s\n";

    inline void close() {
        // TODO:
    }
private:

};
} // namespace ngind

#endif //NGIND_LOGGER_H
