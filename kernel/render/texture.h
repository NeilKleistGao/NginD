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

/// @file texture.h
/// @date 2020/11/1

#ifndef NGIND_TEXTURE_H
#define NGIND_TEXTURE_H

#include <string>

#include "GL/glew.h"
#include "math/vector.h"

namespace ngind {

using Vector2D = math::Vector2D;

/**
@enum
    The color mode in textures. It's a mapping from GL macro to the enum form.
*/
enum TextureColorMode {
    MODE_RGB = GL_RGB,
    MODE_RGBA = GL_RGBA
};

/**
@class
    Texture container used for rendering. It only supports JPEG and PNG formats now.
*/
class Texture {
public:
    /// @public
    /// @param const std::string&: picture path
    /// @param const TextureColorMode&: color mode of picture
    Texture(const std::string&, const TextureColorMode&);

    /// @public
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator= (const Texture&) = delete;

    /// @public
    /// @fn Get the id of texture
    /// @param void
    /// @return GLuint, id of texture
    inline GLuint getTextureID() const {
        return _texture_id;
    }

    /// @public
    /// @fn Get the width of texture
    /// @param void
    /// @return float, width of texture
    inline float getWidth() const {
        return _size.getX();
    }

    /// @public
    /// @fn Get the height of texture
    /// @param void
    /// @return float, height of texture
    inline float getHeight() const {
        return _size.getY();
    }

    /// @public
    /// @fn Get the size of texture
    /// @param void
    /// @return Vector2D, size of texture
    inline Vector2D getSize() const {
        return _size;
    }

    /// @public
    /// @fn Get color mode of texture
    /// @param void
    /// @return TextureColorMode, color mode of texture
    inline TextureColorMode getColorMode() const {
        return _mode;
    }

private:
    /// @private
    /// @property texture id
    GLuint _texture_id;

    /// @private
    /// @property size of texure
    Vector2D _size;

    /// @private
    /// @property color mode of texture
    TextureColorMode _mode;
};

} // namespace ngind

#endif //NGIND_TEXTURE_H
