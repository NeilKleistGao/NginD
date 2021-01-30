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

#include "batch_quad_rendering_command.h"

namespace ngind::rendering {

BatchQuadRenderingCommand::BatchQuadRenderingCommand(Quad* quad, const size_t& size) :
RenderingCommand(), _quad(quad), _size(size) {
}

BatchQuadRenderingCommand::~BatchQuadRenderingCommand() {
    for (auto& v : _vertex) {
        delete[] v;
        v = nullptr;
    }

    _vertex.clear();
    _textures.clear();

    _quad->removeReference();
}

void BatchQuadRenderingCommand::call() {
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_quad->getVAO());

    for (int i = 0; i < _vertex.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glBindBuffer(GL_ARRAY_BUFFER, _quad->getVBO());
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * _size, _vertex[i]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

} // namespace ngind::rendering