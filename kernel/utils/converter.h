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

/// @file converter.h
/// @date 2020/10/25

#ifndef NGIND_CONVERTER_H
#define NGIND_CONVERTER_H

#include <iostream>
#include <sstream>

namespace ngind {

/**
@class Converter helper class.
*/
class Converter {
public:
    /// @public
    /// @static
    /// @fn Convert from string using std::stringstream
    /// @tparam Type: Target type
    /// @param const std::string& str: string
    /// @return Type, convert result
    template <typename Type>
    static Type convertFromString(const std::string& str) {
        std::stringstream stream;
        Type t;
        stream << str;
        stream >> t;

        return t;
    }

    /// @public
    /// @static
    /// @fn Parse hex number.
    /// @param const std::string&: number in hex string
    /// @return unsigned int, number in decimal
    static unsigned int convertHexString(const std::string&);
};

} // namespace ngind

#endif //NGIND_CONVERTER_H
