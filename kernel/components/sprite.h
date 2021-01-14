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

#ifndef NGIND_SPRITE_H
#define NGIND_SPRITE_H

#include <string>

#include "rendering/quad_rendering_command.h"
#include "renderer_component.h"
#include "resources/texture_resource.h"
#include "rendering/rgba.h"
#include "rendering/program.h"
#include "rendering/quad.h"
#include "objects/entity_object.h"
#include "resources/program_resource.h"

#include "rttr/registration.h"
#include "script/lua_registration.h"

namespace ngind::components {
/**
 * The renderer component for sprite. You can create an instance both by new and by create
 * method. Just draw a lovely sprite on your screen!
 */
class Sprite : public RendererComponent {
public:
    Sprite();
    ~Sprite() override;
    Sprite(const Sprite&) = delete;
    Sprite& operator= (const Sprite&) = delete;

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
     * @return Sprite*, a pointer to the new instance.
     */
    static Sprite* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Set a new image to this rendering. It will release the old one texture resource.
     * @param filename: the image' filename
     */
    void setImage(const std::string& filename);

    inline void setImage(const char* filename) {
        setImage(std::string{filename});
    }

    /**
     * Set a new image and new boundary to this rendering.
     * @param filename: the image' filename
     * @param lb: the left bottom boundary
     * @param rt: the right top boundary
     */
    void setImage(const std::string& filename, const glm::vec2& lb, const glm::vec2& rt);

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
    inline void setBound(const glm::vec2& lb, const glm::vec2& rt) {
        setLeftBottomBound(lb);
        setRightTopBound(rt);
    }

    /**
     * Set the left bottom boundary.
     * @param lb: the left bottom boundary position
     */
    inline void setLeftBottomBound(const glm::vec2& lb) {
        _lb = lb;
    }

    /**
     * Set the right top boundary.
     * @param rt: the right top boundary position
     */
    inline void setRightTopBound(const glm::vec2& rt) {
        _rt = rt;
    }

    /**
     * Get the left bottom boundary.
     * @return Vector2D, the left bottom boundary position
     */
    inline glm::vec2 getLeftBottomBound() const {
        return _lb;
    }

    /**
     * Get the right top boundary.
     * @return Vector2D, the right top boundary position
     */
    inline glm::vec2 getRightTopBound() const {
        return _rt;
    }

private:
    /**
     * The texture resource reference this sprite use.
     */
    resources::TextureResource* _texture;

    /**
     * The boundary vectors.
     */
    glm::vec2 _lb, _rt;

    /**
     * Render command this sprite used.
     */
    rendering::QuadRenderingCommand* _command;

    /**
     * Quad information.
     */
    rendering::Quad* _quad;

    glm::mat4 getModelMatrix();

protected:
    /**
     * @see components/render_component.h
     */
    virtual void draw();
};

RTTR_REGISTRATION {
    rttr::registration::class_<Sprite>("Sprite")
            .method("create", &Sprite::create);
}

NGIND_LUA_BRIDGE_REGISTRATION(Sprite) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<Sprite, RendererComponent>("Sprite")
                .addFunction<void, const char*>("setImage", &Sprite::setImage)
                .addFunction("getImageName", &Sprite::getImageName)
                .addFunction("setBound", &Sprite::setBound)
                .addFunction("setLeftBottomBound", &Sprite::setLeftBottomBound)
                .addFunction("setRightTopBound", &Sprite::setRightTopBound)
                .addFunction("getLeftBottomBound", &Sprite::getLeftBottomBound)
                .addFunction("getRightTopBound", &Sprite::getRightTopBound)
            .endClass()
        .endNamespace();
}
} // namespace ngind::components

#endif //NGIND_SPRITE_H
