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
// FILENAME: texture.h
// LAST MODIFY: 2020/11/1

#ifndef NGIND_TEXTURE_H
#define NGIND_TEXTURE_H

#include <string>

#include "GL/glew.h"
#include "math/vector.h"

namespace ngind {

enum TextureColorMode {
    MODE_RGB = GL_RGB,
    MODE_RGBA = GL_RGBA
};

class Texture {
public:
    Texture(const std::string&, const TextureColorMode& mod);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator= (const Texture&) = delete;

    inline GLuint getTextureID() const {
        return _texture_id;
    }

    inline float getWidth() const {
        return _size.getX();
    }

    inline float getHeight() const {
        return _size.getY();
    }

    inline Vector2D getSize() const {
        return _size;
    }

    inline TextureColorMode getColorMode() const {
        return _mode;
    }

private:
    GLuint _texture_id;
    Vector2D _size;
    TextureColorMode _mode;
};

} // namespace

#endif //NGIND_TEXTURE_H
