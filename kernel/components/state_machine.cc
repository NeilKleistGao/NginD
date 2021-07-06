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
_update_function(script::LuaState::getInstance()->getState()) {
}

StateMachine::~StateMachine() {
    halt();
    script::LuaState::getInstance()->destroyStateMachineInstance(_instance);
}

void StateMachine::init(const typename resources::ConfigResource::JsonObject& data) {
    _component_name = data["type"].GetString();

    auto state = script::LuaState::getInstance();
    state->loadScript(data["driver-script"].GetString());
    _instance = state->createStateMachine(data["classname"].GetString());

    if (_instance.isNil()) {
        // TODO:
    }

    _instance["this"] = this;
    if (typeid(_parent) == typeid(objects::EntityObject)) {
        _instance["game_object"] = dynamic_cast<objects::EntityObject*>(_parent);
    }
    else {
        _instance["game_object"] = _parent;
    }

    auto subscription = data["subscription"].GetArray();
    for (const auto& s : subscription) {
        auto item = s.GetObject();
        auto name = item["event-name"].GetString();
        _subscribe[name] = std::unordered_set<std::string>{};
        script::Observer::getInstance()->subscribe(this, name);

        auto whitelist = item["whitelist"].GetArray();
        for (const auto& w : whitelist) {
            _subscribe[name].insert(w.GetString());
        }
    }

    if (data.HasMember("properties")) {
        auto properties = data["properties"].GetArray();
        for (const auto& p : properties) {
            initProperty(p);
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

void StateMachine::move(const std::string& state_name) {
    _state_name = state_name;
    _update_function = _instance["update" + _state_name];
}

void StateMachine::receive(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data) {
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

void StateMachine::receive(const std::string& name, const luabridge::LuaRef& data) {
    auto receive_function = _instance["on" + name];
    if (receive_function.isNil() || !receive_function.isFunction()) {
        return;
    }

    receive_function(_instance, data);
}

void StateMachine::notify(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data) {
    auto ob = script::Observer::getInstance();
    ob->notify(sender, name, data);
}

void StateMachine::notifyAll(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data) {
    auto ob = script::Observer::getInstance();
    ob->notifyAll(sender, name, data);
}

void StateMachine::initProperty(const typename resources::ConfigResource::JsonObject& data) {
    // TODO:
}

} // namespace ngind::components