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

/// @file true_type_font.cc

#include "true_type_font.h"

#include <iostream>

namespace ngind::rendering {

TrueTypeFont::TrueTypeFont() : _font_face(nullptr), _cache(), _max_height(0) {
}

TrueTypeFont::~TrueTypeFont() {
    auto error = FT_Done_Face(_font_face);
    if (error) {
        ///@todo
    }

    for (const auto& [_, ch] : _cache) {
        glDeleteTextures(1, &ch.texture);
    }

    _cache.clear();
}

Character TrueTypeFont::generateCharacterData(const char& c) {
    if (_cache.find(c) == _cache.end()) {
        FT_Set_Pixel_Sizes(_font_face, 0, DEFAULT_FONT_SIZE);
        if (FT_Load_Char(_font_face, c, FT_LOAD_RENDER)) {
            ///@todo
        }

        Character character;
        glGenTextures(1, &character.texture);
        glBindTexture(GL_TEXTURE_2D, character.texture);
        character.size = {_font_face->glyph->bitmap.width, _font_face->glyph->bitmap.rows};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     character.size.x, character.size.y,
                     0, GL_RED, GL_UNSIGNED_BYTE,
                     _font_face->glyph->bitmap.buffer);

        _max_height = std::max<unsigned int>(_max_height, _font_face->glyph->bitmap.rows);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        character.bearing = {_font_face->glyph->bitmap_left, _font_face->glyph->bitmap_top};
        character.advance = {_font_face->glyph->advance.x, _font_face->glyph->advance.y};

        _cache[c] = character;

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    return _cache[c];
}

} // namespace ngind::rendering