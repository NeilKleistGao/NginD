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

/// @file adaptor.cc

#include "adaptor.h"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "GL/glew.h"
#include "log/logger_factory.h"

namespace ngind::rendering {
Adaptor* Adaptor::_instance = nullptr;

Adaptor* Adaptor::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Adaptor();

        if (_instance == nullptr) {
            auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
            logger->log("Can't create adaptor instance.");
            logger->flush();
        }
    }

    return _instance;
}

void Adaptor::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void Adaptor::update() {
    if (_screen.x < 1 || _screen.y < 1 || _resolution.x <= 0 || _resolution.y <= 0) {
        return;
    }

    float scale_x = _screen.x / _resolution.x,
          scale_y = _screen.y / _resolution.y;

    if (_tactic == ResolutionAdaptionTactic::SHOW_ALL) {
        scale_x = scale_y = std::min(scale_x, scale_y);
    }
    else if (_tactic == ResolutionAdaptionTactic::NO_BORDER) {
        scale_x = scale_y = std::max(scale_x, scale_y);
    }
    else if (_tactic == ResolutionAdaptionTactic::FIXED_WIDTH) {
        scale_y = scale_x;
    }
    else if (_tactic == ResolutionAdaptionTactic::FIXED_HEIGHT) {
        scale_x = scale_y;
    }

    float width = scale_x * _resolution.x,
          height = scale_y * _resolution.y;

    float offset_x = std::abs((_screen.x - width)) / 2.0f, offset_y = std::abs((_screen.y - height) / 2.0f);
    glViewport(offset_x, offset_y, width, height);
}

} // namespace ngind::rendering
