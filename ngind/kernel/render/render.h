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

/// @file render.h
/// @date 2020/10/31

#ifndef NGIND_RENDER_H
#define NGIND_RENDER_H

#include "render_queue.h"
#include "window.h"
#include "rgba.h"
#include "perspective.h"

namespace ngind {

/**
@class
    This class is due to operations of render, including drawing on screen
and window management.
*/
class Render {
public:
    /// @public
    /// @static
    /// @fn Get the instance of render
    /// @param void
    /// @return Render*, the instance of render
    static Render* getInstance();

    /// @public
    /// @static
    /// @fn Destroy the instance of render
    /// @param void
    /// @return void
    static void destroyInstance();

    /// @public
    /// @fn Start rendering and check whether application should exit or not
    /// @param void
    /// @return bool, true if it should exit
    bool startRenderLoopOnce();

    /// @public
    /// @fn Create a window
    /// @param const int&: width of window
    /// @param const int&: height of window
    /// @param const std::string&: title of window
    /// @param const std::string&: icon path of window
    /// @param const bool&: true if this window is fullscreen
    /// @return void
    void createWindow(const int&, const int&, const std::string&, const std::string&, const bool&);

    /// @public
    /// @fn Clean the scene
    /// @param const RGBA& color: background color of scene
    /// @return void
    inline void clearScene(const RGBA& color) {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /// @public
    /// @fn Add a render command to render queue
    /// @param RenderCommand* cmd: render command
    /// @return void
    inline void addRenderCommand(RenderCommand* cmd) {
        _queue->push(cmd);
    }

private:
    /// @private
    /// @property The unique instance if render
    static Render* _instance;

    /// @private
    /// @property The instance of window
    Window* _window;

    /// @private
    /// @property Queue for render command
    RenderQueue* _queue;

    /// @private
    /// @fn Execute a render command
    /// @param RenderCommand*: the command to be executed
    /// @return void
    void execute(RenderCommand*);

    /// @private
    /// @fn Execute a quad render command
    /// @param RenderCommand*: the command to be executed
    /// @return void
    void drawQuad(QuadRenderCommand*);

    /// @private
    Render();

    /// @private
    ~Render();
};

} // namespace ngind

#endif //NGIND_RENDER_H
