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
    auto tbm = _pool.end();
    for (auto it = _pool.begin(); it != _pool.end(); ++it) {
        if (tbm != _pool.end()) {
            _pool.erase(tbm);
            tbm = _pool.end();
        }

        auto temp = *it;
        if (temp->getSustain() == 0) {
            temp->~AutoCollectionObject();
            ::operator delete(temp);
            *it = nullptr;
            tbm = it;
        }
    }

    if (tbm != _pool.end()) {
        _pool.erase(tbm);
    }
}

MemoryPool::MemoryPool() : _dirty(false) {
}

MemoryPool::~MemoryPool() {
    for (auto* item : _pool) {
        item->~AutoCollectionObject();
        ::operator delete(item);
    }

    _pool.clear();
}

AutoCollectionObject* MemoryPool::allocate(const size_t& size) {
    auto p = ::operator new(size);
    std::memset(p, 0, size);
    auto ao = reinterpret_cast<AutoCollectionObject*>(p);
    _pool.push_back(ao);
    return ao;
}

} // namespace ngind