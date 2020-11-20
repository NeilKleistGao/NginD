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

/// @file quad.h
/// @date 2020/11/1

/// @brief This file includes the definition of quad data.

#ifndef NGIND_QUAD_H
#define NGIND_QUAD_H

#include "GL/glew.h"

#include <initializer_list>
#include <cstdio>

namespace ngind {

/**
@class The quad data to be rendered.
*/
class Quad {
public:
    /// @public
    /// @param std::initializer_list<GLfloat>: the data of vertices
    /// @param const size_t&: the number of color channel
    Quad(std::initializer_list<GLfloat>, const size_t&);

    /// @public
    ~Quad();

    Quad(const Quad&) = delete;
    Quad& operator= (const Quad&) = delete;

    /// @public
    /// @fn Get the vertices array object index
    /// @param void
    /// @return GLuint, the index of vao
    inline GLuint getVAO() const {
        return _vao;
    }

private:
    /// @private
    /// @property The vertices array object
    GLuint _vao;

    /// @private
    /// @property The vertices buffer object
    GLuint _vbo;

    /// @private
    /// @property The elements buffer object
    GLuint _ebo;
};

} // namespace ngind

#endif //NGIND_QUAD_H
