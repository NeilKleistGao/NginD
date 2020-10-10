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
// FILENAME: resources_manager.h
// LAST MODIFY: 2020/10/3

#ifndef NGIND_RESOURCES_MANAGER_H
#define NGIND_RESOURCES_MANAGER_H

#include <map>

#include "resource.h"

namespace ngind {

class ResourcesManager {
public:
    static ResourcesManager* getInstance();
    static void destroyInstance();

    const static std::string CONFIG_RESOURCES_PATH;
    const static std::string IMAGE_RESOURCES_PATH;
    const static std::string TEXT_RESOURCES_PATH;
    //TODO:

    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Resource, Type>, int> N = 0>
    void preLoad(const std::string&) {
        //TODO:
    }

    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Resource, Type>, int> N = 0>
    Type* load(const std::string& path) {
        if (this->_resources.find(path) != this->_resources.end()) {
            this->_resources[path]->addReference();
            return this->_resources[path];
        }

        //TODO:
    }

    void release(const std::string&);

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager(ResourcesManager&&) = delete;
private:
    ResourcesManager() = default;
    ~ResourcesManager() = default;

    static ResourcesManager* _instance;
    std::map<std::string, Resource*> _resources;
};

} // namespace ngind

#endif //NGIND_RESOURCES_MANAGER_H
