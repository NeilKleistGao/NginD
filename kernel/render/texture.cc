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

/// @file texture.cc
/// @date 2020/11/1

#include "texture.h"

#include <cassert>

#include "SOIL2/SOIL2.h"

namespace ngind {

Texture::Texture(const std::string& filename, const TextureColorMode& mode) {
    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* img = nullptr;
    if (mode == TextureColorMode::MODE_RGB) {
        img = SOIL_load_image(filename.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                     height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (mode == TextureColorMode::MODE_RGBA) {
        img = SOIL_load_image(filename.c_str(), &width, &height, nullptr, SOIL_LOAD_RGBA);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    _size = Vector2D{width, height};
    SOIL_free_image_data(img);
    _mode = mode;

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &_texture_id);
}

} // namespace