/**
 * @copybrief
 * MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file agent.h

#ifndef NGIND_AGENT_H
#define NGIND_AGENT_H

#include <unordered_map>

#include "action.h"
#include "memory/auto_collection_object.h"
#include "script/lua_registration.h"

namespace ngind::objects {
class Object;
} // namespace ngind::objects

namespace ngind::rl {

class Agent : public memory::AutoCollectionObject {
public:
    explicit Agent(objects::Object* object);
    ~Agent() override;

    void addAction(const std::string& sm, const std::string& fc);

    inline std::vector<Action*>& getActionSpace() {
        return _actions;
    }
private:
    objects::Object* _object;
    std::vector<Action*> _actions;
protected:
};

NGIND_LUA_BRIDGE_REGISTRATION(Agent) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<Agent, memory::AutoCollectionObject>("Agent")
                .addConstructor<void(*)(objects::Object*)>()
                .addFunction("addAction", &Agent::addAction)
            .endClass()
        .endNamespace();
}

} // namespace ngind::rl

#endif //NGIND_AGENT_H
