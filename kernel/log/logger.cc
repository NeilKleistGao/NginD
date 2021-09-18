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

/// @file logger.cc

#include "logger.h"

namespace ngind::log {
void Logger::log(const std::string& msg, const LogLevel& level) {
    if (level < this->_level) {
        return;
    }

    std::string format_msg;
    switch (level) {
        case LogLevel::LOG_LEVEL_INFO:
            format_msg = std::string{INFO_FORMAT}.append(msg);
            break;
        case LogLevel::LOG_LEVEL_DEBUG:
            format_msg = std::string{DEBUG_FORMAT}.append(msg);
            break;
        case LogLevel::LOG_LEVEL_WARNING:
            format_msg = std::string{WARNING_FORMAT}.append(msg);
            break;
        case LogLevel::LOG_LEVEL_ERROR:
            format_msg = std::string{ERROR_FORMAT}.append(msg);
            break;
        default:
            format_msg = msg;
            break;
    }

    auto now = timer::Timer::getNow();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    char buffer[128];

    auto size = std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&tt));
    if (size) {
        std::string hs = "{time}";
        auto index = format_msg.find(hs);
        format_msg.replace(index, hs.length(), buffer);
    }

    _output->write(format_msg);

    if (level == LogLevel::LOG_LEVEL_ERROR) {
        _output->close();
        std::terminate();
    }
}
} // namespace ngind::log