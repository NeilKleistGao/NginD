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

/// @file memory_pool.h
/// @date 2020/9/20

/**
@brief This file includes the declaration of memory pool.
*/

#ifndef NGIND_MEMORY_POOL_H
#define NGIND_MEMORY_POOL_H

#include <set>
#include <memory>

#include "auto_collection_object.h"

namespace ngind {
/**
@class This class is used to manage auto collection object. You shouldn't
call this class. Inherit auto collection object instead.
*/
class MemoryPool {
public:
    /// @public
    /// @static
    /// @fn Get instance of memory pool
    /// @param void
    /// @return MemoryPool*, the instance
    static MemoryPool* getInstance();

    /// @public
    /// @static
    /// @fn Destroy the instance of memory pool
    /// @param void
    /// @return void
    static void destroyInstance();

    /// @public
    /// @fn Clear the memory pool
    /// @param void
    /// @return void
    void clear();

    /// @public
    /// @fn Insert a new auto collection object into memory pool
    /// @param AutoCollectionObject* object: the object to be inserted
    /// @return void
    inline void insert(AutoCollectionObject* object) {
        this->_pool.insert(object);
    }

    /// @public
    /// @fn Remove an object from memory pool
    /// @param AutoCollectionObject*: the object to be removed
    /// @return void
    void remove(AutoCollectionObject*);

private:
    /// @private
    /// @static
    /// @property The instance of memory pool
    static MemoryPool* _instance;

    /// @private
    /// @property A RB-Tree to manage objects
    std::set<AutoCollectionObject*> _pool;

    /// @private
    MemoryPool();

    /// @private
    ~MemoryPool();
};
} // namespace ngind

#endif //NGIND_MEMORY_POOL_H
