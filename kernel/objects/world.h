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

/// @file world.h
/// @date 2020/10/31

/**
@brief This file define the world object that contains everything in game.
*/

#ifndef NGIND_WORLD_H
#define NGIND_WORLD_H

#include <string>

#include "object.h"
#include "components/component.h"
#include "resources/config_resource.h"
#include "render/rgba.h"

namespace ngind {

/**
@class
    This class contains everything in game. It should be set by config
file.
*/
class World : public Object {
public:
    /// @public
    /// @param std::string: name of this world
    explicit World(std::string);

    /// @public
    /// @fn Get name of this world
    /// @param void
    /// @return std::string, name of this world
    inline std::string getName() {
        return _name;
    }

    /// @public
    /// @fn Get the background color of this world
    /// @param void
    /// @return RGBA, the background color
    inline RGBA getBackgroundColor() const {
        return _background_color;
    }

    /// @public
    /// @fn Set the background color of this world
    /// @param const RGBA& color: the background color
    /// @return void
    inline void setBackgroundColor(const RGBA& color) {
        _background_color = color;
    }

    /// @public
    /// @fn Set the background color of this world
    /// @param const std::string& code: the code of background color
    /// @return void
    inline void setBackgroundColor(const std::string& code) {
        _background_color = RGBA{code};
    }

    /// @see kernel/objects/updatable_object.h
    void update(const float&) override;
private:
    /// @private
    /// @property The name of this world
    std::string _name;

    /// @private
    /// @property The resource reference of config file
    ConfigResource* _config;

    /// @private
    /// @property Background color of this world
    RGBA _background_color;

    /// @private
    /// @fn Load children objects using config file
    /// @param void
    /// @return void
    void loadObjects();

    /// @private
    /// @fn Generate a new object.
    /// @param Object*: parent object
    /// @param const typename ConfigResource::JsonObject&: part of config file
    /// @return Object*, the new object
    Object* generateObject(Object*, const typename ConfigResource::JsonObject&);

    /// @private
    /// @fn Generate a new component.
    /// @param Object*: parent object
    /// @param const typename ConfigResource::JsonObject&: part of config file
    /// @return Object*, the new component
    components::Component* generateComponent(const typename ConfigResource::JsonObject&);
};

} // namespace ngind

#endif //NGIND_WORLD_H
