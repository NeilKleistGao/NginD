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

/// @file world.h

#include "world.h"

#include "resources/resources_manager.h"
#include "entity_object.h"
#include "components/component_factory.h"
#include "memory/memory_pool.h"
#include "rendering/camera.h"
#include "ui/event_system.h"

namespace ngind::objects {

World::World(std::string name) : Object(), _name(std::move(name)), _config(nullptr), _background_color() {
    _config = resources::ResourcesManager::getInstance()->load<resources::ConfigResource>("worlds/world-" + _name + ".json");
    _background_color = rendering::Color(_config->getDocument()["background-color"].GetString());

    ui::EventSystem::getInstance()->init();

    loadObjects();

    glm::vec2 center;
    auto camera = _config->getDocument()["camera"].GetObject();
    center.x = camera["x"].GetInt(); center.y = camera["y"].GetInt();
    rendering::Camera::getInstance()->moveTo(center);
}

World::World(resources::ConfigResource* config) : Object(), _name(), _config(config), _background_color() {
    _name = _config->getDocument()["world-name"].GetString();
    _background_color = rendering::Color(_config->getDocument()["background-color"].GetString());

    ui::EventSystem::getInstance()->init();

    loadObjects();

    glm::vec2 center;
    auto camera = _config->getDocument()["camera"].GetObject();
    center.x = camera["x"].GetInt(); center.y = camera["y"].GetInt();
    rendering::Camera::getInstance()->moveTo(center);
}

void World::update(const float& delta) {
    Object::update(delta);
}

void World::loadObjects() {
    auto children = _config->getDocument()["children"].GetArray();

    for (const auto& child : children) {
        EntityObject* obj = generateObject(this, child);
        this->addChild(child["name"].GetString(), obj);
    }

    auto components = _config->getDocument()["components"].GetArray();

    for (const auto& component : components) {
        auto com = generateComponent(component);
        this->addComponent(component["name"].GetString(), com);
    }
}

EntityObject* World::generateObject(Object* self, const typename resources::ConfigResource::JsonObject& data) {
    auto* entity = memory::MemoryPool::getInstance()->create<EntityObject>();
    entity->setID(data["id"].GetInt());
    auto position = data["position"].GetObject();
    entity->setPositionX(position["x"].GetFloat());
    entity->setPositionY(position["y"].GetFloat());

    auto scale = data["scale"].GetObject();
    entity->setScaleX(scale["x"].GetFloat());
    entity->setScaleY(scale["y"].GetFloat());

    entity->setRotation(data["rotate"].GetFloat());
    entity->setZOrder(data["z-order"].GetInt());

    if (data.HasMember("components")) {
        auto components = data["components"].GetArray();
        for (const auto& com : components) {
            components::Component* next = generateComponent(com);
            entity->addComponent(com["name"].GetString(), next);
        }
    }
    if (data.HasMember("children")) {
        auto children = data["children"].GetArray();
        for (const auto& child : children) {
            EntityObject* next = generateObject(entity, child);
            self->addChild(child["name"].GetString(), next);
        }
    }

    _all_children[data["id"].GetInt()] = entity;
    return entity;
}

components::Component* World::generateComponent(const typename resources::ConfigResource::JsonObject& data) {
    auto factory = components::ComponentFactory::getInstance();
    components::Component* com = factory->create(data["type"].GetString(), data);
    return com;
}

EntityObject* World::getChildByID(const int& id) {
    if (_all_children.find(id) == _all_children.end()) {
        return nullptr;
    }

    return _all_children[id];
}

void World::dump(rapidjson::Document& document) const {
    document["world-name"].SetString(_name.c_str(), _name.length());
    auto camera = rendering::Camera::getInstance();
    auto camera_pos = camera->getCameraPosition();

    auto& camera_data = document["camera"].SetObject();
    camera_data["x"].SetInt(camera_pos.x);
    camera_data["y"].SetInt(camera_pos.y);

    Object::dump(document);
}

} // namespace ngind::objects