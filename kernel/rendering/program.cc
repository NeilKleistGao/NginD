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

    _vs = manager->load<resources::ShaderResource>(std::string{(*_program_config)["vertex"].GetString()} + ".vs");
    _fs = manager->load<resources::ShaderResource>(std::string{(*_program_config)["fragment"].GetString()} + ".frag");

    this->_program = glCreateProgram();
    glAttachShader(this->_program, (*_vs)->getShader());
    glAttachShader(this->_program, (*_fs)->getShader());
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
    auto args = (*_program_config)["args"].GetArray();
    for (const auto& arg : args) {
        std::string name = arg["name"].GetString();
        std::string type = arg["type"].GetString();

        if (type == "float") {
            this->setFloat(name, arg["value"].GetFloat());
        }
        else if (type == "float2") {
            auto value = arg["value"].GetArray();
            this->setFloat2(name, value[0].GetFloat(), value[1].GetFloat());
        }
        else if (type == "float3") {
            auto value = arg["value"].GetArray();
            this->setFloat3(name, value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat());
        }
        else if (type == "float4") {
            auto value = arg["value"].GetArray();
            this->setFloat4(name, value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat());
        }
        else if (type == "int") {
            this->setInteger(name, arg["value"].GetInt());
        }
        else if (type == "int2") {
            auto value = arg["value"].GetArray();
            this->setFloat2(name, value[0].GetInt(), value[1].GetInt());
        }
        else if (type == "int3") {
            auto value = arg["value"].GetArray();
            this->setFloat3(name, value[0].GetInt(), value[1].GetInt(), value[2].GetInt());
        }
        else if (type == "int4") {
            auto value = arg["value"].GetArray();
            this->setFloat4(name, value[0].GetInt(), value[1].GetInt(), value[2].GetInt(), value[3].GetInt());
        }
        else if (type == "unsigned") {
            this->setUnsigned(name, arg["value"].GetUint());
        }
        else if (type == "unsigned2") {
            auto value = arg["value"].GetArray();
            this->setUnsigned2(name, value[0].GetUint(), value[1].GetUint());
        }
        else if (type == "unsigned3") {
            auto value = arg["value"].GetArray();
            this->setUnsigned3(name, value[0].GetUint(), value[1].GetUint(), value[2].GetUint());
        }
        else if (type == "unsigned4") {
            auto value = arg["value"].GetArray();
            this->setUnsigned4(name, value[0].GetUint(), value[1].GetUint(), value[2].GetUint(), value[3].GetUint());
        }
        else if (type == "matrix2") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat2{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat()};
            this->setMatrix2(name, mat);
        }
        else if (type == "matrix3") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat3{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(),
                                 value[3].GetFloat(), value[4].GetFloat(), value[5].GetFloat(),
                                 value[6].GetFloat(), value[7].GetFloat(), value[8].GetFloat()};
            this->setMatrix3(name, mat);
        }
        else if (type == "matrix4") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat4{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat(),
                                 value[4].GetFloat(), value[5].GetFloat(),value[6].GetFloat(), value[7].GetFloat(),
                                 value[8].GetFloat(), value[9].GetFloat(), value[10].GetFloat(), value[11].GetFloat(),
                                 value[12].GetFloat(), value[13].GetFloat(), value[14].GetFloat(), value[15].GetFloat()};
            this->setMatrix4(name, mat);
        }
        else if (type == "matrix23") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat2x3{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(),
                                   value[3].GetFloat(), value[4].GetFloat(), value[5].GetFloat()};
            this->setMatrix2x3(name, mat);
        }
        else if (type == "matrix24") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat2x4{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat(),
                                   value[4].GetFloat(), value[5].GetFloat(), value[6].GetFloat(), value[7].GetFloat()};
            this->setMatrix2x4(name, mat);
        }
        else if (type == "matrix32") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat3x2{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(),
                                   value[3].GetFloat(), value[4].GetFloat(), value[5].GetFloat()};
            this->setMatrix3x2(name, mat);
        }
        else if (type == "matrix34") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat3x4{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat(),
                                   value[4].GetFloat(), value[5].GetFloat(), value[6].GetFloat(), value[7].GetFloat(),
                                   value[8].GetFloat(), value[9].GetFloat(), value[10].GetFloat(), value[11].GetFloat()};
            this->setMatrix3x4(name, mat);
        }
        else if (type == "matrix42") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat4x2{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat(),
                                   value[4].GetFloat(), value[5].GetFloat(), value[6].GetFloat(), value[7].GetFloat()};
            this->setMatrix4x2(name, mat);
        }
        else if (type == "matrix43") {
            auto value = arg["value"].GetArray();
            auto mat = glm::mat4x3{value[0].GetFloat(), value[1].GetFloat(), value[2].GetFloat(), value[3].GetFloat(),
                                   value[4].GetFloat(), value[5].GetFloat(), value[6].GetFloat(), value[7].GetFloat(),
                                   value[8].GetFloat(), value[9].GetFloat(), value[10].GetFloat(), value[11].GetFloat()};
            this->setMatrix4x3(name, mat);
        }
    }
}

} // namespace ngind::rendering