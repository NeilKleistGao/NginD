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

/// @file true_type_font.h

#ifndef NGIND_TRUE_TYPE_FONT_H
#define NGIND_TRUE_TYPE_FONT_H

#include <string>
#include <unordered_map>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "character.h"

namespace ngind::rendering {

/**
 * True type font(TTF) data.
 */
class TrueTypeFont {
public:
    constexpr static size_t DEFAULT_FONT_SIZE = 48;

    TrueTypeFont();

    ~TrueTypeFont();

    /**
     * Set font face
     * @param face: font face
     */
    inline void setFontFace(FT_Face face) {
        _font_face = face;
    }

    /**
     * Generate Character bitmap if it does not exist
     * @param c: the given character
     * @return Character, the bitmap and data of character
     */
    Character generateCharacterData(const char& c);

    /**
     * Generate UTF8 Character bitmap if it does not exist
     * @param c: the given character
     * @return Character, the bitmap and data of character
     */
    Character generateCharacterData(const wchar_t& c);

    /**
     * Get the max height of all characters.
     * @return size_t, the max height
     */
    inline size_t getMaxHeight() const {
        return _max_height;
    }
private:
    /**
     * Font face data
     */
    FT_Face _font_face;

    /**
     * ASCII characters cache.
     */
    std::unordered_map<char, Character> _cache;

    /**
     * UTF8 characters cache.
     */
    std::unordered_map<wchar_t, Character> _w_cache;

    /**
     * Max height of all characters.
     */
    size_t _max_height;

    /**
     * Bind character data.
     * @return The available character data.
     */
    Character bind();
};

} // namespace ngind::rendering

#endif //NGIND_TRUE_TYPE_FONT_H
