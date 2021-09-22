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

/// @file texture_resource.cc

#include "texture_resource.h"

#include "log/logger_factory.h"

namespace ngind::resources {
const std::string TextureResource::IMAGE_RESOURCE_PATH = "resources/images";

void TextureResource::load(const std::string& filename) {
    if (this->_texture != nullptr) {
        delete this->_texture;
        this->_texture = nullptr;
    }

    this->_path = filename;

    auto pos = filename.find_last_of('.');
    std::string ext = filename.substr(pos + 1);

    if (ext == "png") {
        _texture = new rendering::Texture(IMAGE_RESOURCE_PATH + "/" + filename, rendering::TextureColorMode::MODE_RGBA);
    }
    else if (ext == "jpg") {
        _texture = new rendering::Texture(IMAGE_RESOURCE_PATH + "/" + filename, rendering::TextureColorMode::MODE_RGB);
    }
    else {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Unsupported texture format.");
        logger->flush();
    }
}
} // namespace ngind::resources