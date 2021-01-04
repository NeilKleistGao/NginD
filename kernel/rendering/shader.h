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

/// @file shader.h


#ifndef NGIND_SHADER_H
#define NGIND_SHADER_H

#include <string>

#include "GL/glew.h"

namespace ngind::rendering {

/**
 * This class contains a reference of OpenGL rendering shader.
 */
class Shader {
public:
    /**
     * @param filename: shader file's name
     * @param type: type of shader
     */
    Shader(const std::string& filename, const int& type);
    ~Shader();
    Shader(const Shader&) = delete;
    Shader& operator= (const Shader&) = delete;

    /**
     * Get index of shader in OpenGL
     * @return GLuint, index of shader
     */
    inline GLuint getShader() const {
        return _shader;
    }
private:
    /**
     * Index of shader
     */
    GLuint _shader;
};

} // namespace ngind::rendering

#endif //NGIND_SHADER_H
