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

/// @file batch_quad_rendering_command.h

#ifndef NGIND_BATCH_QUAD_RENDERING_COMMAND_H
#define NGIND_BATCH_QUAD_RENDERING_COMMAND_H

#include <vector>
#include <initializer_list>

#include "rendering_command.h"
#include "quad.h"

namespace ngind::rendering {

class BatchQuadRenderingCommand : public RenderingCommand {
public:
    BatchQuadRenderingCommand(Quad* quad, const size_t& size);
    ~BatchQuadRenderingCommand();
    BatchQuadRenderingCommand(const BatchQuadRenderingCommand&) = delete;
    BatchQuadRenderingCommand& operator= (const BatchQuadRenderingCommand&) = delete;

    void call() override;

    inline void push(std::initializer_list<GLfloat> vertex, const GLuint& texture) {
        _vertex.push_back(new GLfloat[_size]);
        auto& v = _vertex.back();
        int i = 0;
        for (const auto& f : vertex) {
            v[i++] = f;
        }

        _textures.push_back(texture);
    }
private:
    Quad* _quad;
    std::vector<GLfloat*> _vertex;
    std::vector<GLuint> _textures;

    size_t _size;
};

} // namespace ngind::rendering

#endif //NGIND_BATCH_QUAD_RENDERING_COMMAND_H
