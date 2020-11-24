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
// FILENAME: shader.cc
// LAST MODIFY: 2020/10/31

#include "shader.h"

#include "filesystem/file.h"

namespace ngind {

Shader::Shader(const std::string& filename, const int& type) {
    File* fp = new File(filename, "r");
    std::string code = fp->readToEnd();
    fp->close();

    this->_shader = glCreateShader(type);
    const GLchar* str = code.c_str();

    glShaderSource(this->_shader, 1, &str, nullptr);
    glCompileShader(this->_shader);

    GLint success;
    glGetShaderiv(this->_shader, GL_COMPILE_STATUS, &success);
    if (!success) {

    }
}

Shader::~Shader() {
    glDeleteShader(this->_shader);
}

} // namespace ngind