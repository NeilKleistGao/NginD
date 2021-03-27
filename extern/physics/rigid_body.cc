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

namespace ngind::physics {

RigidBody::RigidBody() : components::Component(), _body(nullptr), _def(), _fixture(), _shape(nullptr) {
}

RigidBody::~RigidBody() {
    delete _shape;
    _shape = nullptr;
}

void RigidBody::update(const float& delta) {
    if (_body == nullptr) {
        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        _body = pw->_world.CreateBody(&_def);

        if (_body == nullptr) {
            return;
        }

        _body->CreateFixture(&_fixture);
    }

    if (_ep == nullptr) {
        _ep = dynamic_cast<objects::EntityObject*>(_parent);
        if (_ep == nullptr) {
            //TODO:
            return;
        }
    }

    auto position = _body->GetPosition();
    _ep->setPosition(glm::vec2{position.x, position.y});
    auto angle = _body->GetAngle();
    _ep->setRotation(angle);
}

void RigidBody::init(const typename resources::ConfigResource::JsonObject& data) {
    auto position = data["init-position"].GetObject();
    _def.position.Set(position["x"].GetFloat(), position["y"].GetFloat());
    _def.angle = data["init-angle"].GetFloat();
    _def.angularDamping = data["angular-damping"].GetFloat();
    _def.linearDamping = data["linear-damping"].GetFloat();
    _def.type = static_cast<b2BodyType>(data["rigid-type"].GetInt());
    _def.fixedRotation = data["fixed-rotation"].GetBool();
    _def.gravityScale = data["gravity-scale"].GetFloat();

    _fixture.density = data["density"].GetFloat();
    _fixture.friction = data["friction"].GetFloat();

    auto shape_data = data["shape"].GetObject();
    std::string shape_name = shape_data["name"].GetString();
    if (shape_name == "circle") {
        _shape = new CircleShape(shape_data["data"]);
    }
    else if (shape_name == "polygon") {
        _shape = new PolygonShape(shape_data["data"]);
    }

    _fixture.shape = _shape->shape;
}

RigidBody* RigidBody::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* body = memory::MemoryPool::getInstance()->create<RigidBody>();
    body->init(data);
    return body;
}

} // namespace ngind::physics