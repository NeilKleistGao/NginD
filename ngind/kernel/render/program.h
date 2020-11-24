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

/// @file program.h
/// @date 2020/11/1

/// @brief This file defines the render program data.

#ifndef NGIND_PROGRAM_H
#define NGIND_PROGRAM_H

#include <string>

#include "resources/shader_resource.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace ngind {

/**
@class
    This class contains a reference of OpenGL render program that
linked to two shaders. One is for vertex and the other is for fragment.
*/
class Program {
public:
    /// @public
    /// @param const std::string&: program's name
    explicit Program(const std::string&);

    /// @public
    ~Program();

    Program(const Program&) = delete;
    Program& operator= (const Program&) = delete;

    /// @public
    /// @fn Use current render program
    /// @param void
    /// @return void
    inline void use() const {
        glUseProgram(this->_program);
    }

    /// @public
    /// @fn Set vector4 uniform property in this program
    /// @param const std::string& name: name of property
    /// @param const glm::vec4& v: vector4 data
    /// @return void
    inline void setVector4(const std::string& name, const glm::vec4& v) {
        glUniform4f(glGetUniformLocation(this->_program, name.c_str()), v.x, v.y, v.z, v.w);
    }

    /// @public
    /// @fn Set matrix4 uniform property in this program
    /// @param const std::string& name: name of property
    /// @param const glm::mat4& m: matrix4 data
    /// @return void
    inline void setMatrix4(const std::string& name, const glm::mat4& m) {
        glUniformMatrix4fv(glGetUniformLocation(this->_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    }

    /// @public
    /// @fn Set integer uniform property in this program
    /// @param const std::string& name: name of property
    /// @param const int& i: integer data
    /// @return void
    inline void setInteger(const std::string& name, const int& i) {
        glUniform1i(glGetUniformLocation(this->_program, name.c_str()), i);
    }
private:
    /// @private
    /// @property The index of program
    GLuint _program;
};

} // namespace ngind

#endif //NGIND_PROGRAM_H
