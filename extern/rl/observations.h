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

/// @file observations.h

#ifndef NGIND_OBSERVATIONS_H
#define NGIND_OBSERVATIONS_H

#include <unordered_map>

#include "script/lua_state.h"
#include "memory/auto_collection_object.h"

namespace ngind::objects {
    class Object;
} // namespace ngind::objects

namespace ngind::rl {

class Observations : public memory::AutoCollectionObject {
public:
    explicit Observations(objects::Object* object);
    ~Observations() override = default;

    luabridge::LuaRef getObservationSpace();

    void addObservation(const std::string& ob_name, const std::string& node_name, const std::string& sm_name, const std::string& func_name);

    static Observations* create(objects::Object* object);
private:
    using Getter = std::tuple<objects::Object*, std::string, std::string>;

    objects::Object* _object;
    std::unordered_map<std::string, Getter> _observations;

    objects::Object* searchObject(objects::Object* object, const std::string& name);
protected:
};

NGIND_LUA_BRIDGE_REGISTRATION(Observations) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<Observations, memory::AutoCollectionObject>("Observations")
                .addStaticFunction("create", &Observations::create)
                .addFunction("addObservation", &Observations::addObservation)
                .addFunction("getObservationSpace", &Observations::getObservationSpace)
            .endClass()
        .endNamespace();
}

} // namespace ngind::rl

#endif //NGIND_OBSERVATIONS_H
