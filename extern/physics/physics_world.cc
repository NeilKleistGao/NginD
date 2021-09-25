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

/// @file physics_manager.cc

#include "physics_world.h"

#include "kernel/log/logger_factory.h"

namespace ngind::physics {

PhysicsWorld::PhysicsWorld() : components::Component(), _gravity(0, -9.8), _world(_gravity), _passed(0.0f) {
}

PhysicsWorld::~PhysicsWorld() = default;

void PhysicsWorld::update(const float& delta) {
    components::Component::update(delta);
    _passed += _timer.getTick();
    if (_passed >= 0.2f) {
        _world.Step(0.2f, 8, 3);
        _passed -= 0.2f;
    }
}

void PhysicsWorld::init(const typename resources::ConfigResource::JsonObject& data) {
    try {
        auto gravity = data["gravity"].GetObject();
        _gravity = {gravity["x"].GetFloat(), gravity["y"].GetFloat()};
        setGravity(_gravity.x, _gravity.y);
        _world.SetContinuousPhysics(true);
        _world.SetAllowSleeping(true);
        _world.SetContactListener(&listener);
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("An error occurred when initializing physics world.");
        logger->flush();
    }
}

PhysicsWorld* PhysicsWorld::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* world = memory::MemoryPool::getInstance()->create<PhysicsWorld>();
    world->init(data);
    return world;
}

void PhysicsWorld::clearRigidBody(objects::Object* node) {
    auto body = node->getComponent<RigidBody>("RigidBody");
    _world.SetContactListener(nullptr);
    if (body != nullptr) {
        auto temp = body->_body;
        body->_body = nullptr;
        _world.DestroyBody(temp);
    }

    auto children = node->getChildren();
    for (auto* child : children) {
        clearRigidBody(child);
    }

    _world.SetContactListener(&listener);
}

} // namespace ngind::physics