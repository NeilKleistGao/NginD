/** MIT License
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

/// @file aseprite_tag.cc

#include "aseprite_tag.h"

#include "log/logger_factory.h"

namespace ngind::animation {

AsepriteTag::AsepriteTag(const typename resources::ConfigResource::JsonObject& data) : _direction(), _from(), _to(), _name() {
    try {
        _name = data["name"].GetString();
        _from = data["from"].GetInt();
        _to = data["to"].GetInt() + 1;

        std::string direction = data["direction"].GetString();
        if (direction == "forward") {
            _direction = AnimationDirection::DIRECTION_FORWARD;
        }
        else if (direction == "reverse") {
            _direction = AnimationDirection::DIRECTION_REVERSE;
        }
        else if (direction == "ping-pong") {
            _direction = AnimationDirection::DIRECTION_PING_PONG;
        }
        else {
            auto logger = log::LoggerFactory::getInstance()->getLogger("warning.log", log::LogLevel::LOG_LEVEL_WARNING);
            logger->log(direction + " is not a supported animation direction.");
            logger->close();
        }
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("An error occurred when parsing aseprite tag");
        logger->close();

        throw std::exception{};
    }
}

} // namespace ngind::animation