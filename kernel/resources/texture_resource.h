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

/// @file texture_resource.h

#ifndef NGIND_TEXTURE_RESOURCE_H
#define NGIND_TEXTURE_RESOURCE_H

#include <iostream>

#include "rendering/texture.h"
#include "resource.h"
#include "glm/glm.hpp"

namespace ngind::resources {

/**
 * Resource class containing texture data.
 */
class TextureResource : public Resource {
public:
    const static std::string IMAGE_RESOURCE_PATH;

    TextureResource() : Resource(), _texture(nullptr) {};
    ~TextureResource() override = default;

    /**
     * @see kernel/resources/resource.h
     */
    void load(const std::string&) override;

    /**
     * Get texture object.
     * @return rendering::Texture*, texture object
     */
    inline rendering::Texture* operator-> () {
        return _texture;
    }

private:
    /**
     * Texture pointer.
     */
    rendering::Texture* _texture;
};

} // namespace ngind::resources

#endif //NGIND_TEXTURE_RESOURCE_H
