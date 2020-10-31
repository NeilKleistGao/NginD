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
// LAST MODIFY: 2020/10/31

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

#include "rttr/registration.h"

namespace ngind {

class SpriteRender : public RenderComponent {
public:
    SpriteRender();
    ~SpriteRender() override;
    SpriteRender(const SpriteRender&) = delete;
    SpriteRender& operator= (const SpriteRender&) = delete;

    void update(const float&) override;
    void init(const typename ConfigResource::JsonObject&) override;
    static SpriteRender* create(const typename ConfigResource::JsonObject&);

    void setImage(const std::string&);
    void setImage(const std::string&, const Vector2D&, const Vector2D&);

    inline std::string getImageName() {
        return _texture->getResourcePath();
    }

    inline void setBound(const Vector2D& lb, const Vector2D& rt) {
        setLeftBottomBound(lb);
        setRightTopBound(rt);
    }

    inline void setLeftBottomBound(const Vector2D& lb) {
        _lb = lb;
    }

    inline void setRightTopBound(const Vector2D& rt) {
        _rt = rt;
    }

    inline Vector2D getLeftBottomBound() const {
        return _lb;
    }

    inline Vector2D getRightTopBound() const {
        return _rt;
    }

    inline void setColor(const RGBA& color) {
        _color = color;
    }

    inline RGBA getColor() const {
        return _color;
    }

private:
    TextureResource* _texture;
    Vector2D _lb, _rt;
    RGBA _color;
    QuadRenderCommand* _command;
    Program* _program;
    Quad* _quad;

protected:
    virtual void draw();
};

RTTR_REGISTRATION {
    rttr::registration::class_<SpriteRender>("SpriteRender")
        .method("create", &SpriteRender::create);
}

} // namespace ngind

#endif //NGIND_SPRITE_RENDER_H
