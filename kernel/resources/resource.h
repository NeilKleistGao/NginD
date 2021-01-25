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

/// @file resource.h

#ifndef NGIND_RESOURCE_H
#define NGIND_RESOURCE_H

#include <iostream>

#include "memory/auto_collection_object.h"

namespace ngind::resources {

/**
 * Basic resource class. All kinds of resources must implement the load function.
 */
class Resource : public memory::AutoCollectionObject {
public:
    Resource() : memory::AutoCollectionObject() { };
    virtual ~Resource() = default;
    /**
     * Load resource.
     * @param name: name of resource
     */
    virtual void load(const std::string& name) = 0;

    /**
     * Get path of resource.
     * @return std::string, path of resource
     */
    inline const std::string getResourcePath() const {
        return _path;
    }

protected:
    /**
     * Path of resource.
     */
    std::string _path;
};

} // namespace ngind::resources

#endif //NGIND_RESOURCE_H
