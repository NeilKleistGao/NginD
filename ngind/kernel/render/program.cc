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

/// @file program.cc
/// @date 2020/10/31

/// @brief This file includes the implementations of program.

#include "program.h"

#include "resources/resources_manager.h"

namespace ngind {

Program::Program(const std::string& program_name) {
    auto* vertex = ResourcesManager::getInstance()->load<ShaderResource>(program_name + ".vs");
    auto* fragment = ResourcesManager::getInstance()->load<ShaderResource>(program_name + ".fs");

    this->_program = glCreateProgram();
    glAttachShader(this->_program, vertex->getShader());
    glAttachShader(this->_program, fragment->getShader());
    glLinkProgram(this->_program);

    GLint success;
    glGetProgramiv(this->_program, GL_LINK_STATUS, &success);
    if (!success) {
        /// @todo error process
    }

    ResourcesManager::getInstance()->release(vertex->getResourcePath());
    ResourcesManager::getInstance()->release(fragment->getResourcePath());
}

Program::~Program() {
    glDeleteProgram(this->_program);
}

} // namespace ngind