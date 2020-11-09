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
// LAST MODIFY: 2020/10/21
// FILENAME: game.h

#ifndef NGIND_GAME_H
#define NGIND_GAME_H

#include <map>
#include <string>
#include <stack>

#include "resources/config_resource.h"
#include "timer/timer.h"
#include "objects/world.h"

namespace ngind {

class Game {
public:
    static Game* getInstance();
    static void destroyInstance();

    void loadWorld(const std::string&);
    void destroyWorld(const std::string&);
    void pushAndLoadWorld(const std::string&);
    void popAndLoadWorld(const std::string&, const bool&);
    void DestroyAndLoadWorld(const std::string&);

    void start();

    inline World* getCurrentWorld() {
        return _current_world;
    }

    inline void quit() {
        this->_loop_flag = false;
    }

private:
    Game();
    ~Game();

    static Game* _instance;
    ConfigResource* _global_settings;
    Timer _global_timer;
    World* _current_world;
    std::map<std::string, World*> _worlds;
    std::stack<World*> _stack;
    bool _loop_flag;
};

} // namespace ngind

#endif //NGIND_GAME_H
