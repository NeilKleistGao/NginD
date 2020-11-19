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

/// @file font_factory.h
/// @date 2020/10/19

/**
@brief This file includes the factory for creating FFT font face data.
*/

#ifndef NGIND_FONT_FACTORY_H
#define NGIND_FONT_FACTORY_H

#include <string>

#include "freetype2/ft2build.h"
#include FT_FREETYPE_H

namespace ngind {

/**
@class This class is defined for font face data creating.
*/
class FontFactory {
public:
    /// @public
    /// @static
    /// @fn Get instance of factory
    /// @param void
    /// @return FontFactory*, the instance of factory
    static FontFactory* getInstance();

    /// @public
    /// @static
    /// @fn Destroy instance of factory
    /// @param void
    /// @return void
    static void destroyInstance();

    /// @public
    /// @fn Load font face data from file
    /// @param const std::string&: filename of font
    /// @param const long&: face index
    /// @return FT_Face, face data of font
    FT_Face loadFontFace(const std::string&, const long&);
private:
    /// @private
    FontFactory();

    /// @private
    ~FontFactory() = default;

    /// @private
    /// @static
    /// @property The instance of font factory
    static FontFactory* _instance;

    /// @private
    /// @property The font library
    FT_Library _library;
};

} // namespace ngind

#endif //NGIND_FONT_FACTORY_H
