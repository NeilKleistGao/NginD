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
// FILENAME: render_command.h
// LAST MODIFY: 2020/11/1

#ifndef NGIND_RENDER_COMMAND_H
#define NGIND_RENDER_COMMAND_H

#include "quad.h"
#include "program.h"
#include "math/vector.h"
#include "rgba.h"

namespace ngind {

enum RenderCommandType {
    UNKNOWN_COMMAND,
    QUAD_COMMAND,
    // TODO: other types
};

struct RenderCommand {
public:
    unsigned int z_order{};
    const RenderCommandType type;
    bool transparent{};

    explicit RenderCommand(const RenderCommandType& t = UNKNOWN_COMMAND)
        : type(t) {}
};

struct QuadRenderCommand : public RenderCommand {
    GLuint texture_id{};
    Quad* quad;
    Program* program;

    QuadRenderCommand()
        : RenderCommand(QUAD_COMMAND), quad(nullptr), program(nullptr) {}
};

} // namespace ngind

#endif //NGIND_RENDER_COMMAND_H
