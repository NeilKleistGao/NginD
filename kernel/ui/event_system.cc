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

/// @file event_system.cc

#include "event_system.h"

#include <cmath>

#include "input/input.h"
#include "script/observer.h"
#include "script/lua_state.h"

namespace ngind::ui {
EventSystem* EventSystem::_instance = nullptr;

EventSystem::EventSystem() : _tree(nullptr) {
}

EventSystem::~EventSystem() {
    if (_tree != nullptr) {
        delete _tree;
        _tree = nullptr;
    }
}

EventSystem* EventSystem::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) EventSystem();
        if (_instance == nullptr) {
            // TODO:
        }
    }

    return _instance;
}

void EventSystem::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void EventSystem::registerEvent(const ClickableReceiver& receiver) {
    if (_tree == nullptr) {
        // TODO:
    }

    _tree->insert(receiver);
}

void EventSystem::unregisterEvent(const ClickableReceiver& receiver) {
    if (_tree == nullptr) {
        // TODO:
    }

    _tree->erase(receiver);
}

void EventSystem::update() {
    if (_tree == nullptr) {
        return;
    }

    auto instance = input::Input::getInstance();
    instance->setInterruption(false);

    auto left = instance->getMouseReleased(0),
         right = instance->getMouseReleased(1),
         middle = instance->getMouseReleased(2);

    instance->setInterruption(true);
    if (!std::isnan(left.x) && !std::isnan(left.y)) {
        auto p = _tree->query(left, input::BUTTON_LEFT);
        if (p != nullptr) {
            script::Observer::getInstance()
                ->notifyAll(script::LuaState::getInstance()->createNil(), p->event_name, script::LuaState::getInstance()->createNil());
        }
    }
    else if (!std::isnan(right.x) && !std::isnan(right.y)) {
        auto p = _tree->query(right, input::BUTTON_RIGHT);
        if (p != nullptr) {
            script::Observer::getInstance()
                    ->notifyAll(script::LuaState::getInstance()->createNil(), p->event_name, script::LuaState::getInstance()->createNil());
        }
    }
    else if (!std::isnan(middle.x) && !std::isnan(middle.y)) {
        auto p = _tree->query(middle, input::BUTTON_MIDDLE);
        if (p != nullptr) {
            script::Observer::getInstance()
                    ->notifyAll(script::LuaState::getInstance()->createNil(), p->event_name, script::LuaState::getInstance()->createNil());
        }
    }
    else {
        instance->setInterruption(false);
    }
}

void EventSystem::init(const size_t& width, const size_t& height) {
    if (_tree != nullptr) {
        delete _tree;
        _tree = nullptr;
    }

    _tree = new(std::nothrow) QuadTree(height, 0, 0, width);
    if (_tree == nullptr) {
        // TODO:
    }
}

} // namespace ngind::ui