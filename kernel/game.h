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

/// @file game.h
/// @date 2020/10/21

#ifndef NGIND_GAME_H
#define NGIND_GAME_H

#include <map>
#include <string>
#include <stack>

#include "resources/config_resource.h"
#include "timer/timer.h"
#include "objects/world.h"

namespace ngind {

/**
@class Game manager class. It's a singleton class and manages all game works.
*/
class Game {
public:
    /// @public
    /// @static
    /// @fn Get instance of game manager.
    /// @param void
    /// @return Game*, instance of game manager
    static Game* getInstance();

    /// @public
    /// @static
    /// @fn Destroy instance of game manager.
    /// @param void
    /// @return void
    static void destroyInstance();

    /// @public
    /// @fn Load a game world into memory
    /// @param const std::string&: world's name
    /// @return void
    void loadWorld(const std::string&);

    /// @public
    /// @fn Destroy a game world
    /// @param const std::string&: world's name
    /// @return void
    void destroyWorld(const std::string&);

    /// @public
    /// @fn Push current world into stack and load a new one
    /// @param const std::string&: world's name
    /// @return void
    void pushAndLoadWorld(const std::string&);

    /// @public
    /// @fn Pop a world from stack and load it.
    /// @param const bool&: true if destroy current world later
    /// @return void
    void popAndLoadWorld(const bool&);

    /// @public
    /// @fn Load a game world into memory and destroy current world
    /// @param const std::string&: world's name
    /// @return void
    void DestroyAndLoadWorld(const std::string&);

    /// @public
    /// @fn Start playing game.
    /// @param void
    /// @return void
    void start();

    /// @public
    /// @fn Get current world
    /// @param void
    /// @return World*, current world
    inline World* getCurrentWorld() {
        return _current_world;
    }

    /// @public
    /// @fn Quit game.
    /// @param void
    /// @return void
    inline void quit() {
        this->_loop_flag = false;
    }

private:
    /// @private
    Game();

    /// @property
    ~Game();

    /// @private
    /// @static
    /// @property Instance of game manager
    static Game* _instance;

    /// @private
    /// @property Global config data
    ConfigResource* _global_settings;

    /// @private
    /// @property Global timer
    Timer _global_timer;

    /// @private
    /// @property Current world
    World* _current_world;

    /// @private
    /// @property Worlds dictionary
    std::map<std::string, World*> _worlds;

    /// @private
    /// @property Worlds stack
    std::stack<World*> _stack;

    /// @private
    /// @property Whether game still goes on
    bool _loop_flag;
};

} // namespace ngind

#endif //NGIND_GAME_H
