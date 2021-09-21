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

/// @file texture.cc

#include "texture.h"

#include "SOIL2/SOIL2.h"
#include "filesystem/file_input_stream.h"
#include "filesystem/zip_input_stream.h"
#include "settings.h"
#include "log/logger_factory.h"

namespace ngind::rendering {

Texture::Texture(const std::string& filename, const TextureColorMode& mode) : _texture_id{}, _mode{mode}, _size{} {
    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width = 0, height = 0;
    unsigned char* img = nullptr;
    int channel = 0, gl_color_mode = 0;
    if (mode == TextureColorMode::MODE_RGB) {
        channel = SOIL_LOAD_RGB; gl_color_mode = GL_RGB;
    }
    else if (mode == TextureColorMode::MODE_RGBA) {
        channel = SOIL_LOAD_RGBA; gl_color_mode = GL_RGBA;
    }
    else {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Unsupported image format.");
        logger->flush();
    }

    if constexpr (CURRENT_MODE == MODE_RELEASE) {
        std::string temp = filename;
        int pos = filename.find_last_of('.');
        temp.replace(pos + 1, 1, "c");

        auto fp = new filesystem::ZipInputStream(new filesystem::FileInputStream(temp));
        std::string content = fp->readAllCharacters();
        fp->close();
        img = SOIL_load_image_from_memory(reinterpret_cast<const unsigned char *const>(content.c_str()),
                                          content.length(), &width, &height, nullptr, channel);
    }
    else {
        auto fp = new filesystem::FileInputStream(filename);
        std::string content = fp->readAllCharacters();
        fp->close();
        img = SOIL_load_image_from_memory(reinterpret_cast<const unsigned char *const>(content.c_str()),
                                          content.length(), &width, &height, nullptr, channel);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, gl_color_mode, width,
                 height, 0, gl_color_mode, GL_UNSIGNED_BYTE, img);
    glBindTexture(GL_TEXTURE_2D, 0);

    _size = glm::vec2{width, height};
    SOIL_free_image_data(img);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &_texture_id);
}

} // namespace ngind::rendering