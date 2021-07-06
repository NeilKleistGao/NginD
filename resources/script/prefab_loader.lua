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

--- @file prefab_loader.lua

PrefabLoader = class("PrefabLoader")

function PrefabLoader:ctor()
end

function PrefabLoader:enter()
    self.move("Create")
end

function PrefabLoader:updateCreate(delta)
    local spin1 = PrefabFactory.loadPrefab("spin")
    local spin2 = PrefabFactory.loadPrefab("spin")
    spin1:setPosition(engine.vec2(200, 384))
    spin2:setPosition(engine.vec2(824, 384))
    self.game_object:addChild("spin1", spin1)
    self.game_object:addChild("spin2", spin2)
    self.move("Idle")
end

function PrefabLoader:updateIdle(delta)
end

function PrefabLoader:exit()
end