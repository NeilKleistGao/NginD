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

    TextureResource() : Resource() {};
    ~TextureResource() override = default;

    /**
     * @see kernel/resources/resource.h
     */
    virtual void load(const std::string&);

    /**
     * Get the id of texture in OpenGL.
     * @return GLuint, id of texture
     */
    inline GLuint getTextureID() const {
        return _texture->getTextureID();
    }

    /**
     * Get the size of texture.
     * @return Vector2D, size of texture
     */
    inline glm::vec2 getTextureSize() const {
        return _texture->getSize();
    }

    /**
     * Get width of texture.
     * @return float, width of texture
     */
    inline float getTextureWidth() const {
        return _texture->getWidth();
    }

    /**
     * Get height of texture.
     * @return float, height of texture
     */
    inline float getTextureHeight() const {
        return _texture->getHeight();
    }

    /**
     * Get color mode of texture.
     * @return TextureColorMode, color mode of texture
     */
    inline rendering::TextureColorMode getTextureColorMode() const {
        return _texture->getColorMode();
    }

private:
    /**
     * Texture pointer.
     */
    rendering::Texture* _texture;
};

}

#endif //NGIND_TEXTURE_RESOURCE_H
