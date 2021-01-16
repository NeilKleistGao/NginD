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

/// @file memory_pool.cc

#include "memory_pool.h"

#include <iostream>
#include <cstring>

namespace ngind::memory {
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
    if (!_dirty) {
        return;
    }

    std::vector<std::vector<AutoCollectionObject*>::iterator> _todo;
    for (auto& [size, vec] : _pool) {
        for (auto it = vec.begin(); it != vec.end(); it++) {
            int sustain = (*it)->getSustain();
            if (sustain == 0) {
                _todo.push_back(it);
            }
            else if (sustain == 1) {
                (*it)->removeReference();
            }
        }

        for (auto& p : _todo) {
            AutoCollectionObject* temp = *p;
            ::operator delete(temp);
            vec.erase(p);
        }
        _todo.clear();
    }

    _dirty = false;
}

MemoryPool::MemoryPool() : _dirty(false) {
    this->_pool.clear();
}

MemoryPool::~MemoryPool() {
    for (auto& [size, vec] : _pool) {
        for (auto& p : vec) {
            ::operator delete(p);
        }

        vec.clear();
    }

    _pool.clear();
}

AutoCollectionObject* MemoryPool::allocate(const size_t& size) {
    if (_pool.find(size) == _pool.end()) {
        _pool[size] = std::vector<AutoCollectionObject*>{};
    }

    _dirty = true;

    for (auto& p : _pool[size]) {
        if (p->getSustain() == 0) {
            std::memset(p, 0, size);
            return p;
        }
    }

    auto p = reinterpret_cast<AutoCollectionObject*>(::operator new(size));
    std::memset(p, 0, size);
    _pool[size].push_back(p);
    return p;
}

} // namespace ngind