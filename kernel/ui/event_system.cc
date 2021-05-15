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

#include "components/button.h"
#include "event_system.h"

#include <cmath>

#include "input/input.h"
#include "script/observer.h"
#include "script/lua_state.h"

namespace ngind::ui {
EventSystem* EventSystem::_instance = nullptr;

EventSystem::EventSystem() : _tree(nullptr), _current_receiver(nullptr), _current_moving(nullptr) {
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

    auto mouse = instance->getMousePressed(0);

    instance->setInterruption(true);
    if (!std::isnan(mouse.x) && !std::isnan(mouse.y)) {
        mouse.y = _win_height - mouse.y;
        auto p = _tree->query(mouse);
        if (p != nullptr) {
            _current_receiver = p;
            p->button->setPressed(true);
        }
        else {
            instance->setInterruption(false);
        }
    }
    else {
        mouse = instance->getMouseReleased(0);
        if (!std::isnan(mouse.x) && !std::isnan(mouse.y)) {
            mouse.y = _win_height - mouse.y;
            auto p = _tree->query(mouse);
            if (p != nullptr && p == _current_receiver) {
                script::Observer::getInstance()
                        ->notifySiblings("Click", p->button->getParent(), script::LuaState::getInstance()->createNil());
                p->button->setPressed(false);
            }
            else if (_current_receiver != nullptr) {
                _current_receiver->button->setPressed(false);
                _current_receiver = nullptr;
            }
            else {
                instance->setInterruption(false);
            }
        }
        else {
            instance->setInterruption(false);
        }
    }

    if (_current_moving != nullptr) {
        _current_moving->button->setHighlighted(false);
        _current_moving = nullptr;
    }

    mouse = input::Input::getInstance()->getMouseMoving();
    mouse.y = _win_height - mouse.y;
    auto p = _tree->query(mouse);
    if (p != nullptr) {
        _current_moving = p;
        _current_moving->button->setHighlighted(true);
    }
}

void EventSystem::init(const size_t& width, const size_t& height) {
    if (_tree != nullptr) {
        delete _tree;
        _tree = nullptr;
    }

    _tree = new(std::nothrow) KDTree();
    if (_tree == nullptr) {
        // TODO:
    }
}

} // namespace ngind::ui