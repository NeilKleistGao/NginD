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

/// @file resources_manager.h

#ifndef NGIND_RESOURCES_MANAGER_H
#define NGIND_RESOURCES_MANAGER_H

#include <map>
#include <functional>

#include "resource.h"
#include "memory/memory_pool.h"

namespace ngind::resources {

/**
 * Manager of all kinds of resources.
 */
class ResourcesManager {
public:
    /**
     * Get the instance of resources manager.
     * @return ResourcesManager*, the instance of resources manager
     */
    static ResourcesManager* getInstance();

    /**
     * Destory the instance of resources manager.
     */
    static void destroyInstance();

    /**
     * Load resource by path.
     * @tparam Type: specific type of resource
     * @param path: the path of resource
     * @return Type*, the resource object
     */
    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Resource, Type>, int> N = 0>
    Type* load(const std::string& path) {
        if (this->_resources.find(path) != this->_resources.end()) {
            this->_resources[path]->addReference();
            return static_cast<Type*>(this->_resources[path]);
        }

        this->_resources[path] = memory::MemoryPool::getInstance()->create<Type>();
        if (this->_resources[path] == nullptr) {
            //TODO: Exception Detect
        }
        else {
            this->_resources[path]->load(path);
            this->_resources[path]->addReference();
        }

        return static_cast<Type*>(this->_resources[path]);
    }

    /**
     * Release resource by path
     * @param path: path of resource
     */
    void release(const std::string& path);

    inline void release(Resource* resource) {
        this->release(resource->getResourcePath());
    }

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager(ResourcesManager&&) = delete;
private:
    ResourcesManager() = default;
    ~ResourcesManager() = default;

    /**
     * The instance of resources manager
     */
    static ResourcesManager* _instance;

    /**
     * The RB-Tree storing mapping between paths and resources.
     */
    std::map<std::string, Resource*> _resources;
};

} // namespace ngind::resources

#endif //NGIND_RESOURCES_MANAGER_H
