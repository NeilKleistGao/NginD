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

#include <map>
#include <unordered_set>

#include "component.h"
#include "script/lua_state.h"
#include "script/lua_registration.h"
#include "component_factory.h"

namespace ngind::components {

/**
 * State machine driven by Lua.
 * The core of this engine.
 */
class StateMachine : public Component {
public:
    StateMachine();
    ~StateMachine() override;

    /**
     * @see kernel/components/component.h
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    /**
     * Create a state machine.
     * @param data: the configuration data this component initialization process requires.
     * @return StateMachine*, a new state machine
     */
    static StateMachine* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Move to another state.
     * @param state_name: the name of next state
     */
    inline void move(const std::string& state_name) {
        _state_name = state_name;
    }

    /**
     * Stop running this state machine.
     */
    void halt();

    /**
     * @see kernel/objects/updatable_object.h
     */
    void update(const float& dlt) override;

    /**
     * @see kernel/components/component.h
     */
    inline void setParent(Object* parent) override {
        Component::setParent(parent);
        _instance["game_object"] = _parent;
    }

    /**
     * Receive a new message from observer.
     * @param sender: who sent this message
     * @param name: the name of this message
     * @param data: the data attended
     */
    void receive(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data);

    /**
     * Receive a new message from observer. This message is sent by engine.
     * @param name: the name of this message
     * @param data: the data attended
     */
    void receive(const std::string& name, const luabridge::LuaRef& data);

    /**
     * Publish a new message to a random target.
     * @param sender: who sent this message
     * @param name: the name of this message
     * @param data: the data attended
     */
    void notify(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data);

    /**
     * Publish a new message to all targets.
     * @param sender: who sent this message
     * @param name: the name of this message
     * @param data: the data attended
     */
    void notifyAll(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data);

    inline luabridge::LuaRef getInstance() {
        return _instance;
    }
private:
    /**
     * The instance of this component in lua environment.
     */
    luabridge::LuaRef _instance;

    /**
     * Current update function.
     */
    luabridge::LuaRef _update_function;

    /**
     * Name of current state
     */
    std::string _state_name;

    /**
     * Subscribe information, determining which message can be received in some state.
     */
    std::map<std::string, std::unordered_set<std::string>> _subscribe;
};

NGIND_LUA_BRIDGE_REGISTRATION(StateMachine) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .beginClass<StateMachine>("StateMachine")
            .addFunction("move", &StateMachine::move)
            .addFunction("halt", &StateMachine::halt)
            .addFunction("notify", &StateMachine::notify)
            .addFunction("notifyAll", &StateMachine::notifyAll)
        .endClass()
    .endNamespace();

    ComponentFactory::getInstance()->registerComponent<StateMachine>("StateMachine");
}

} // namespace ngind::components

#endif //NGIND_STATE_MACHINE_H
