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

--- @file welcome.lua

WelcomeWorldAction = class("WelcomeWorldAction")

function WelcomeWorldAction:ctor()
    self.alpha = 255
    self.timer = 0
end

function WelcomeWorldAction:entry()
    self.label = engine.Label.getComponent(self.game_object)
    self.input = engine.Input.getInstance()
    self.this.move(self.this, "Idle")
end

function WelcomeWorldAction:exit()
    print("goodbye")
end

function WelcomeWorldAction:updateIdle(dlt)
    self.timer = self.timer + dlt
    if self.timer >= 1.0 then
        self.alpha = 255 - self.alpha
        self.timer = self.timer - 1.0
        self.label.setAlpha(self.label, self.alpha)
    end

    local test = self.input.getKeyReleased(self.input, 32)
    if test == true then
        local game = engine.Game.getInstance()
        game.quit(game)
    end
end