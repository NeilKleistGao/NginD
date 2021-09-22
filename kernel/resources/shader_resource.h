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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file shader_resource.h

#ifndef NGIND_SHADER_RESOURCE_H
#define NGIND_SHADER_RESOURCE_H

#include "resource.h"
#include "rendering/shader.h"

namespace ngind::resources {

/**
 * Resource class containing shader data.
 */
class ShaderResource : public Resource {
public:
    /**
     * Path all shader files stored
     */
    const static std::string SHADER_RESOURCE_PATH;

    ShaderResource() : Resource(), _shader(nullptr) {};
    ~ShaderResource() override;

    /**
     * @see kernel/resources/resource.h
     */
    void load(const std::string&) override;

    /**
     * Get shader object.
     * @return rendering::Shader*, shader object
     */
    inline rendering::Shader* operator-> () {
        return _shader;
    }
private:
    /**
     * The shader object
     */
    rendering::Shader* _shader;
};

} // namespace ngind::resources

#endif //NGIND_SHADER_RESOURCE_H
