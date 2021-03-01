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

--- @file click_receiver.lua

ClickReceiver = class("ClickReceiver")

function ClickReceiver:ctor()
    self.subscribe[1] = {}
    self.subscribe[1]["name"] = "Clicked"
    self.subscribe[1]["whitelist"] = {"__all__"}

    self.count = 0
end

function ClickReceiver:enter()
    self.move("Idle")
end

function ClickReceiver:updateIdle()
end

function ClickReceiver:onClicked()
    self.count = self.count + 1
    local label = Label.getComponent(self.game_object)
    label:setText("YOU CLICK "..tostring(self.count).." TIME(S)")
end

function ClickReceiver:exit()
end