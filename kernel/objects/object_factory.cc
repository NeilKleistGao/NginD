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

/// @file object_factory.cc

#include "object_factory.h"

#include "components/component_factory.h"
#include "prefab_factory.h"
#include "log/logger_factory.h"

namespace ngind::objects {

EntityObject* ObjectFactory::createEntityObject(const typename resources::ConfigResource::JsonObject& data) {
    try {
        if (data.HasMember("prefab")) {
            auto* entity = PrefabFactory::getInstance()->loadPrefab(data["prefab"].GetString());
            entity->init(data);
            return entity;
        }
        else {
            auto* entity = EntityObject::create(data);

            if (data.HasMember("components")) {
                auto components = data["components"].GetArray();
                for (const auto& com : components) {
                    components::Component* next = createComponent(com);
                    entity->addComponent(com["name"].GetString(), next);
                }
            }
            if (data.HasMember("children")) {
                auto children = data["children"].GetArray();
                for (const auto& child : children) {
                    EntityObject* next = createEntityObject(child);
                    entity->addChild(child["name"].GetString(), next);
                }
            }

            return entity;
        }
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create entity object in object factory.");
        logger->flush();
    }

    return nullptr;
}

components::Component* ObjectFactory::createComponent(const typename resources::ConfigResource::JsonObject& data) {
    try {
        auto factory = components::ComponentFactory::getInstance();
        components::Component* com = factory->create(data["type"].GetString(), data);
        return com;
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create component in object factory.");
        logger->flush();
    }

    return nullptr;
}

} // namespace ngind::objects
