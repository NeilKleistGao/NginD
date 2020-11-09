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
// FILENAME: shader_resource.h
// LAST MODIFY: 2020/10/31

#include "shader_resource.h"

namespace ngind {

const std::string ShaderResource::SHADER_RESOURCE_PATH = "resources/shaders";

ShaderResource::~ShaderResource() {
    if (_shader != nullptr) {
        delete _shader;
        _shader = nullptr;
    }
}

void ShaderResource::load(const std::string& filename) {
    if (_shader != nullptr) {
        delete _shader;
        _shader = nullptr;
    }

    this->_path = filename;
    int pos = filename.find_last_of('.');
    if (filename.substr(pos + 1) == "vs") {
        _shader = new Shader(SHADER_RESOURCE_PATH + "/" + filename, GL_VERTEX_SHADER);
    }
    else {
        _shader = new Shader(SHADER_RESOURCE_PATH + "/" + filename, GL_FRAGMENT_SHADER);
    }
}

} // namespace