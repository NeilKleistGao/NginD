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

/// @file agent.cc

#include "agent.h"

#include "components/state_machine.h"

namespace ngind::rl {

Agent::Agent(objects::Object* object) : memory::AutoCollectionObject(),  _object(object), _actions{} {
}

Agent::~Agent() {
    for (auto* act : _actions) {
        delete act;
        act = nullptr;
    }

    _actions.clear();
}

void Agent::addAction(const std::string& sm, const std::string& fc) {
    if (_object == nullptr) {
        return;
    }

    auto* state_machine = _object->getComponent<components::StateMachine>(sm);
    if (state_machine != nullptr) {
        auto ref = state_machine->getInstance();
        auto function = ref[fc];
        if (function.isFunction()) {
            _actions.push_back(new Action{ref, function});
        }
    }
    else {
        auto* ins = script::LuaState::getInstance();
        auto function = luabridge::getGlobal(ins->getState(), fc.c_str());
        if (function.isFunction()) {
            _actions.push_back(new Action{ins->createNil(), function});
        }
    }
}

} // namespace ngind::rl