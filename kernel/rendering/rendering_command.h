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
#include "color.h"
#include "camera.h"
#include "memory/auto_collection_object.h"

namespace ngind::rendering {
/**
 * Command for rendering.
 */
class RenderingCommand : public memory::AutoCollectionObject {
public:
    RenderingCommand() : AutoCollectionObject() {}

    /**
     * execute the command.
     */
    virtual void call() = 0;

    /**
     * Set the z order.
     * @param z: the z order
     */
    inline void setZ(const unsigned int& z) {
        _z = z;
    }

    /**
     * Get the z order.
     * @return unsigned int, the z order
     */
    inline unsigned int getZ() const {
        return _z;
    }

    /**
     * Set the color for rendering.
     * @param color: the color.
     */
    inline void setColor(const rendering::Color& color) {
        _color = color;
    }

    /**
     * Get the color for rendering.
     * @return rendering::Color, the color for rendering
     */
    inline rendering::Color getColor() const {
        return _color;
    }

    /**
     * Set the model matrix.
     * @param model: the model matrix
     */
    inline void setModel(const glm::mat4& model) {
        _model = model;
    }

    /**
     * Get the model matrix.
     * @return glm::mat4, he model matrix
     */
    inline glm::mat4 getModel() const {
        return _model;
    }

    /**
     * Set the program that rendering uses.
     * @param program: the program that rendering uses
     */
    inline void setProgram(Program* program) {
        _program = program;
    }

    /**
     * Get the program that rendering uses.
     * @return Program*, the program that rendering uses
     */
    inline Program* getProgram() const {
        return _program;
    }

    virtual void prepare() {
        this->getProgram()->use();
        auto color = this->getColor();
        this->getProgram()->setFloat4("my_color", color.r / 255.0f, color.g / 255.0f,
                                     color.b / 255.0f, color.a / 255.0f);
        this->getProgram()->setMatrix4("projection", Camera::getInstance()->getProjection());
        this->getProgram()->setMatrix4("model", this->getModel());
    }
private:
    /**
     * The z order
     */
    unsigned int _z;

    /**
     * The color for rendering
     */
    rendering::Color _color;

    /**
     * Model projection matrix
     */
    glm::mat4 _model;

    /**
     * Render program
     */
    Program* _program;
};

} // namespace ngind::rendering

#endif //NGIND_RENDERING_COMMAND_H
