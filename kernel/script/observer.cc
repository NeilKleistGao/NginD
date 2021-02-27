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

/// @file observer.h

#include "observer.h"

#include "components/state_machine.h"
#include "math/random.h"

namespace ngind::script {
Observer* Observer::_instance = nullptr;

Observer::~Observer() {
    _dependence.clear();
}

Observer* Observer::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Observer();
    }

    return _instance;
}

void Observer::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void Observer::subscribe(components::StateMachine* machine, const std::string& name) {
    if (_dependence.find(name) == _dependence.end()) {
        _dependence[name] = std::vector<components::StateMachine*>{};
    }

    auto& list = _dependence[name];
    list.push_back(machine);
}

void Observer::notify(const luabridge::LuaRef& sender, const std::string& name, luabridge::LuaRef data) {
    if (_dependence.find(name) == _dependence.end()) {
        // TODO:
    }

    auto& list = _dependence[name];
    if (list.empty()) {
        // TODO:
    }

    using math::Random;
    Random random;
    auto index = random.getRangeRandomNumber(0, list.size());
    list[index]->receive(sender, name, data);
}

void Observer::notifyAll(const luabridge::LuaRef& sender, const std::string& name, luabridge::LuaRef data) {
    if (_dependence.find(name) == _dependence.end()) {
        // TODO:
    }

    auto& list = _dependence[name];
    if (list.empty()) {
        // TODO:
    }

    for (const auto& m : list) {
        m->receive(sender, name, data);
    }
}

void Observer::cancel(components::StateMachine* machine, const std::string& name) {
    if (_dependence.find(name) == _dependence.end()) {
        // TODO:
    }

    auto& list = _dependence[name];
    decltype(list.begin()) it;
    bool flag = false;

    for (it = list.begin(); it != list.end(); it++) {
        if (*it == machine) {
            flag = true;
            break;
        }
    }

    if (flag) {
        list.erase(it);
    }
}

} // namespace ngind::script