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

/// @file memory_pool.h

#ifndef NGIND_MEMORY_POOL_H
#define NGIND_MEMORY_POOL_H

#include <set>
#include <memory>
#include <vector>
#include <map>

#include "auto_collection_object.h"

namespace ngind::memory {
/**
 * This class is used to manage auto collection object. You shouldn't
 * call this class. Inherit auto collection object instead.
 */
class MemoryPool {
public:
    /**
     * Get instance of memory pool
     * @return MemoryPool*, the instance
     */
    static MemoryPool* getInstance();

    /**
     * Destroy the instance of memory pool
     */
    static void destroyInstance();

    /**
     * Clear the memory pool
     */
    void clear();

    /**
     * Remove an object from memory pool
     * @param obj: the object to be removed
     */
    inline void remove(AutoCollectionObject* obj) {
        obj->~AutoCollectionObject();
    }

    /**
     * Create an instance of given type.
     * @tparam T: type of instance
     * @return T*, the instance
     */
    template<typename T, std::enable_if_t<std::is_base_of_v<AutoCollectionObject, T>, int> N = 0>
    T* create() {
        auto p = allocate(sizeof(T));
        new(p) T();
        return reinterpret_cast<T*>(p);
    }

    /**
     * Create an instance of given type and params.
     * @tparam T: type of instance
     * @tparam P: type list of params
     * @param params: params
     * @return T*, the instance
     */
    template<typename T, typename ...P, std::enable_if_t<std::is_base_of_v<AutoCollectionObject, T>, int> N = 0>
    T* create(P... params) {
        auto p = allocate(sizeof(T));
        new(p) T(params...);
        return reinterpret_cast<T*>(p);
    }

private:
    /**
     * The instance of memory pool
     */
    static MemoryPool* _instance;

    /**
     * Should pool be cleaned.
     */
    bool _dirty;

    /**
     * Allocate a piece of memory from pool
     * @param size: size of memory piece
     * @return AutoCollectionObject*, new memory area
     */
    AutoCollectionObject* allocate(const size_t& size);

    /**
     * A RB-Tree to manage objects
     */
    std::map<size_t, std::vector<AutoCollectionObject*>> _pool;

    MemoryPool();

    ~MemoryPool();
};
} // namespace ngind::memory

#endif //NGIND_MEMORY_POOL_H
