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
    for (auto& [size, list] : _open_pool) {
        for (auto* item : list) {
            ::operator delete(item);
        }

        list.clear();
    }

    for (auto& [size, list] : _closed_pool) {
        auto prev = list.end();
        for (auto it = list.begin(); it != list.end(); it++) {
            auto temp = *it;
            if (temp->getSustain() == 0) {
                temp->~AutoCollectionObject();
                _open_pool[size].push_back(temp);
                list.erase(it);

                if (prev == list.end()) {
                    it = list.begin();
                }
                else {
                    it = prev;
                }
            }

            prev = it;
        }
    }
}

MemoryPool::MemoryPool() {
}

MemoryPool::~MemoryPool() {
    for (auto& [size, list] : _open_pool) {
        for (auto* item : list) {
            ::operator delete(item);
        }

        list.clear();
    }

    for (auto& [size, list] : _closed_pool) {
        for (auto* item : list) {
            delete item;
        }

        list.clear();
    }

    _open_pool.clear();
    _closed_pool.clear();
}

AutoCollectionObject* MemoryPool::allocate(const size_t& size) {
    if (_closed_pool.find(size) == _closed_pool.end()) {
        _closed_pool[size] = std::list<AutoCollectionObject*>{};
        _open_pool[size] = std::list<AutoCollectionObject*>{};
    }

    if (_open_pool[size].empty()) {
        auto p = reinterpret_cast<AutoCollectionObject*>(::operator new(size));
        std::memset(p, 0, size);
        _closed_pool[size].push_back(p);
        return p;
    }
    else {
        auto p = _open_pool[size].front();
        _open_pool[size].pop_front();
        std::memset(p, 0, size);
        _closed_pool[size].push_back(p);
        return p;
    }
}

} // namespace ngind