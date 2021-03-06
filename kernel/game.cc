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

/// @file game.cc

#include "game.h"

#include "rendering/renderer.h"
#include "resources/resources_manager.h"
#include "log/visual_logger.h"
#include "script/lua_state.h"
#include "memory/memory_pool.h"
#include "ui/event_system.h"

namespace ngind {
Game* Game::_instance = nullptr;

Game::Game() : _global_timer(), _loop_flag(true), _current_world(nullptr), _transition(), _trans_next(false) {
    this->_global_settings = resources::ResourcesManager::getInstance()->load<resources::ConfigResource>("global_settings.json");
}

Game::~Game() {
    resources::ResourcesManager::getInstance()->release(this->_global_settings->getResourcePath());

    while (!_stack.empty()) {
        _stack.pop();
    }

    _worlds.clear();
    script::LuaState::getInstance()->destroyInstance();
}

Game* Game::getInstance() {
    if (_instance == nullptr) {
        _instance = new Game();
    }

    return _instance;
}

void Game::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void Game::start() {
    auto render = rendering::Renderer::getInstance();
    auto height = _global_settings->getDocument()["window-height"].GetInt();
    render->createWindow(_global_settings->getDocument()["window-width"].GetInt(),
            height,
            _global_settings->getDocument()["window-title"].GetString(),
            _global_settings->getDocument()["window-icon"].GetString(),
            _global_settings->getDocument()["window-full-screen"].GetBool());

    ui::EventSystem::getInstance()->init(height);

    script::LuaState::getInstance()->preload("kernel");

    this->loadWorld(_global_settings->getDocument()["welcome-world"].GetString());

    auto logger = log::VisualLogger::getInstance();
    if (_global_settings->getDocument()["enable-visual-debug"].GetBool()) {
        logger->enable();
    }

    const float MAX_FRAME_RATE = _global_settings->getDocument()["max-frame-rate"].GetFloat();
    const float MIN_DURATION = 1.0f / MAX_FRAME_RATE;
    float duration = 1.0f / 60.0f;
    logger->registerVariable("frame rate", "0");
    _global_timer.start();
    while (_loop_flag) {
        if (_trans_next) {
            _transition();
            _trans_next = false;
        }

        glfwPollEvents();
        render->clearScene(_current_world->getBackgroundColor());
        ui::EventSystem::getInstance()->update();
        this->_current_world->update(duration);
        logger->draw();
        _loop_flag &= render->startRenderingLoopOnce();

        memory::MemoryPool::getInstance()->clear();

        duration = _global_timer.getTick();
        float rest = MIN_DURATION - duration;
        if (rest >= 0.005) {
            _global_timer.sleep(rest);
            logger->updateVariable("frame rate", MAX_FRAME_RATE);
            duration = MIN_DURATION;
        }
        else if (std::abs(rest) <= 0.0075) {
            logger->updateVariable("frame rate", MAX_FRAME_RATE);
            duration = MIN_DURATION;
        }
        else {
            logger->updateVariable("frame rate", 1.0f / duration);
        }
    }
}

void Game::loadWorld(const std::string& name) {
    if (this->_worlds.find(name) == this->_worlds.end()) {
        this->_worlds[name] = memory::MemoryPool::getInstance()->create<objects::World>(name);
        this->_worlds[name]->addReference();
    }

    this->_current_world = this->_worlds[name];
    this->_worlds[name]->loadObjects();
}

void Game::loadWorld(resources::ConfigResource* config) {
    std::string name = config->getDocument()["world-name"].GetString();
    if (this->_worlds.find(name) == this->_worlds.end()) {
        this->_worlds[name] = memory::MemoryPool::getInstance()->create<objects::World>(config);
        this->_worlds[name]->addReference();
    }

    this->_current_world = this->_worlds[name];
    this->_worlds[name]->loadObjects();
}

void Game::destroyWorld(const std::string& name) {
    if (this->_worlds.find(name) != this->_worlds.end()) {
        auto current_name = this->_current_world->getName();

        this->_worlds[name]->removeReference();
        this->_worlds.erase(name);

        if (current_name == name) {
            this->_current_world = nullptr;
            exit(0);
        }
    }
}

void Game::pushAndLoadWorld(const std::string& name) {
    this->_stack.push(this->_current_world);
    this->loadWorld(name);
}

void Game::popAndLoadWorld(const bool& has_destroy_current = true) {
    if (!this->_stack.empty()) {
        auto destroy_name = this->_current_world->getName();
        this->_current_world = this->_stack.top();
        this->_stack.pop();

        if (has_destroy_current) {
            destroyWorld(destroy_name);
        }
    }
}

void Game::destroyAndLoadWorld(std::string name) {
    _next_world = name;
    _transition = [&]() {
        auto destroy_name = this->_current_world->getName();
        loadWorld(_next_world);
        destroyWorld(destroy_name);
    };

    _trans_next = true;
}

} // namespace ngind