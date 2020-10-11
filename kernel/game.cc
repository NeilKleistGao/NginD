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
// LAST MODIFY: 2020/10/11
// FILENAME: game.cc

#include "game.h"

#include "render/render.h"
#include "resources/resources_manager.h"

namespace ngind {

Game::Game() {
    this->_global_settings = ResourcesManager::getInstance()->load<ConfigResource>("global_settings.json");
}

Game::~Game() {
    ResourcesManager::getInstance()->release(this->_global_settings->getResourcePath());
}

void Game::start() {
    bool main_loop_flag = true;

    auto render = Render::getInstance();
    render->createWindow(_global_settings->getDocument()["window-width"].GetInt(),
            _global_settings->getDocument()["window-height"].GetInt(),
            _global_settings->getDocument()["window-title"].GetString(),
            _global_settings->getDocument()["window-icon"].GetString(),
            _global_settings->getDocument()["window-full-screen"].GetBool());


    while (main_loop_flag) {
        glfwPollEvents();
        main_loop_flag &= render->startRenderLoopOnce();
    }
}

} // namespace ngind