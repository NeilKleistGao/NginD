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

/// @file environment.cc

#include "environment.h"
#include "script/lua_state.h"

namespace ngind::rl {

Environment::Environment(Agent* agent, Observations* ob, Algorithm* algorithm, const std::string& script, const std::string& cl)
    : memory::AutoCollectionObject(),  _agent(agent), _observations(ob), _algorithm(algorithm),
      _script(script::LuaState::getInstance()->createNil()), _current(0) {
    auto* ins = script::LuaState::getInstance();
    ins->loadScript(script);

    _script = ins->createStateMachine(cl);
}

Environment::~Environment() {
    if (_agent != nullptr) {
        _agent->removeReference();
        _agent = nullptr;
    }

    if (_observations != nullptr) {
        _observations->removeReference();
        _observations = nullptr;
    }

    if (_algorithm != nullptr) {
        _algorithm->removeReference();
        _algorithm = nullptr;
    }
}

void Environment::update() {
    if (_agent == nullptr || _observations == nullptr || _algorithm == nullptr || _script.isNil()) {
        return;
    }

    int steps = _algorithm->getSteps();
    if (_current < steps) {
        auto ob_space = _observations->getObservationSpace();
        if (_algorithm->step(_agent, ob_space)) {
            auto reset = _script["reset"];
            if (!reset.isNil() && reset.isFunction()) {
                reset();
            }
        }

        ++_current;
    }
}

void Environment::setAgent(Agent* agent) {
    if (_agent != nullptr) {
        _agent->removeReference();
        _agent = nullptr;
    }

    _agent = agent;
    _agent->addReference();
}

void Environment::setObservations(Observations* ob) {
    if (_observations != nullptr) {
        _observations->removeReference();
        _observations = nullptr;
    }

    _observations = ob;
    _observations->addReference();
}

void Environment::setAlgorithm(Algorithm* algorithm) {
    if (_algorithm != nullptr) {
        _algorithm->removeReference();
        _algorithm = nullptr;
    }

    _algorithm = algorithm;
    _algorithm->addReference();
}

} // namespace ngind::rl