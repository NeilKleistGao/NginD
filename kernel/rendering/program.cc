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
    auto manager = resources::ResourcesManager::getInstance();
    _program_config = manager->load<resources::ConfigResource>("programs/" + program_name + ".json");

    _vs = manager->load<resources::ShaderResource>(std::string{_program_config->getDocument()["vertex"].GetString()} + ".vs");
    _fs = manager->load<resources::ShaderResource>(std::string{_program_config->getDocument()["fragment"].GetString()} + ".frag");

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

    auto manager = resources::ResourcesManager::getInstance();
    manager->release(_vs);
    manager->release(_fs);
    manager->release(_program_config);
}

GLint Program::getUniform(const std::string& name) const {
    auto res = glGetUniformLocation(this->_program, name.c_str());
    if (res == -1) {
        // TODO:
    }

    return res;
}

void Program::prepare() {
    auto args = _program_config->getDocument()["args"].GetArray();
    for (const auto& arg : args) {
        std::string name = arg["name"].GetString();
        std::string type = arg["type"].GetString();

        if (type == "float") {
            this->setFloat(name, arg["value"].GetFloat());
        }
        else if (type == "float2") {
            // TODO:
        }
        else if (type == "float3") {

        }
        else if (type == "float4") {

        }
        else if (type == "int") {

        }
        else if (type == "int2") {

        }
        else if (type == "int3") {

        }
        else if (type == "int4") {

        }
        else if (type == "int") {

        }
        else if (type == "int2") {

        }
        else if (type == "int3") {

        }
        else if (type == "int4") {

        }
        else if (type == "unsigned") {

        }
        else if (type == "unsigned2") {

        }
        else if (type == "unsigned3") {

        }
        else if (type == "unsigned4") {

        }
        else if (type == "matrix2") {

        }
        else if (type == "matrix3") {

        }
        else if (type == "matrix4") {

        }
        else if (type == "matrix23") {

        }
        else if (type == "matrix24") {

        }
        else if (type == "matrix32") {

        }
        else if (type == "matrix34") {

        }
        else if (type == "matrix42") {

        }
        else if (type == "matrix43") {

        }
    }
}

} // namespace ngind::rendering