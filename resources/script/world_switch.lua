--[[--
- MIT License
- Copyright (c) 2020 NeilKleistGao
- Permission is hereby granted, free of charge, to any person obtaining a copy
- of this software and associated documentation files (the "Software"), to deal
- in the Software without restriction, including without limitation the rights
- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
- copies of the Software, and to permit persons to whom the Software is
- furnished to do so, subject to the following conditions:
-
- The above copyright notice and this permission notice shall be included in all
- copies or substantial portions of the Software.
-
- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
- SOFTWARE.
- ]]

--- @file world_switch.lua

WorldSwitch = class("WorldSwitch")

function WorldSwitch:ctor()
end

function WorldSwitch:enter()
    self.move("Idle")
end

function WorldSwitch:updateIdle()
    if Input:getKeyReleased(KEY_CODE.LEFT) then
        local name = Game:getCurrentWorldName()
        Game:destroyAndLoadWorld(WORLD_SWITCH_TABLE[name].prev)
    elseif Input:getKeyReleased(KEY_CODE.RIGHT) then
        local name = Game:getCurrentWorldName()
        Game:destroyAndLoadWorld(WORLD_SWITCH_TABLE[name].next)
    elseif Input:getKeyReleased(KEY_CODE.ESCAPE) then
        Game:quit()
    end
end

function WorldSwitch:exit()
end

WORLD_SWITCH_TABLE = {
    [welcome] = {
        [next] = "colorful-labels",
        [prev] = "resolution"
    },
    [colorful-labels] = {
        [next] = "audio",
        [prev] = "welcome"
    },
    [audio] = {
        [next] = "i18n",
        [prev] = "colorful-labels"
    },
    [i18n] = {
        [next] = "animation",
        [prev] = "audio"
    },
    [animation] = {
        [next] = "button",
        [prev] = "i18n"
    },
    [button] = {
        [next] = "capture",
        [prev] = "animation"
    },
    [capture] = {
        [next] = "physics",
        [prev] = "button"
    },
    [physics] = {
        [next] = "joint",
        [prev] = "capture"
    },
    [joint] = {
        [next] = "camera",
        [prev] = "physics"
    },
    [camera] = {
        [next] = "archive",
        [prev] = "joint"
    },
    [archive] = {
        [next] = "prefab",
        [prev] = "camera"
    },
    [prefab] = {
        [next] = "shader",
        [prev] = "archive"
    },
    [shader] = {
        [next] = "resolution",
        [prev] = "prefab"
    },
    [resolution] = {
        [next] = "welcome",
        [prev] = "shader"
    }
}