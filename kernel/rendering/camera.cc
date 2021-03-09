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

/// @file camera.cc

#include "camera.h"

#include <iostream>

#include "SOIL2/SOIL2.h"

namespace ngind::rendering {
Camera* Camera::_instance = nullptr;

Camera::Camera() : _width(0), _height(0), _projection() {
}

Camera* Camera::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Camera();

        if (_instance == nullptr) {
            // TODO: throw
        }
    }

    return _instance;
}

void Camera::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void Camera::init(const glm::vec2& center, const size_t& width, const size_t& height) {
    glViewport(center.x - width / 2, center.y - height / 2,
               width, height);
    _projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height), -1.0f, 1.0f);

    _width = width; _height = height;
    _center = center;
}

void Camera::capture(const std::string& filename) const {
    glReadBuffer(GL_FRONT);

    glPixelStorei(GL_PACK_ALIGNMENT,1);
    auto buffer = new unsigned char[_width * _height * sizeof(unsigned char) * 4];
    glReadPixels(0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height / 2; j++) {
            std::swap(buffer[(j * _width + i) * 4], buffer[((_height - j - 1) * _width + i) * 4]);
            std::swap(buffer[(j * _width + i) * 4 + 1], buffer[((_height - j - 1) * _width + i) * 4 + 1]);
            std::swap(buffer[(j * _width + i) * 4 + 2], buffer[((_height - j - 1) * _width + i) * 4 + 2]);
            std::swap(buffer[(j * _width + i) * 4 + 3], buffer[((_height - j - 1) * _width + i) * 4 + 3]);
        }
    }

    SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_PNG, _width, _height, SOIL_LOAD_RGBA, buffer);

    delete[] buffer;
    buffer = nullptr;
}

} // namespace ngind::rendering