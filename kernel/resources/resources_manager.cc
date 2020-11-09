/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// FILENAME: resources_manager.cc
// LAST MODIFY: 2020/10/11

#include "resources_manager.h"

namespace ngind {
ResourcesManager* ResourcesManager::_instance = nullptr;

ResourcesManager* ResourcesManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) ResourcesManager();
    }

    return _instance;
}

void ResourcesManager::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void ResourcesManager::release(const std::string& path) {
    if (this->_resources.find(path) == this->_resources.end()) {
        return;
    }

    this->_resources[path]->removeReference();
    if (this->_resources[path]->getSustain() == 0) {
        delete this->_resources[path];
        this-_resources.erase(path);
    }
}

} // namespace ngind