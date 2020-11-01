// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: program.h
// LAST MODIFY: 2020/11/1

#ifndef NGIND_PROGRAM_H
#define NGIND_PROGRAM_H

#include <string>

#include "resources/shader_resource.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace ngind {

class Program {
public:
    explicit Program(const std::string&);
    ~Program();
    Program(const Program&) = delete;
    Program& operator= (const Program&) = delete;

    inline void use() const {
        glUseProgram(this->_program);
    }

    inline void setVector4(const std::string& name, const glm::vec4& v) {
        glUniform4f(glGetUniformLocation(this->_program, name.c_str()), v.x, v.y, v.z, v.w);
    }

    inline void setMatrix4(const std::string& name, const glm::mat4& m) {
        glUniformMatrix4fv(glGetUniformLocation(this->_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    }

    inline void setInteger(const std::string& name, const int& i) {
        glUniform1i(glGetUniformLocation(this->_program, name.c_str()), i);
    }
private:
    GLuint _program;
};

} // namespace ngind

#endif //NGIND_PROGRAM_H
