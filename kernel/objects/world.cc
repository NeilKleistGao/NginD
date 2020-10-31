// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: world.h
// LAST MODIFY: 2020/10/31

#include "world.h"

#include "resources/resources_manager.h"
#include "entity_object.h"
#include "rttr/registration.h"

namespace ngind {

World::World(std::string name) : _name(std::move(name)), _config(nullptr), _background_color() {
    _config = ResourcesManager::getInstance()->load<ConfigResource>("world-" + _name + ".json");
    _background_color = RGBA(_config->getDocument()["background-color"].GetString());

    loadObjects();
}

void World::update(const float& delta) {
    Object::update(delta);
}

void World::loadObjects() {
    auto children = _config->getDocument()["children"].GetArray();

    for (const auto& child : children) {
        Object* obj = generateObject(this, child);
        this->addChild(child["name"].GetString(), obj);
    }
}

Object* World::generateObject(Object* self, const typename ConfigResource::JsonObject& data) {
    Object* object = nullptr;
    if (std::string(data["type"].GetString()) == "entity") {
        object = new EntityObject();
        auto* entity = static_cast<EntityObject*>(object);

        auto position = data["position"].GetObject();
        entity->setPositionX(position["x"].GetFloat());
        entity->setPositionY(position["y"].GetFloat());

        auto scale = data["scale"].GetObject();
        entity->setScaleX(scale["x"].GetFloat());
        entity->setScaleY(scale["y"].GetFloat());

        entity->setRotation(data["rotate"].GetFloat());
        entity->setZOrder(data["z-order"].GetInt());
    }
    else {
        object = new Object();
    }

    if (data.HasMember("components")) {
        auto components = data["components"].GetArray();
        for (const auto& com : components) {
            Component* next = generateComponent(com);
            object->addComponent(com["name"].GetString(), next);
        }
    }
    if (data.HasMember("children")) {
        auto children = data["children"].GetArray();
        for (const auto& child : children) {
            Object* next = generateObject(object, child);
            self->addChild(child["name"].GetString(), next);
        }
    }

    return object;
}

Component* World::generateComponent(const typename ConfigResource::JsonObject& data) {
    rttr::type type = rttr::type::get_by_name(data["name"].GetString());
    rttr::variant temp = type.create();
    rttr::method create_func = type.get_method("create");
    rttr::variant var = create_func.invoke(temp, data);

    Component* com = var.get_value<Component*>();
    com->init(data);
    return com;
}

} // namespace ngind