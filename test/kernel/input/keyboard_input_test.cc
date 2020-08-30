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
// LAST MODIFY: 2020/8/29
// FILENAME: keyboard_input_test.cc

//#define NGIND_KEYBOARD_INPUT_TEST
#ifdef NGIND_KEYBOARD_INPUT_TEST

#include <iostream>

#include "reflection_injector.h"
#include "render/render.h"
#include "input/input.h"

int main() {
    ngind::injectReflection();

    bool main_loop_flag = true;

    auto render = ngind::Render::getInstance();
    render->createWindow();

    auto input = ngind::Input::getInstance();
    input->registerKeyCodeName("test_once", ngind::KeyboardCode::SPACE);
    input->registerKeyCodeName("test", ngind::KeyboardCode::ENTER);

    while (main_loop_flag) {
        glfwPollEvents();
        main_loop_flag &= render->startRenderLoopOnce();

        if (input->getKey("test_once", true)) {
            std::cout << "once press" << std::endl;
        }
        if (input->getKey("test", false)) {
            std::cout << "test" << std::endl;
        }
    }

    return 0;
}

#endif // NGIND_KEYBOARD_INPUT_TEST
