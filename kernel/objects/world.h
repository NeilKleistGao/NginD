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

#include "object.h"
#include "components/component.h"
#include "resources/config_resource.h"
#include "rendering/rgba.h"

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
     * Get name of this world
     * @return std::string, name of this world
     */
    inline std::string getName() {
        return _name;
    }

    /**
     * Get the background color of this world
     * @return RGBA, the background color
     */
    inline rendering::RGBA getBackgroundColor() const {
        return _background_color;
    }

    /**
     * Set the background color of this world
     * @param color: the background color
     */
    inline void setBackgroundColor(const rendering::RGBA& color) {
        _background_color = color;
    }

    /**
     * Set the background color of this world
     * @param code: the code of background color
     */
    inline void setBackgroundColor(const std::string& code) {
        _background_color = rendering::RGBA{code};
    }

    /**
     * @see kernel/objects/updatable_object.h
     */
    void update(const float&) override;
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
    rendering::RGBA _background_color;

    /**
     * Load children objects using config file
     */
    void loadObjects();

    /**
     * Generate a new object.
     * @param self: parent object
     * @param data: part of config file
     * @return Object*, the new object
     */
    Object* generateObject(Object* self, const typename resources::ConfigResource::JsonObject& data);

    /**
     * Generate a new component.
     * @param data: part of config file
     * @return Object*, the new component
     */
    components::Component* generateComponent(const typename resources::ConfigResource::JsonObject& data);
};

} // namespace ngind::objects

#endif //NGIND_WORLD_H
