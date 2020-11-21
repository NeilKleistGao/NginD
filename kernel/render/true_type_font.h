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

/// @file true_type_font.h
/// @date 2020/10/19

#ifndef NGIND_TRUE_TYPE_FONT_H
#define NGIND_TRUE_TYPE_FONT_H

#include <string>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

namespace ngind {

/**
@class True type font(TTF) data. It's still being developed.
*/
class TrueTypeFont {
public:
    /// @public
    TrueTypeFont();

    /// @public
    ~TrueTypeFont();

    /// @public
    /// @fn Set font face
    /// @param FT_Face face: font face
    /// @return void
    inline void setFontFace(FT_Face face) {
        _font_face = face;
    }
private:
    /// @private
    /// @property Font face data
    FT_Face _font_face;
};

} // namespace ngind

#endif //NGIND_TRUE_TYPE_FONT_H
