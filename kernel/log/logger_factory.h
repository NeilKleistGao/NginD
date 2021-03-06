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

/// @file logger_factory.h

#ifndef NGIND_LOGGER_FACTORY_H
#define NGIND_LOGGER_FACTORY_H

#include <map>
#include <string>

#include "logger.h"

namespace ngind::log {
/**
 * This class is defined to create and manage logger instances.
 */
class LoggerFactory {
public:
    /**
     * Get the single instance of logger factory
     * @return LoggerFactory*, the instance of logger factory
     */
    static LoggerFactory* getInstance();

    /**
     * Destroy the instance of logger factory
     */
    static void destroyInstance();

    /**
     * Get logger instance by filename the logger uses and specify the level
     * @param filename: the filename
     * @param level: the level of logger
     * @return Logger*, the logger object
     */
    Logger* getLogger(const std::string& filename, const LogLevel& level);
private:
    LoggerFactory() = default;

    ~LoggerFactory();

    /**
     * The instance of logger factory.
     */
    static LoggerFactory* _instance;

    /**
     * The map from filename to logger instances.
     */
    std::map<std::string, Logger*> _loggers;
};
} // namespace ngind::log

#endif //NGIND_LOGGER_FACTORY_H
