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
// FILENAME: perspective.cc
// LAST MODIFY: 2020/11/1

#include "perspective.h"

#include <iostream>

#include "resources/program_resource.h"

namespace ngind {
Perspective* Perspective::_instance = nullptr;

Perspective::Perspective() : _width(0), _height(0) {
}

Perspective* Perspective::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Perspective();

        if (_instance == nullptr) {
            // TODO: throw
        }
    }

    return _instance;
}

void Perspective::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void Perspective::init(const Vector2D& center, const size_t& width, const size_t& height) {
    glViewport(center.getX() - width / 2, center.getY() - height / 2,
               width, height);
    _projection = glm::ortho(0.0f, static_cast<float>(width),
                                      static_cast<float>(height), 0.0f,
                                      -1.0f, 1.0f); //TODO:

    _width = width; _height = height;
}
} // namespace ngind