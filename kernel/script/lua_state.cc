/** MIT License
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

/// @file lua_state.cc

#include "lua_state.h"

#include <filesystem>

namespace ngind::script {
LuaState* LuaState::_instance = nullptr;
const std::string LuaState::SCRIPT_PATH = "resources/script";

LuaState::LuaState() : _state(nullptr) {
    _state = luaL_newstate();
    luaL_openlibs(_state);
}

LuaState::~LuaState() {
    if (_state != nullptr) {
        lua_close(_state);
        _state = nullptr;
    }
}

LuaState* LuaState::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) LuaState();
    }

    return _instance;
}

void LuaState::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void LuaState::loadScript(const std::vector<std::string>& filenames) {
    for (const auto& filename :filenames) {
        this->loadScript(filename);
    }
}

void LuaState::loadScript(const std::string& name) {
    if (_visit.find(name) != _visit.end()) {
        return;
    }

    _visit.insert(name);
    auto res = luaL_dofile(_state, (SCRIPT_PATH + "/" + name).c_str());
    if (res) {
        // TODO:
    }
}

luabridge::LuaRef LuaState::createStateMachine(const std::string& classname) {
    luabridge::LuaRef create_function = luabridge::getGlobal(_state, classname.c_str())["new"];
    if (create_function.isNil() || !create_function.isFunction()) {
        // TODO:
    }

    luabridge::LuaRef object = create_function();
    return object;
}

void LuaState::destroyStateMachineInstance(luabridge::LuaRef& instance) {
    if (!instance.isNil()) {
        instance = luabridge::Nil{};
    }
}

void LuaState::preload(const std::string& path) {
    for (auto& p : std::filesystem::directory_iterator(SCRIPT_PATH + "/" + path)) {
        if (!p.is_directory()) {
            auto filename = path + "/" + p.path().filename().string();
            _preload_list.push_back(filename);
            this->loadScript(filename);
        }
    }
}

void LuaState::restart() {
    if (_state != nullptr) {
        lua_close(_state);
        _state = nullptr;
    }

    _state = luaL_newstate();
    luaL_openlibs(_state);

    _visit.clear();
    for (const auto& s : _preload_list) {
        this->loadScript(s);
    }
}

} // namespace ngind::script