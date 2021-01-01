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

#include "render/texture.h"
#include "resource.h"
#include "math/vector.h"

namespace ngind {

class TextureResource : public Resource {
public:
    const static std::string IMAGE_RESOURCE_PATH;

    TextureResource() = default;
    ~TextureResource() override = default;
    virtual void load(const std::string&);

    inline GLuint getTextureID() const {
        return _texture->getTextureID();
    }

    inline Vector2D getTextureSize() const {
        return _texture->getSize();
    }

    inline float getTextureWidth() const {
        return _texture->getWidth();
    }

    inline float getTextureHeight() const {
        return _texture->getHeight();
    }

    inline TextureColorMode getTextureColorMode() const {
        return _texture->getColorMode();
    }

private:
    Texture* _texture;
};

}

#endif //NGIND_TEXTURE_RESOURCE_H
