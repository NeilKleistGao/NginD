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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file font_resource.h

#include "font_resource.h"

#include "rendering/font_factory.h"
#include "log/logger_factory.h"

namespace ngind::resources {
const std::string FontResource::FONT_RESOURCE_PATH = "resources/fonts";

FontResource::FontResource() : Resource(), _font(new(std::nothrow) rendering::TrueTypeFont()) {
}

FontResource::~FontResource() {
    delete _font;
    _font = nullptr;
}

void FontResource::load(const std::string& filename) {
    if (_font != nullptr) {
        this->_path = filename;
        auto face = rendering::FontFactory::getInstance()->loadFontFace(FONT_RESOURCE_PATH + "/" + filename, 0);
        _font->setFontFace(face);
    }
    else {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't load font " + filename + ".");
        logger->flush();
    }
}

} // namespace ngind::resources