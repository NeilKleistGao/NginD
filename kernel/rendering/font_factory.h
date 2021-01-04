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
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file font_factory.h

#ifndef NGIND_FONT_FACTORY_H
#define NGIND_FONT_FACTORY_H

#include <string>

#include "freetype2/ft2build.h"
#include FT_FREETYPE_H

namespace ngind::rendering {

/**
 * This class is defined for font face data creating.
 */
class FontFactory {
public:
    /**
     * Get instance of factory
     * @return FontFactory*, the instance of factory
     */
    static FontFactory* getInstance();

    /**
     * Destroy instance of factory
     */
    static void destroyInstance();

    /**
     * Load font face data from file
     * @param filename: filename of font
     * @param index: face index
     * @return FT_Face, face data of font
     */
    FT_Face loadFontFace(const std::string& filename, const long& index);
private:
    FontFactory();
    ~FontFactory() = default;

    /**
     * The instance of font factory
     */
    static FontFactory* _instance;

    /**
     * The font library
     */
    FT_Library _library;
};

} // namespace ngind::rendering

#endif //NGIND_FONT_FACTORY_H
