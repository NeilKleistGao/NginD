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
// FILENAME: mouse_input.h
// LAST MODIFY: 2020/10/21

#ifndef NGIND_MOUSE_INPUT_H
#define NGIND_MOUSE_INPUT_H

#include "glfw3.h"

#include "math/vector.h"

namespace ngind {

enum MouseCode {
    BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
    BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
    BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
};

class MouseInput {
public:
    explicit MouseInput(GLFWwindow*);
    ~MouseInput();

    Vector2D getMousePressed(GLFWwindow*, const MouseCode&);
    Vector2D getMouse(GLFWwindow*, const MouseCode&);
    Vector2D getMouseReleased(GLFWwindow*, const MouseCode&);
    Vector2D getMouseMoving(GLFWwindow*);
private:

};

} // namespace ngind

#endif //NGIND_MOUSE_INPUT_H
