/** MIT License
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

/// @file quad_rendering_command.h

#ifndef NGIND_QUAD_RENDERING_COMMAND_H
#define NGIND_QUAD_RENDERING_COMMAND_H

#include "rendering_command.h"
#include "quad.h"

namespace ngind::rendering {

class QuadRenderingCommand : public RenderingCommand {
public:
    QuadRenderingCommand(Quad* quad, const GLuint& tid);
    ~QuadRenderingCommand() = default;
    QuadRenderingCommand(const QuadRenderingCommand&) = delete;
    QuadRenderingCommand& operator= (const QuadRenderingCommand&) = delete;

    void call() override;
private:
    Quad* _quad;

    GLuint _texture;
};

} // namespace ngind::rendering

#endif //NGIND_QUAD_RENDERING_COMMAND_H