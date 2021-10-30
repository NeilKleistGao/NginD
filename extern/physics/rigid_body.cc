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

/// @file rigid_body.cc

#include "rigid_body.h"

#include "kernel/game.h"
#include "physics_world.h"
#include "glm/glm.hpp"
#include "kernel/log/logger_factory.h"

namespace ngind::physics {

RigidBody::RigidBody() : components::Component(),
    _body(nullptr), _def(), _fixture_def(), _fixture(nullptr), _shape(nullptr), _ep(nullptr) {
}

RigidBody::~RigidBody() {
    if (_shape != nullptr) {
        delete _shape;
        _shape = nullptr;
    }

    if (_body != nullptr) {
        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        if (pw != nullptr) {
            pw->_world.DestroyBody(_body);
            _body = nullptr;
        }
    }
}

void RigidBody::update(const float& delta) {
    if (_body == nullptr) {
        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        if (pw == nullptr) {
            return;
        }

        _ep = dynamic_cast<objects::EntityObject*>(_parent);
        if (_ep == nullptr) {
            return;
        }
        _def.position += b2Vec2{_ep->getGlobalPositionX(), _ep->getGlobalPositionY()};
        _def.position -= b2Vec2{_ep->getPositionX(), _ep->getPositionY()};
        _def.angle += _ep->getGlobalRotation();
        _def.angle -= _ep->getRotation();

        _body = pw->_world.CreateBody(&_def);

        if (_body == nullptr) {
            return;
        }

        _fixture = _body->CreateFixture(&_fixture_def);
    }

    auto position = _body->GetPosition();
    auto global_offset = glm::vec2 {0, 0};
    float global_rot = 0.0f;
    auto gp = dynamic_cast<objects::EntityObject*>(_ep->getParent());

    if (gp) {
        global_offset = gp->getGlobalPosition();
        global_rot = gp->getGlobalRotation();
    }

    if (_def.type != b2BodyType::b2_staticBody) {
        _ep->setPosition(glm::vec2{position.x, position.y} - global_offset);
        auto angle = _body->GetAngle();
        _ep->setRotation(angle - global_rot);
    }
}

void RigidBody::init(const typename resources::ConfigResource::JsonObject& data) {
    try {
        auto position = data["init-position"].GetObject();
        _def.position.Set(position["x"].GetFloat(), position["y"].GetFloat());
        _def.angle = data["init-angle"].GetFloat();
        _def.angularDamping = data["angular-damping"].GetFloat();
        _def.linearDamping = data["linear-damping"].GetFloat();
        _def.type = static_cast<b2BodyType>(data["rigid-type"].GetInt());
        _def.fixedRotation = data["fixed-rotation"].GetBool();
        _def.gravityScale = data["gravity-scale"].GetFloat();

        _def.userData.pointer = reinterpret_cast<uintptr_t>(this);

        _fixture_def.density = data["density"].GetFloat();
        _fixture_def.friction = data["friction"].GetFloat();
        _fixture_def.filter.categoryBits = data["category"].GetInt();
        _fixture_def.filter.maskBits = data["mask"].GetInt();

        auto shape_data = data["shape"].GetObject();
        std::string shape_name = shape_data["name"].GetString();
        if (shape_name == "circle") {
            _shape = new CircleShape(shape_data["data"]);
        }
        else if (shape_name == "polygon") {
            _shape = new PolygonShape(shape_data["data"]);
        }
        else if (shape_name == "edge") {
            _shape = new EdgeShape(shape_data["data"]);
        }
        else if (shape_name == "chain") {
            _shape = new ChainShape(shape_data["data"]);
        }
        else {
            throw std::exception();
        }

        _fixture_def.shape = _shape->shape;
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("An error occurred when initializing rigid body.");
        logger->flush();
    }
}

RigidBody* RigidBody::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* body = memory::MemoryPool::getInstance()->create<RigidBody>();
    body->init(data);
    return body;
}

void RigidBody::applyForce(const glm::vec2& force) {
    if (_body == nullptr) {
        return;
    }
    _body->ApplyForceToCenter({force.x, force.y}, true);
}

void RigidBody::applyTorque(float torque) {
    if (_body == nullptr) {
        return;
    }

    _body->ApplyTorque(torque, true);
}

void RigidBody::setVelocity(const glm::vec2& velocity) {
    if (_body == nullptr) {
        return;
    }

    _body->SetLinearVelocity({velocity.x, velocity.y});
}

void RigidBody::setAngularVelocity(float velocity) {
    if (_body == nullptr) {
        return;
    }

    _body->SetAngularVelocity(velocity);
}

void RigidBody::setSleepingAllowed(bool allowed) {
    if (_body == nullptr) {
        return;
    }

    _body->SetSleepingAllowed(allowed);
}

bool RigidBody::isSleepingAllowed() const {
    if (_body == nullptr) {
        return true;
    }

    return _body->IsSleepingAllowed();
}

void RigidBody::setRotationFixed(bool fixed) {
    if (_body == nullptr) {
        return;
    }

    _body->SetFixedRotation(fixed);
}

bool RigidBody::isRotationFixed() const {
    if (_body == nullptr) {
        return false;
    }

    return _body->IsFixedRotation();
}

} // namespace ngind::physics