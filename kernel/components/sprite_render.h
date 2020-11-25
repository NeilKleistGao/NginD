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

/// @file: sprite_render.h
/// @date: 2020/11/1

/**
@brief
    This file includes the sprite render component class. This component's parent
must be Entity Object or the engine can't calculate the position, rotation and
scale of texture.
    This file also includes the RTTR registration information. If you want to create
object by using configuration files, you need provide a static method called create
at least.
 */

#ifndef NGIND_SPRITE_RENDER_H
#define NGIND_SPRITE_RENDER_H

#include <string>

#include "render/render_command.h"
#include "render_component.h"
#include "resources/texture_resource.h"
#include "math/vector.h"
#include "render/rgba.h"
#include "render/program.h"
#include "render/quad.h"
#include "objects/entity_object.h"
#include "resources/program_resource.h"

#include "rttr/registration.h"

namespace ngind {

/**
@class
    The render component for sprite. You can create an instance both by new and by create
method. Just draw a lovely sprite on your screen!

@see kernel/components/render_compoent.h
*/
class SpriteRender : public RenderComponent {
public:
    SpriteRender();
    ~SpriteRender() override;
    SpriteRender(const SpriteRender&) = delete;
    SpriteRender& operator= (const SpriteRender&) = delete;

    /// @fn Update the state of this component. This function is inherited from UpdatableObject
    /// @see objects/updatable_object.h
    void update(const float&) override;

    /// @fn Initialization function of this class used by configuration creating method. This function
    /// is inherited from Component
    /// @see components/component.h
    /// @param const typename ConfigResource::JsonObject& : the configuration data
    /// this component initialization process requires.
    /// @return void
    void init(const typename ConfigResource::JsonObject&) override;

    /// @static
    /// @fn Static function used by configuration creators. This function create a new instance of Sptite
    /// Render.
    /// @param const typename ConfigResource::JsonObject& : the configuration data
    /// this component initialization process requires.
    /// @return SpriteRender*, a pointer to the new instance
    static SpriteRender* create(const typename ConfigResource::JsonObject&);

    /// @fn Set a new image to this render. It will release the old one texture resource.
    /// @param const std::string& : the image' filename
    /// @return void
    void setImage(const std::string&);

    /// @fn Set a new image and new boundary to this render.
    /// @see void setImage(const std::string&);
    /// @param const std::string& : the image' filename
    /// @param const Vector2D& : the left bottom boundary
    /// @param const Vector2D& : the right top boundary
    /// @return void
    void setImage(const std::string&, const Vector2D&, const Vector2D&);

    /// @fn Get the filename of the texture used in this render.
    /// @param void
    /// @return std::string, the filename of texture
    inline std::string getImageName() {
        return _texture->getResourcePath();
    }

    /// @fn Set the boundary of texture
    /// @param const Vector2D& lb : the left bottom boundary position
    /// @param const Vector2D& rt : the right top boundary position
    /// @return void
    inline void setBound(const Vector2D& lb, const Vector2D& rt) {
        setLeftBottomBound(lb);
        setRightTopBound(rt);
    }

    /// @fn Set the left bottom boundary
    /// @see inline void setBound(const Vector2D& lb, const Vector2D& rt)
    /// @param const Vector2D& lb : the left bottom boundary position
    /// @return void
    inline void setLeftBottomBound(const Vector2D& lb) {
        _lb = lb;
    }

    /// @fn Set the right top boundary
    /// @see inline void setBound(const Vector2D& lb, const Vector2D& rt)
    /// @param const Vector2D& rt : the right top boundary position
    /// @return void
    inline void setRightTopBound(const Vector2D& rt) {
        _rt = rt;
    }

    /// @fn Get the left bottom boundary
    /// @param void
    /// @return Vector2D, the left bottom boundary position
    inline Vector2D getLeftBottomBound() const {
        return _lb;
    }

    /// @fn Get the right top boundary
    /// @param
    /// @return Vector2D, the right top boundary position
    inline Vector2D getRightTopBound() const {
        return _rt;
    }

    /// @fn Set the color mask of this sprite. The default color is pure white(#FFFFFFFF).
    /// @param const RGBA& color : the color
    /// @return void
    inline void setColor(const RGBA& color) {
        _color = color;
    }

    /// @fn Get the color mask of this sprite. The default color is pure white(#FFFFFFFF).
    /// @param void
    /// @return RGBA, the color//
    inline RGBA getColor() const {
        return _color;
    }

private:
    /// @property The texture resource reference this sprite use
    TextureResource* _texture;

    /// @property The boundary vectors
    Vector2D _lb, _rt;

    /// @property Mask color
    RGBA _color;

    /// @property Render command this sprite used
    QuadRenderCommand* _command;

    /// @property Vertex shader and fragment shader this sprite used
    ProgramResource* _program;

    /// @property Quad information
    Quad* _quad;

protected:
    /// @fn Create some render command and send them to the render queue in order to show
    /// something on the screen. This method should be called in update. This method is
    /// inherited from RenderComponent
    /// @see components/render_component.h
    /// @param void
    /// @return void
    virtual void draw();
};

RTTR_REGISTRATION {
    rttr::registration::class_<SpriteRender>("SpriteRender")
        .method("create", &SpriteRender::create);
}

} // namespace ngind

#endif //NGIND_SPRITE_RENDER_H
