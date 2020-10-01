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
// LAST MODIFY: 2020/10/1
// FILENAME: game.cc

#include "game.h"

#include "render/render.h"
#include "filesystem/file.h"
#include "filesystem/file_utils.h"

namespace ngind {

Game::Game() : _global_settings_doc(new rapidjson::Document()) {
    this->loadGlobalSettings();
}

Game::~Game() {
    if (_global_settings_doc != nullptr) {
        delete  _global_settings_doc;
        _global_settings_doc = nullptr;
    }
}

void Game::start() {
    bool main_loop_flag = true;

    auto render = Render::getInstance();
    render->createWindow((*_global_settings_doc)["window-width"].GetInt(),
                         (*_global_settings_doc)["window-height"].GetInt(),
                         (*_global_settings_doc)["window-title"].GetString(),
                         (*_global_settings_doc)["window-icon"].GetString(),
                         (*_global_settings_doc)["window-full-screen"].GetBool());

    delete _global_settings_doc;
    _global_settings_doc = nullptr;

    while (main_loop_flag) {
        glfwPollEvents();
        main_loop_flag &= render->startRenderLoopOnce();
    }
}

void Game::loadGlobalSettings() {
    File* file = new File(CONFIG_RESOURCES_PATH + "/global_settings.json", "r");
    std::string content = file->readToEnd();
    file->close();

    bool flag = _global_settings_doc->Parse(content.c_str()).HasParseError();
    if (flag) {
        throw "Can't Open Global Settings File!";
    }
}

} // namespace ngind