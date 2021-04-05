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

/// @file rigid_body.h

#ifndef NGIND_RIGID_BODY_H
#define NGIND_RIGID_BODY_H

#include "kernel/components/component.h"
#include "box2d/box2d.h"
#include "kernel/components/component_factory.h"
#include "kernel/script/lua_registration.h"
#include "kernel/objects/entity_object.h"
#include "physics_shape.h"

namespace ngind::physics {
class RigidBody : public components::Component {
public:
    RigidBody();
    ~RigidBody() override;

    /**
     * @see objects/updatable_object.h
     */
    void update(const float& delta) override;

    /**
     * Initialization function of this class used by configuration creating method. This function
     * is inherited from Component
     * @param data: the configuration data this component initialization process requires.
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    static RigidBody* create(const typename resources::ConfigResource::JsonObject& data);

    inline b2Body* getBody() const {
        return _body;
    }
private:
    b2BodyDef _def;
    b2FixtureDef _fixture;
    PhysicsShape* _shape;
    b2Body* _body;

    objects::EntityObject* _ep;
};

NGIND_LUA_BRIDGE_REGISTRATION(RigidBody) {
    components::ComponentFactory::getInstance()->registerComponent<RigidBody>("RigidBody");
}

} // namespace ngind::physics

#endif //NGIND_RIGID_BODY_H
