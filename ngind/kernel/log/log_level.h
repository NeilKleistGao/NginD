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

/// @file log_level.h
/// @date 2020/9/21

/// @brief This file includes the declaration of log level

#ifndef NGIND_LOG_LEVEL_H
#define NGIND_LOG_LEVEL_H

namespace ngind {

/**
@enum
    The level of logger. The higher level is, the less general
information will be showed.
*/
enum LogLevel {
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_DEBUG = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERROR = 3
};
} // namespace ngind

#endif //NGIND_LOG_LEVEL_H
