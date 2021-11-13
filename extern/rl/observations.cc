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

/// @file observations.cc

#include "observations.h"

#include "script/lua_state.h"
#include "objects/entity_object.h"
#include "components/state_machine.h"

namespace ngind::rl {

Observations::Observations(objects::Object* object) : memory::AutoCollectionObject(), _object(object) {
}

luabridge::LuaRef Observations::getObservationSpace() {
    auto* ins = script::LuaState::getInstance();
    auto table = luabridge::newTable(ins->getState());

    for (auto [name, getter] : _observations) {
        auto* target = std::get<0>(getter);
        auto sm = std::get<1>(getter);
        auto func = std::get<2>(getter);

        auto* machine = target->getComponent<components::StateMachine>(sm);
        table[name] = machine->getInstance()[func](machine->getInstance());
    }

    return table;
}

void Observations::addObservation(const std::string& ob_name, const std::string& node_name, const std::string& sm_name, const std::string& func_name) {
    objects::Object* target;
    if (node_name.empty()) {
        target = _object;
    }
    else {
        target = searchObject(_object, node_name);
    }

    if (target != nullptr) {
        auto* machine = target->getComponent<components::StateMachine>(sm_name);
        if (machine != nullptr) {
            auto ref = machine->getInstance();
            auto func = ref[func_name];

            if (func.isFunction()) {
                _observations[ob_name] = std::make_tuple(target, sm_name, func_name);
            }
        }
    }
}


objects::Object* Observations::searchObject(objects::Object* object, const std::string& name) {
    auto* entity = object->getChildByName(name);
    if (entity != nullptr) {
        return entity;
    }

    auto children = object->getChildren();
    for (auto* child : children) {
        auto* temp = searchObject(child, name);
        if (temp != nullptr) {
            return temp;
        }
    }

    return nullptr;
}

Observations* Observations::create(objects::Object* object) {
    return new Observations{object};
}

} // namespace ngind::rl