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
// LAST MODIFY: 2020/10/16
// FILENAME: game.cc

#include "game.h"

#include "render/render.h"
#include "resources/resources_manager.h"
#include "log/logger_factory.h"

namespace ngind {

Game::Game() : _global_timer() {
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

    auto global_logger = LoggerFactory::getInstance()->getLogger(Logger::STDOUT, LogLevel::LOG_LEVEL_DEBUG);

    const float MIN_DURATION = 1.0f / _global_settings->getDocument()["max-frame-rate"].GetFloat();
    _global_timer.start();
    while (main_loop_flag) {
        glfwPollEvents();
        main_loop_flag &= render->startRenderLoopOnce();

        float duration = _global_timer.getTick(), rest = MIN_DURATION - duration;
        if (rest >= 0.005) {
            _global_timer.sleep(rest);
            global_logger->log<float>(60.0f, LogLevel::LOG_LEVEL_DEBUG);
        }
        else {
            global_logger->log<float>(1.0f / duration, LogLevel::LOG_LEVEL_DEBUG);
        }
    }
}

} // namespace ngind