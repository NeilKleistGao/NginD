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

/// @file quad.h

#include "quad.h"
#include "log/logger_factory.h"

namespace ngind::rendering {

Quad::Quad(std::initializer_list<GLfloat> vs,
           const bool& dynamic) : _dynamic(dynamic) {
    _size = vs.size();
    if (_size == 0) {
        auto log = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LOG_LEVEL_ERROR);
        log->log("zero size of vertex data when creating quad.");
        exit(-1);
    }

    _vertex = new GLfloat[_size];
    auto it = vs.begin();
    for (int i = 0; i < _size; i++, it++) {
        _vertex[i] = *it;
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    if (!dynamic) {
        glGenBuffers(1, &_ebo);
        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _size, _vertex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        constexpr GLuint indices[] = {
                0, 1, 3,
                1, 2, 3
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        delete[] _vertex;
        _vertex = nullptr;
    }
    else {
        _ebo = 0;
        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _size, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
}

Quad::~Quad() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);

    if (_dynamic) {
        delete[] _vertex;
        _vertex = nullptr;
    }
    else {
        glDeleteBuffers(1, &_ebo);
    }
}

void Quad::bindSubData() {
    if (!_dynamic) {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * _size, _vertex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace ngind::rendering