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

/// @file memory_pool.cc
/// @date 2020/9/20

/// @brief This file includes the implementation of memory pool.

#include "memory_pool.h"

#include <iostream>

namespace ngind {
MemoryPool* MemoryPool::_instance = nullptr;

MemoryPool* MemoryPool::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) MemoryPool();
    }

    return _instance;
}

void MemoryPool::destroyInstance() {
    delete _instance;
    _instance = nullptr;
}

void MemoryPool::clear() {
    for (auto it : this->_pool) {
        delete it;
        it = nullptr;
    }

    this->_pool.clear();
}

MemoryPool::MemoryPool() {
    this->_pool.clear();
}

MemoryPool::~MemoryPool() {
    this->clear();
}

void MemoryPool::remove(AutoCollectionObject* obj) {
    auto it = this->_pool.find(obj);
    if (it != this->_pool.end()) {
        this->_pool.erase(it);
    }
}

} // namespace ngind