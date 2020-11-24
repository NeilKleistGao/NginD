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

/// @file text_input.h
/// @date 2020/10/25

/**
@brief
    This file includes text encoding type and text input manager. You should not
visit text input class directly but use input class instead.
*/

#ifndef NGIND_TEXT_INPUT_H
#define NGIND_TEXT_INPUT_H

#include <string>
#include <list>

#include "glfw3.h"

namespace ngind {

/**
@enum
    The encoding type code for text input.
*/
enum EncodingType {
    ENCODING_ASCII,
    ENCODING_UTF8 /// @todo hook sys
};

/**
@class
    The text input manager. This is a more sophisticated interface with
GLFWwindow as a param. Use Input class instead.
*/
class TextInput {
public:
    /// @public
    /// @param GLFWwindow*: the GLFW window that is the event listener
    explicit TextInput(GLFWwindow*&);

    /// @public
    ~TextInput() = default;

    /// @see kernel/input/input.h
    std::string getString(const EncodingType& encoding = EncodingType::ENCODING_ASCII);

    /// @public
    /// @fn Enable text input
    /// @param const bool& enable: whether enable it or not
    /// @return void
    inline void setEnable(const bool& enable) {
        _enabled = enable;
    }
private:

    /// @private
    /// @static
    /// @fn The callback function for glfw to receive text input
    /// @param GLFWwindow*: the GLFW window that is the event listener
    /// @param unsigned int: the code that user inputs
    static void textCallBack(GLFWwindow*, unsigned int);

    /// @private
    /// @property A buffer reserves for text input
    std::list<unsigned int> _buff;

    /// @private
    /// @property A self pointer used in the callback function
    static TextInput* _self;

    /// @private
    /// @property Whether text input is enabled
    bool _enabled;
};

} // namespace ngind

#endif //NGIND_TEXT_INPUT_H
