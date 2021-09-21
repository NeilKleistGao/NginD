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
#include "resources/config_resource.h"
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
    explicit Program(const std::string& program_name);

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
     * Get Uniform variable's index by given name
     * @param name: the given name
     * @return GLint, the uniform variable's index
     */
    GLint getUniform(const std::string& name) const;

    /**
     * Set float uniform variable
     * @param name: variable's name
     * @param f: the given value
     */
    inline void setFloat(const std::string& name, const float& f) const {
        glUniform1f(getUniform(name), f);
    }

    /**
     * Set 2 float properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     */
    inline void setFloat2(const std::string& name, const float& x, const float& y) const {
        glUniform2f(getUniform(name), x, y);
    }

    /**
     * Set 3 float properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     * @param z: the third property
     */
    inline void setFloat3(const std::string& name, const float& x, const float& y, const float& z) const {
        glUniform3f(getUniform(name), x, y, z);
    }

    /**
     * Set 4 float properties in this program
     * @param name: name of property
     * @param r: the first property
     * @param g: the second property
     * @param b: the third property
     * @param a: the fourth property
     */
    inline void setFloat4(const std::string& name, const float& r, const float& g, const float& b, const float& a) const {
        glUniform4f(getUniform(name), r, g, b, a);
    }

    /**
     * Set integer uniform property in this program
     * @param name: name of property
     * @param i: integer data
     */
    inline void setInteger(const std::string& name, const int& i) const {
        glUniform1i(getUniform(name), i);
    }

    /**
     * Set 2 integer uniform properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     */
    inline void setInteger2(const std::string& name, const int& x, const int& y) const {
        glUniform2i(getUniform(name), x, y);
    }

    /**
     * Set 3 integer uniform properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     * @param z: the third property
     */
    inline void setInteger3(const std::string& name, const int& x, const int& y, const int& z) const {
        glUniform3i(getUniform(name), x, y, z);
    }

    /**
     * Set 4 integer uniform properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     * @param z: the third property
     * @param w: the forth property
     */
    inline void setInteger4(const std::string& name, const int& x, const int& y, const int& z, const int& w) const {
        glUniform4i(getUniform(name), x, y, z, w);
    }

    /**
     * Set unsigned integer uniform property in this program
     * @param name: name of property
     * @param i: integer data
     */
    inline void setUnsigned(const std::string& name, const unsigned& i) const {
        glUniform1ui(getUniform(name), i);
    }

    /**
     * Set 2 unsigned integer uniform properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     */
    inline void setUnsigned2(const std::string& name, const unsigned& x, const unsigned& y) const {
        glUniform2ui(getUniform(name), x, y);
    }

    /**
     * Set 3 unsigned integer uniform properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     * @param z: the third property
     */
    inline void setUnsigned3(const std::string& name, const unsigned& x, const unsigned& y, const unsigned& z) const {
        glUniform3ui(getUniform(name), x, y, z);
    }

    /**
     * Set 4 unsigned integer uniform properties in this program
     * @param name: name of property
     * @param x: the first property
     * @param y: the second property
     * @param z: the third property
     * @param w: the forth property
     */
    inline void setUnsigned4(const std::string& name, const unsigned& x, const unsigned& y, const unsigned& z, const unsigned& w) const {
        glUniform4ui(getUniform(name), x, y, z, w);
    }

    /**
     * Set 2x2 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix2(const std::string& name, const glm::mat2& m) const {
        glUniformMatrix2fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 3x3 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix3(const std::string& name, const glm::mat3& m) const {
        glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 4x4 matrix uniform property in this program
     * @param name: name of property
     * @param m: matrix4 data
     */
    inline void setMatrix4(const std::string& name, const glm::mat4& m) const {
        glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 2x3 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix2x3(const std::string& name, const glm::mat2x3 & m) const {
        glUniformMatrix2x3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 3x2 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix3x2(const std::string& name, const glm::mat3x2 & m) const {
        glUniformMatrix3x2fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 2x4 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix2x4(const std::string& name, const glm::mat2x4 & m) const {
        glUniformMatrix2x4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 4x2 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix4x2(const std::string& name, const glm::mat4x2 & m) const {
        glUniformMatrix4x2fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 3x4 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix3x4(const std::string& name, const glm::mat3x4 & m) const {
        glUniformMatrix3x4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Set 4x3 matrix uniform property
     * @param name: name of property
     * @param m: the matrix
     */
    inline void setMatrix4x3(const std::string& name, const glm::mat4x3 & m) const {
        glUniformMatrix4x3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(m));
    }

    /**
     * Prepare uniform variables.
     */
    void prepare();

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

    /**
     * Program configuration
     */
    resources::ConfigResource* _program_config;
};

} // namespace ngind::rendering

#endif //NGIND_PROGRAM_H
