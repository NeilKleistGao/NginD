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
// LAST MODIFY: 2020/10/31
// FILENAME: render.h

#ifndef NGIND_RENDER_H
#define NGIND_RENDER_H

#include "render_queue.h"
#include "window.h"
#include "rgba.h"
#include "perspective.h"

namespace ngind {

class Render {
public:
    static Render* getInstance();

    static void destroyInstance();

    bool startRenderLoopOnce();

    void createWindow(const int&, const int& height, const std::string&, const std::string&, const bool&);

    inline void clearScene(const RGBA& color) {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    inline void addRenderCommand(RenderCommand* cmd) {
        _queue->push(cmd);
    }

private:
    static Render* _instance;

    Window* _window;
    RenderQueue* _queue;

    void execute(RenderCommand*);
    void drawQuad(QuadRenderCommand*);

    Render();
    ~Render();
};

} // namespace ngind

#endif //NGIND_RENDER_H
