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
// FILENAME: text_input.h
// LAST MODIFY: 2020/10/25

#include "text_input.h"

namespace ngind {
TextInput* TextInput::_self = nullptr;

TextInput::TextInput(GLFWwindow*& win) : _enabled(false) {
    glfwSetCharCallback(win, TextInput::textCallBack);
    TextInput::_self = this;
}

std::string TextInput::getString(const EncodingType& encoding) {
    std::string res = "";
    for (const auto& ch : _buff) {
        if (encoding == EncodingType::ENCODING_ASCII) {
            res += static_cast<char>(ch);
        }
        else if (encoding == EncodingType::ENCODING_UTF8) {
            res += static_cast<char>(ch & 0x000000FF);
            res += static_cast<char>(ch & 0x0000FF00);
        }
    }

    _buff.clear();
    return res;
}

void TextInput::textCallBack(GLFWwindow*, unsigned int codepoint) {
    if (_self->_enabled) {
        _self->_buff.push_back(codepoint);
    }
}

} // namespace ngind