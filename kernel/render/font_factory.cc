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
// FILENAME: font_factory.h
// LAST MODIFY: 2020/10/19

#include "font_factory.h"

namespace ngind {
FontFactory* FontFactory::_instance = nullptr;

FontFactory::FontFactory() : _library(nullptr) {
    auto error = FT_Init_FreeType(&_library);
    if (error) {
        // TODO: throw
    }
}

FontFactory* FontFactory::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) FontFactory();
    }

    return _instance;
}

void FontFactory::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

FT_Face FontFactory::loadFontFace(const std::string& filename, const long& index) {
    FT_Face face = nullptr;
    auto error = FT_New_Face(_library, filename.c_str(), index, &face);
    if (error) {
        face = nullptr;
    }

    return face;
}

}