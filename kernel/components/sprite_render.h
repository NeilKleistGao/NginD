// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: sprite_render.h
// LAST MODIFY: 2020/11/1

// This file includes the sprite render component class. This component's parent
// must be Entity Object or the engine can't calculate the position, rotation and
// scale of texture.
// This file also includes the RTTR registration information. If you want to create
// object by using configuration files, you need provide a static method called create
// at least.

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

// The render component for sprite. You can create an instance both by new and by create
// method. Just draw a lovely sprite on your screen!
class SpriteRender : public RenderComponent {
public:
    // Constructor function
    SpriteRender();

    // Destructor function
    ~SpriteRender() override;

    // Copy behavior is not allowed. You can only maintain a pointer of a component
    SpriteRender(const SpriteRender&) = delete;
    // Copy behavior is not allowed. You can only maintain a pointer of a component
    SpriteRender& operator= (const SpriteRender&) = delete;

    // Update the state of this component. This function is inherited from UpdatableObject
    // @see objects/updatable_object.h
    void update(const float&) override;

    // Initialization function of this class used by configuration creating method. This function
    // is inherited from Component
    // @see components/component.h
    // params:
    //      const typename ConfigResource::JsonObject& : the configuration data
    //      this component initialization process requires.
    // return: void
    void init(const typename ConfigResource::JsonObject&) override;

    // Static function used by configuration creators. This function create a new instance of Sptite
    // Render.
    // params:
    //      const typename ConfigResource::JsonObject& : the configuration data
    //      this component initialization process requires.
    // return SpriteRender* : a pointer to the new instance
    static SpriteRender* create(const typename ConfigResource::JsonObject&);

    // Set a new image to this render. It will release the old one texture resource.
    // params:
    //      const std::string& : the image' filename
    // return: void
    void setImage(const std::string&);

    // Set a new image and new boundary to this render.
    // @see void setImage(const std::string&);
    // params:
    //      const std::string& : the image' filename
    //      const Vector2D& : the left bottom boundary
    //      const Vector2D& : the right top boundary
    // return: void
    void setImage(const std::string&, const Vector2D&, const Vector2D&);

    // Get the filename of the texture used in this render.
    // params: void
    // return std::string: the filename of texture
    inline std::string getImageName() {
        return _texture->getResourcePath();
    }

    // Set the boundary of texture
    // params:
    //      const Vector2D& lb : the left bottom boundary position
    //      const Vector2D& rt : the right top boundary position
    // return: void
    inline void setBound(const Vector2D& lb, const Vector2D& rt) {
        setLeftBottomBound(lb);
        setRightTopBound(rt);
    }

    // Set the left bottom boundary
    // @see inline void setBound(const Vector2D& lb, const Vector2D& rt)
    // params:
    //      const Vector2D& lb : the left bottom boundary position
    // return: void
    inline void setLeftBottomBound(const Vector2D& lb) {
        _lb = lb;
    }

    // Set the right top boundary
    // @see inline void setBound(const Vector2D& lb, const Vector2D& rt)
    // params:
    //      const Vector2D& rt : the right top boundary position
    // return: void
    inline void setRightTopBound(const Vector2D& rt) {
        _rt = rt;
    }

    // Get the left bottom boundary
    // params: void
    // return Vector2D : the left bottom boundary position
    inline Vector2D getLeftBottomBound() const {
        return _lb;
    }

    // Get the right top boundary
    // params: void
    // return Vector2D : the right top boundary position
    inline Vector2D getRightTopBound() const {
        return _rt;
    }

    // Set the color mask of this sprite. The default color is pure white(#FFFFFFFF).
    // params:
    //      const RGBA& color : the color
    // return: void
    inline void setColor(const RGBA& color) {
        _color = color;
    }

    // Get the color mask of this sprite. The default color is pure white(#FFFFFFFF).
    // params: void
    // return RGBA : the color//
    inline RGBA getColor() const {
        return _color;
    }

private:
    // the texture resource reference this sprite use
    TextureResource* _texture;

    // the boundary vectors
    Vector2D _lb, _rt;

    // mask color
    // default: #FFFFFFFF
    RGBA _color;

    // render command this sprite used
    QuadRenderCommand* _command;

    // vertex shader and fragment shader this sprite used
    ProgramResource* _program;

    // quad infomation
    Quad* _quad;

protected:
    // Create some render command and send them to the render queue in order to show
    // something on the screen. This method should be called in update. This method is
    // inherited from RenderComponent
    // @see components/render_component.h
    // params: void
    // return: void
    virtual void draw();
};

// RTTR Reflection Registration for SpriteRender
// properties:
//
// methods:
//      create -> static SpriteRender* create(const typename ConfigResource::JsonObject&);
RTTR_REGISTRATION {
    rttr::registration::class_<SpriteRender>("SpriteRender")
        .method("create", &SpriteRender::create);
}

} // namespace ngind

#endif //NGIND_SPRITE_RENDER_H
