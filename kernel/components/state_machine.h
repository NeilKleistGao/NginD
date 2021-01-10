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

/// @file state_machine.h

#ifndef NGIND_STATE_MACHINE_H
#define NGIND_STATE_MACHINE_H

#include "component.h"
#include "script/lua_state.h"
#include "script/lua_registration.h"
#include "rttr/registration.h"

namespace ngind::components {

class StateMachine : public Component {
public:
    StateMachine();
    ~StateMachine() override;

    void init(const typename resources::ConfigResource::JsonObject& data) override;
    static StateMachine* create(const typename resources::ConfigResource::JsonObject& data);

    inline void move(const std::string& state_name) {
        _state_name = state_name;
    }

    void halt();

    void update(const float& dlt) override;

    inline void setParent(Object* parent) override {
        Component::setParent(parent);
        _instance["game_object"] = _parent;
    }
private:
    luabridge::LuaRef _instance;

    luabridge::LuaRef _update_function;
    std::string _state_name;
};

RTTR_REGISTRATION {
    rttr::registration::class_<StateMachine>("StateMachine")
            .method("create", &StateMachine::create);
}

NGIND_LUA_BRIDGE_REGISTRATION(StateMachine) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .beginClass<StateMachine>("StateMachine")
            .addFunction("move", &StateMachine::move)
            .addFunction("halt", &StateMachine::halt)
        .endClass()
    .endNamespace();
}

} // namespace ngind::components

#endif //NGIND_STATE_MACHINE_H
