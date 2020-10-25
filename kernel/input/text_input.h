// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: text_input.h
// LAST MODIFY: 2020/10/25

#ifndef NGIND_TEXT_INPUT_H
#define NGIND_TEXT_INPUT_H

#include <string>
#include <list>

#include "glfw3.h"

namespace ngind {

enum EncodingType {
    ENCODING_ASCII,
    ENCODING_UTF8 // TODO: hook sys
};

class TextInput {
public:
    explicit TextInput(GLFWwindow*&);
    ~TextInput() = default;

    std::string getString(const EncodingType& encoding = EncodingType::ENCODING_ASCII);

    inline void setEnable(const bool& enable) {
        _enabled = enable;
    }
private:
    static void textCallBack(GLFWwindow*, unsigned int);

    std::list<unsigned int> _buff;
    static TextInput* _self;
    bool _enabled;
};

} // namespace ngind

#endif //NGIND_TEXT_INPUT_H
