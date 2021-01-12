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

/// @file render_command.h

#ifndef NGIND_RENDERING_COMMAND_H
#define NGIND_RENDERING_COMMAND_H

#include "quad.h"
#include "program.h"
#include "rgba.h"

namespace ngind::rendering {

enum RenderCommandType {
    UNKNOWN_COMMAND,
    QUAD_COMMAND,
    BATCH_QUAD_COMMAND,
    // TODO: other types
};

class RenderingCommand {
public:
    virtual void call() = 0;

    inline void setZ(const unsigned int& z) {
        _z = z;
    }

    inline unsigned int getZ() const {
        return _z;
    }

    inline void setColor(const rendering::RGBA& color) {
        _color = color;
    }

    inline rendering::RGBA getColor() const {
        return _color;
    }

    inline void setModel(const glm::mat4& model) {
        _model = model;
    }

    inline glm::mat4 getModel() const {
        return _model;
    }

    inline void setProgram(Program* program) {
        _program = program;
    }

    inline Program* getProgram() const {
        return _program;
    }
private:
    unsigned int _z;

    rendering::RGBA _color;

    glm::mat4 _model;

    /**
     * Render program
     */
    Program* _program;
};

struct RenderCommand {
public:
    unsigned int z_order{};
    const RenderCommandType type;

    explicit RenderCommand(const RenderCommandType& t = UNKNOWN_COMMAND)
        : type(t) {}
};

/**
 * This command is designed for quad rendering.
 */
struct QuadRenderCommand : public RenderCommand {
    /**
     * ID of texture that rendering will use
     */
    GLuint texture_id{};

    /**
     * Quad data
     */
    Quad* quad;

    /**
     * Render program
     */
    Program* program;

    QuadRenderCommand()
        : RenderCommand(QUAD_COMMAND), quad(nullptr), program(nullptr) {}
};

} // namespace ngind::rendering

#endif //NGIND_RENDERING_COMMAND_H
