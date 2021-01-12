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

#ifndef NGIND_QUAD_H
#define NGIND_QUAD_H

#include "GL/glew.h"

#include <initializer_list>
#include <cstdio>

#include "rendering/rgba.h"
#include "glm/glm.hpp"

namespace ngind::rendering {

class Renderer;

/**
 * The quad data to be rendered.
 */
class Quad {
public:
    /**
     * @param vs: the data of vertices
     * @param color_size: the number of color channel
     */
    explicit Quad(std::initializer_list<GLfloat> vs);
    explicit Quad(const size_t& size);

    ~Quad();

    Quad(const Quad&) = delete;
    Quad& operator= (const Quad&) = delete;

    /**
     * Get the vertices array object index
     * @return GLuint, the index of vao
     */
    inline GLuint getVAO() const {
        return _vao;
    }

    inline GLuint getVBO() const {
        return _vbo;
    }
private:
    /**
     * The vertices array object
     */
    GLuint _vao;

    /**
     * The vertices buffer object
     */
    GLuint _vbo;

    GLuint _ebo;

    GLfloat* _vertex;

    size_t _size;
};

} // namespace ngind::rendering

#endif //NGIND_QUAD_H
