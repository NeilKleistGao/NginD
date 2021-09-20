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

/// @file prefab_factory.h

#ifndef NGIND_PREFAB_FACTORY_H
#define NGIND_PREFAB_FACTORY_H

#include <map>

#include "entity_object.h"
#include "script/lua_registration.h"

namespace ngind::objects {
/**
 * Factory allowing users instantiate object from prefab.
 */
class PrefabFactory {
public:
    /**
     * Get the unique instance of factory. If it does not exist, this function will create one.
     * @return PrefabFactory*, the unique instance
     */
    static PrefabFactory* getInstance();

    /**
     * Destroy the unique instance if it exists.
     */
    static void destroyInstance();

    PrefabFactory(const PrefabFactory&) = delete;
    PrefabFactory& operator= (const PrefabFactory&) = delete;

    /**
     * Load and instantiate a prefab.
     * @param name: name of prefab
     * @return EntityObject*, the instance of prefab
     */
    EntityObject* loadPrefab(const std::string& name);

    /**
     * Remove all prefab from the cache
     */
    void clearCache();
private:
    /**
     * The unique instance.
     */
    static PrefabFactory* _instance;

    /**
     * The prefabs cache.
     */
    std::map<std::string, resources::ConfigResource*> _cache;

    PrefabFactory() = default;
    ~PrefabFactory() {
        clearCache();
    }
};

NGIND_LUA_BRIDGE_REGISTRATION(PrefabFactory) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<PrefabFactory>("PrefabFactory")
                .addStaticFunction("getInstance", &PrefabFactory::getInstance)
                .addFunction("loadPrefab", &PrefabFactory::loadPrefab)
            .endClass()
        .endNamespace();

    luabridge::setGlobal(script::LuaState::getInstance()->getState(), PrefabFactory::getInstance(), "PrefabFactory");
}

} //namespace ngind::objects

#endif //NGIND_PREFAB_FACTORY_H
