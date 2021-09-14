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

/// @file logger.h

#ifndef NGIND_LOGGER_H
#define NGIND_LOGGER_H

#include <iostream>
#include <cstdio>
#include <sstream>

#include "log_level.h"
#include "filesystem/file_output_stream.h"
#include "timer/timer.h"

namespace ngind::log {

/** This class is used to log text information for debug and recording data. You should
 * not create the instance directly. Try to use factory instead.
 */
class Logger {
public:
    /**
     * @param filename: the filename this logger uses
     * @param level: the level of logger
     */
    Logger(const std::string& filename, const LogLevel& level) : _level(level), _output{new filesystem::FileOutputStream{filename}} {
    }
    
    ~Logger() {
        _output->close();
        delete _output;
        _output = nullptr;
    }

    /**
     * Output some message to logger file
     * @tparam T: the type of message
     * @param msg: the message to be outputted
     * @param level: the type of log information
     */
    template<typename T>
    void log(const T& msg, const LogLevel& level = LogLevel::LOG_LEVEL_DEBUG) {
        if (level < this->_level) {
            return;
        }
        std::string string_msg = msg;

        std::string format_msg;
        switch (level) {
            case LogLevel::LOG_LEVEL_INFO:
                format_msg = std::string{INFO_FORMAT}.append(string_msg);
                break;
            case LogLevel::LOG_LEVEL_DEBUG:
                format_msg = std::string{DEBUG_FORMAT}.append(string_msg);
                break;
            case LogLevel::LOG_LEVEL_WARNING:
                format_msg = std::string{WARNING_FORMAT}.append(string_msg);
                break;
            case LogLevel::LOG_LEVEL_ERROR:
                format_msg = std::string{ERROR_FORMAT}.append(string_msg);
                break;
            default:
                format_msg = std::move(string_msg);
                break;
        }

        auto now = timer::Timer::getNow();
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        char buffer[128];

        auto size = std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&tt));
        if (size) {
            std::string hs = "{time}";
            int index = format_msg.find(hs);
            format_msg.replace(index, hs.length(), buffer);
        }

        _output->write(format_msg);

        if (level == LogLevel::LOG_LEVEL_ERROR) {
            close();
            std::terminate();
        }
    }

    /**
     * Close the log stream
     */
    inline void close() {
        _output->close();
    }
private:
    /**
     * The output format for information printed in files.
     */
    constexpr static char INFO_FORMAT[] = "[info {time}]";

    /**
     * The output format for debug text printed in files.
     */
    constexpr static char DEBUG_FORMAT[] = "[debug {time}]";
    
    /**
     * The output format for warning text printed in files.
     */
    constexpr static char WARNING_FORMAT[] = "[warning {time}]";

    /**
     * The output format for error text printed in files.
     */
    constexpr static char ERROR_FORMAT[] = "[error {time}]";
    
    /**
     * The minimum level that could be outputted.
     */
    LogLevel _level;

    /**
     * String converter.
     */
    std::stringstream _string_stream;

    filesystem::FileOutputStream* _output;
};

} // namespace ngind::log

#endif //NGIND_LOGGER_H
