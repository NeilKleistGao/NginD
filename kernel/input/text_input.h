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

/// @file text_input.h

#ifndef NGIND_TEXT_INPUT_H
#define NGIND_TEXT_INPUT_H

#include <string>
#include <list>

#include "glfw3.h"

namespace ngind::input {

/**
 * The encoding type code for text input.
 */
enum EncodingType {
    ENCODING_ASCII,
    ENCODING_UTF8 /// @todo hook sys
};

/**
 * The text input manager. This is a more sophisticated interface with
 * GLFWwindow as a param. Use Input class instead.
 */
class TextInput {
public:
    /**
     * @param window: the GLFW window that is the event listener
     */
    explicit TextInput(GLFWwindow*& window);

    ~TextInput() = default;

    /**
     * @see kernel/input/input.h
     */
    std::string getString(const EncodingType& encoding = EncodingType::ENCODING_ASCII);

    /**
     * Enable text input
     * @param enable: whether enable it or not
     */
    inline void setEnable(const bool& enable) {
        _enabled = enable;
    }
private:
    /**
     * The callback function for glfw to receive text input
     * @param window: the GLFW window that is the event listener
     * @param code: the code that user inputs
     */
    static void textCallBack(GLFWwindow* window, unsigned int code);

    /**
     * A buffer reserves for text input
     */
    std::list<unsigned int> _buff;

    /**
     * A self pointer used in the callback function
     */
    static TextInput* _self;

    /**
     * Whether text input is enabled
     */
    bool _enabled;
};

} // namespace ngind::input

#endif //NGIND_TEXT_INPUT_H
