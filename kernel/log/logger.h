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
#include "script/lua_registration.h"

namespace ngind::log {

class LoggerFactory;

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

    /**
     * Output some message to logger file
     * @tparam T: the type of message, which is not convertible for std::string
     * @param msg: the message to be outputted
     * @param level: the type of log information
     */
    template<typename T, std::enable_if_t<std::negation_v<std::is_convertible<T, std::string>>, bool> = true>
    void log(T msg, const LogLevel& level = LogLevel::LOG_LEVEL_DEBUG) {
        std::string string_msg;
        std::stringstream stream;
        stream << msg;
        stream >> string_msg;
        log(string_msg, level);
    }

    /**
     * Output some message to logger file
     * @param msg: string message
     * @param level: the type of log information
     */
    void log(const std::string& msg, const LogLevel& level = LogLevel::LOG_LEVEL_DEBUG);

    inline void logForLua(const std::string& msg, int level = 1) {
        log(msg, static_cast<LogLevel>(level));
    }

    /**
     * Flush the current log file.
     */
    inline void flush() {
        _output->flush();
    }

    friend class LoggerFactory;
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

    /**
     * Log file stream.
     */
    filesystem::FileOutputStream* _output;

    ~Logger() {
        _output->close();
        delete _output;
        _output = nullptr;
    }
};

NGIND_LUA_BRIDGE_REGISTRATION(Logger) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .beginClass<Logger>("Logger")
            .addFunction("log", &Logger::logForLua)
            .addFunction("flush", &Logger::flush)
        .endClass()
    .endNamespace();
}

} // namespace ngind::log

#endif //NGIND_LOGGER_H
