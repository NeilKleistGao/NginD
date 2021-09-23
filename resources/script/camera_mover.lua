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

--- @file camera_mover.lua

CameraMover = class("CameraMover")

function CameraMover:ctor()
    self._dis = 100
end

function CameraMover:enter()
    self.move("Left")
end

function CameraMover:updateLeft(delta)
    pos = Camera:getCameraPosition()
    if self._dis > 0 then
        pos.x = pos.x - delta * 100
        Camera:moveTo(pos)
        self._dis = self._dis - 1
    else
        self._dis = 100
        self.move("Right")
    end
end

function CameraMover:updateRight(delta)
    pos = Camera:getCameraPosition()
    if self._dis > 0 then
        pos.x = pos.x + delta * 100
        Camera:moveTo(pos)
        self._dis = self._dis - 1
    else
        self._dis = 100
        self.move("Left")
    end
end

function CameraMover:exit()
end