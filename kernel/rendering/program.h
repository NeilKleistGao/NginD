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

/// @file program.h

#ifndef NGIND_PROGRAM_H
#define NGIND_PROGRAM_H

#include <string>

#include "resources/shader_resource.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace ngind::rendering {

/**
 * This class contains a reference of OpenGL rendering program that
 * linked to two shaders. One is for vertex and the other is for fragment.
 */
class Program {
public:
    /**
     * @param name: program's name
     */
    explicit Program(const std::string& name);

    ~Program();

    Program(const Program&) = delete;
    Program& operator= (const Program&) = delete;

    /**
     * Use current rendering program
     */
    inline void use() const {
        glUseProgram(this->_program);
    }

    /**
     * Set vector4 uniform property in this program
     * @param name: name of property
     * @param v: vector4 data
     */
    inline void setVector4(const std::string& name, const glm::vec4& v) {
        glUniform4f(glGetUniformLocation(this->_program, name.c_str()), v.x, v.y, v.z, v.w);
    }

    /**
     * Set matrix4 uniform property in this program
     * @param name: name of property
     * @param m: matrix4 data
     */
    inline void setMatrix4(const std::string& name, const glm::mat4& m) {
        glUniformMatrix4fv(glGetUniformLocation(this->_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set integer uniform property in this program
     * @param name: name of property
     * @param i: integer data
     */
    inline void setInteger(const std::string& name, const int& i) {
        glUniform1i(glGetUniformLocation(this->_program, name.c_str()), i);
    }

    /**
     * Set 3 float properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     * @param z: the third property
     */
    inline void setFloat3(const std::string& name, const float& x, const float& y, const float& z) {
        glUniform3f(glGetUniformLocation(this->_program, name.c_str()), x, y, z);
    }

    /**
     * Set 4 float properties in this program
     * @param name: name of property
     * @param r: the first property
     * @param g: the second property
     * @param b: the third property
     * @param a: the fourth property
     */
    inline void setFloat4(const std::string& name, const float& r, const float& g, const float& b, const float& a) {
        glUniform4f(glGetUniformLocation(this->_program, name.c_str()), r, g, b, a);
    }
private:
    /**
     * The index of program
     */
    GLuint _program;

    /**
     * Reference of vertex shader
     */
    resources::ShaderResource* _vs;

    /**
     * Reference of segment shader
     */
    resources::ShaderResource* _fs;
};

} // namespace ngind::rendering

#endif //NGIND_PROGRAM_H
