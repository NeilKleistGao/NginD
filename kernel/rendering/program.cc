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

/// @file program.cc

#include "program.h"

#include "resources/resources_manager.h"

namespace ngind::rendering {

Program::Program(const std::string& program_name) {
    _vs = resources::ResourcesManager::getInstance()->load<resources::ShaderResource>(program_name + ".vs");
    _fs = resources::ResourcesManager::getInstance()->load<resources::ShaderResource>(program_name + ".frag");

    this->_program = glCreateProgram();
    glAttachShader(this->_program, _vs->getShader());
    glAttachShader(this->_program, _fs->getShader());
    glLinkProgram(this->_program);

    GLint success;
    glGetProgramiv(this->_program, GL_LINK_STATUS, &success);
    if (!success) {
        /// @todo error process
    }
}

Program::~Program() {
    glDeleteProgram(this->_program);
}

GLint Program::getUniform(const std::string& name) const {
    auto res = glGetUniformLocation(this->_program, name.c_str());
    if (res == -1) {
        // TODO:
    }

    return res;
}

} // namespace ngind::rendering