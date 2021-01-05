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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file: sprite_render.h

#ifndef NGIND_SPRITE_RENDERER_H
#define NGIND_SPRITE_RENDERER_H

#include <string>

#include "rendering/render_command.h"
#include "render_component.h"
#include "resources/texture_resource.h"
#include "math/vector.h"
#include "rendering/rgba.h"
#include "rendering/program.h"
#include "rendering/quad.h"
#include "objects/entity_object.h"
#include "resources/program_resource.h"

#include "rttr/registration.h"

namespace ngind::components {
using Vector2D = math::Vector2D;
/**
 * The renderer component for sprite. You can create an instance both by new and by create
 * method. Just draw a lovely sprite on your screen!
 */
class SpriteRenderer : public RenderComponent {
public:
    SpriteRenderer();
    ~SpriteRenderer() override;
    SpriteRenderer(const SpriteRenderer&) = delete;
    SpriteRenderer& operator= (const SpriteRenderer&) = delete;

    /**
     * @see objects/updatable_object.h
     */
    void update(const float& delta) override;

    /**
     * Initialization function of this class used by configuration creating method. This function
     * is inherited from Component
     * @param data: the configuration data this component initialization process requires.
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    /**
     * Static function used by configuration creators. This function create a new instance of Sprite
     * @param data: the configuration data this component initialization process requires.
     * @return SpriteRenderer*, a pointer to the new instance.
     */
    static SpriteRenderer* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Set a new image to this rendering. It will release the old one texture resource.
     * @param filename: the image' filename
     */
    void setImage(const std::string& filename);

    /**
     * Set a new image and new boundary to this rendering.
     * @param filename: the image' filename
     * @param lb: the left bottom boundary
     * @param rt: the right top boundary
     */
    void setImage(const std::string& filename, const Vector2D& lb, const Vector2D& rt);

    /**
     * Get the filename of the texture used in this rendering.
     * @return std::string, the filename of texture
     */
    inline std::string getImageName() {
        return _texture->getResourcePath();
    }

    /**
     * Set the boundary of texture.
     * @param lb: the left bottom boundary position
     * @param rt: the right top boundary position
     */
    inline void setBound(const Vector2D& lb, const Vector2D& rt) {
        setLeftBottomBound(lb);
        setRightTopBound(rt);
    }

    /**
     * Set the left bottom boundary.
     * @param lb: the left bottom boundary position
     */
    inline void setLeftBottomBound(const Vector2D& lb) {
        _lb = lb;
    }

    /**
     * Set the right top boundary.
     * @param rt: the right top boundary position
     */
    inline void setRightTopBound(const Vector2D& rt) {
        _rt = rt;
    }

    /**
     * Get the left bottom boundary.
     * @return Vector2D, the left bottom boundary position
     */
    inline Vector2D getLeftBottomBound() const {
        return _lb;
    }

    /**
     * Get the right top boundary.
     * @return Vector2D, the right top boundary position
     */
    inline Vector2D getRightTopBound() const {
        return _rt;
    }

    /**
     * Set the color mask of this sprite. The default color is pure white(#FFFFFFFF).
     * @param color: the color
     */
    inline void setColor(const rendering::RGBA& color) {
        _color = color;
    }

    /**
     * Get the color mask of this sprite. The default color is pure white(#FFFFFFFF).
     * @return RGBA, the color
     */
    inline rendering::RGBA getColor() const {
        return _color;
    }

private:
    /**
     * The texture resource reference this sprite use.
     */
    resources::TextureResource* _texture;

    /**
     * The boundary vectors.
     */
    Vector2D _lb, _rt;

    /**
     * Mask color.
     */
    rendering::RGBA _color;

    /**
     * Render command this sprite used.
     */
    rendering::QuadRenderCommand* _command;

    /**
     * Vertex shader and fragment shader this sprite used.
     */
    resources::ProgramResource* _program;

    /**
     * Quad information.
     */
    rendering::Quad* _quad;

protected:
    /**
     * @see components/render_component.h
     */
    virtual void draw();
};

RTTR_REGISTRATION {
    rttr::registration::class_<SpriteRenderer>("SpriteRenderer")
            .method("create", &SpriteRenderer::create);
}
} // namespace ngind::components

#endif //NGIND_SPRITE_RENDERER_H
