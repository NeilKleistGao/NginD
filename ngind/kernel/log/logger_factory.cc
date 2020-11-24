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

/// @file logger_factory.cc
/// @date 2020/10/16

/// @brief This file includes the implementations of logger factory

#include "logger_factory.h"

namespace ngind {
LoggerFactory* LoggerFactory::_instance = nullptr;

LoggerFactory* LoggerFactory::getInstance() {
    if (_instance == nullptr) {
        _instance = new LoggerFactory();
    }

    return _instance;
}

void LoggerFactory::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

Logger* LoggerFactory::getLogger(const std::string& filename, const LogLevel& level) {
    if (_loggers.find(filename) != _loggers.end()) {
        return _loggers[filename];
    }

    _loggers[filename] = new Logger(filename, level);
    return _loggers[filename];
}

LoggerFactory::~LoggerFactory() {
    for (auto pairs : _loggers) {
        delete pairs.second;
        pairs.second = nullptr;
    }

    _loggers.clear();
}

} // namespace ngind