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

/// @file logger.h
/// @date 2020/10/16

/**
@brief This file declares the logger class. This file also includes the implementations
of some template functions.
*/

#ifndef NGIND_LOGGER_H
#define NGIND_LOGGER_H

#include <iostream>
#include <cstdio>

#include "log_level.h"
#include "filesystem/output_stream.h"

namespace ngind {
/**
@class
    This class is used to log text information for debug and recording data. You should
not create the instance directly. Try to use factory instead.
*/
class Logger {
public:
    /// @public
    /// @param const std::string&: the filename this logger uses
    /// @param const LogLevel&: the level of logger
    Logger(const std::string&, const LogLevel&);

    /// @public
    ~Logger();

    /// @public
    /// @static
    /// @property The special filename references for stdout and stderr
    const static std::string& STDOUT, &STDERR;

    /// @public
    /// @fn Output some message to logger file
    /// @tparam T: the type of message
    /// @param const T& msg: the message to be outputted
    /// @param const LogLevel& level: the type of log information
    /// @return void
    template<typename T>
    void log(const T& msg, const LogLevel& level = LogLevel::LOG_LEVEL_DEBUG) {
        if (level < this->_level) {
            return;
        }

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
            _stream << msg;
        }
        else {
            int pos = format.find('%');
            _stream << format.substr(0,pos) << msg << format.substr(pos + 1);
        }
    }

    /// @public
    /// @fn Close the log stream
    /// @param void
    /// @return void
    inline void close() {
        if (_stream.isOpen()) {
            _stream.close();
        }
    }
private:
    /// @private
    /// @static
    /// @property The output format for information printed in stdout or stderr
    constexpr static char STD_INFO_FORMAT[] = "\033[34m[info]\033[0m %\n";

    /// @private
    /// @static
    /// @property The output format for debug text printed in stdout or stderr
    constexpr static char STD_DEBUG_FORMAT[] = "\033[35m[debug]\033[0m %\n";

    /// @private
    /// @static
    /// @property The output format for warning text printed in stdout or stderr
    constexpr static char STD_WARNING_FORMAT[] = "\033[33m[warning] %\033[0m\n";

    /// @private
    /// @static
    /// @property The output format for error text printed in stdout or stderr
    constexpr static char STD_ERROR_FORMAT[] = "\033[31m[error] %\033[0m\n";

    /// @private
    /// @static
    /// @property The output format for information printed in files
    constexpr static char INFO_FORMAT[] = "[info] %\n";

    /// @private
    /// @static
    /// @property The output format for debug text printed in files
    constexpr static char DEBUG_FORMAT[] = "[debug] %\n";

    /// @private
    /// @static
    /// @property The output format for warning text printed in files
    constexpr static char WARNING_FORMAT[] = "[warning] %\n";

    /// @private
    /// @static
    /// @property The output format for error text printed in files
    constexpr static char ERROR_FORMAT[] = "[error] %\n";

    /// @private
    /// @property The output format for information this logger now uses
    char* _info_format;

    /// @private
    /// @property The output format for debug text this logger now uses
    char* _debug_format;

    /// @private
    /// @property The output format for warning text this logger now uses
    char* _warning_format;

    /// @private
    /// @property The output format for error text this logger now uses
    char* _error_format;

    /// @private
    /// @property The output stream object
    OutputStream _stream;

    /// @private
    /// @property The minimum level that could be outputted
    LogLevel _level;
};
} // namespace ngind

#endif //NGIND_LOGGER_H
