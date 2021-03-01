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

/// @file state_machine.cc

#include "state_machine.h"
#include "script/observer.h"
#include "memory/memory_pool.h"

namespace ngind::components {
StateMachine::StateMachine() :
_instance(script::LuaState::getInstance()->getState()),
_update_function(script::LuaState::getInstance()->getState()),
_state_name(""){
}

StateMachine::~StateMachine() {
    halt();
    script::LuaState::getInstance()->destroyStateMachineInstance(_instance);
}

void StateMachine::init(const typename resources::ConfigResource::JsonObject& data) {
    auto state = script::LuaState::getInstance();
    state->loadScript(data["driver-script"].GetString());
    _instance = state->createStateMachine(data["classname"].GetString());

    if (_instance.isNil()) {
        // TODO:
    }

    _instance["this"] = this;
    _instance["game_object"] = _parent;

    auto subscribe = _instance["subscribe"];
    if (subscribe.isTable()) {
        for (int i = 1; i <= subscribe.length(); i++) {
            auto item = subscribe[i];
            auto name = item["name"].cast<std::string>();
            _subscribe[name] = std::unordered_set<std::string>{};
            script::Observer::getInstance()->subscribe(this, name);
            auto whitelist = item["whitelist"];
            for (int j = 1; j <= whitelist.length(); j++) {
                _subscribe[name].insert(whitelist[j].cast<std::string>());
            }
        }
    }
}

StateMachine* StateMachine::create(const typename resources::ConfigResource::JsonObject& data) {
    auto machine = memory::MemoryPool::getInstance()->create<StateMachine>();
    machine->init(data);
    return machine;
}

void StateMachine::halt() {
    luabridge::LuaRef state_exit = _instance["exit"];
    state_exit();
}

void StateMachine::update(const float& dlt) {
    if (_update_function.isNil()) {
        if (_state_name.empty()) {
            luabridge::LuaRef entry = _instance["enter"];
            entry(_instance);
            return;
        }

        _update_function = _instance["update" + _state_name];
        if (_update_function.isNil()) {
            // TODO:
        }
    }

    _update_function(_instance, dlt);
}

void StateMachine::receive(luabridge::LuaRef sender, const std::string& name, luabridge::LuaRef data) {
    const auto& whitelist = _subscribe[name];
    if (whitelist.find(_state_name) != whitelist.end() ||
        whitelist.find("__all__") != whitelist.end()) {
        auto receive_function = _instance["on" + name];
        if (receive_function.isNil() || !receive_function.isFunction()) {
            return;
        }

        receive_function(_instance, sender, data);
    }
}

void StateMachine::notify(luabridge::LuaRef sender, const std::string& name, luabridge::LuaRef data) {
    auto ob = script::Observer::getInstance();
    ob->notify(sender, name, data);
}

void StateMachine::notifyAll(luabridge::LuaRef sender, const std::string& name, luabridge::LuaRef data) {
    auto ob = script::Observer::getInstance();
    ob->notifyAll(sender, name, data);
}

} // namespace ngind::components