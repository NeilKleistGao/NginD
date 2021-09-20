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

/// @file object_factory.h

#ifndef NGIND_OBJECT_FACTORY_H
#define NGIND_OBJECT_FACTORY_H

#include "entity_object.h"
#include "components/component.h"

namespace ngind::objects {
/**
 * Factory providing interface to create objects and components
 */
class ObjectFactory {
public:
    /**
     * Create an entity object with given config data
     * @param data: given config data
     * @return EntityObject*, a new entity object
     */
    static EntityObject* createEntityObject(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Create a component with given config data
     * @param data: given config data
     * @return components::Component*, a new component
     */
    static components::Component* createComponent(const typename resources::ConfigResource::JsonObject& data);
};

} // namespace ngind::objects

#endif //NGIND_OBJECT_FACTORY_H
