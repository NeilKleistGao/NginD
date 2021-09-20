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

/// @file world.h

#ifndef NGIND_WORLD_H
#define NGIND_WORLD_H

#include <string>
#include <unordered_map>

#include "object.h"
#include "components/component.h"
#include "resources/config_resource.h"
#include "rendering/color.h"

namespace ngind::objects {

/**
 * This class contains everything in game. It should be set by config
 * file.
 */
class World : public Object {
public:
    /**
     * @param name: name of this world
     */
    explicit World(std::string name);

    /**
     * @param config: the configure data of this world
     */
    explicit World(resources::ConfigResource* config);

    ~World() override;

    /**
     * Get name of this world
     * @return std::string, name of this world
     */
    inline std::string getName() {
        return _name;
    }

    /**
     * Get the background color of this world
     * @return Color, the background color
     */
    inline rendering::Color getBackgroundColor() const {
        return _background_color;
    }

    /**
     * Set the background color of this world
     * @param color: the background color
     */
    inline void setBackgroundColor(const rendering::Color& color) {
        _background_color = color;
    }

    /**
     * Set the background color of this world
     * @param code: the code of background color
     */
    inline void setBackgroundColor(const std::string& code) {
        _background_color = rendering::Color{code};
    }

    /**
     * @see kernel/objects/updatable_object.h
     */
    void update(const float&) override;

    /**
     * Find entity object by given id
     * @param id: the given id
     * @return EntityObject*, the object with given id
     */
    EntityObject* getChildByID(const int& id);

    /**
     * Add an entity object to the world.
     * @param id: id of the object
     * @param entity: the object
     */
    inline void registerEntity(int id, EntityObject* entity) {
        _all_children[id] = entity;
    }

    /**
     * Remove an entity object from the world.
     * @param id: id of the entity object
     */
    void unregisterEntity(int id);

    /**
     * Get the number of children.
     * @return size_t, the number of children
     */
    inline size_t getChildrenNumber() const {
        return _all_children.size();
    }

    /**
    * Load children objects using config file
    */
    void loadObjects();
private:
    /**
     * The name of this world
     */
    std::string _name;

    /**
     * The resource reference of config file
     */
    resources::ConfigResource* _config;

    /**
     * Background color of this world
     */
    rendering::Color _background_color;

    /**
     * Table containing all entity objects in the world
     */
    std::unordered_map<int, EntityObject*> _all_children;
};

} // namespace ngind::objects

#endif //NGIND_WORLD_H
