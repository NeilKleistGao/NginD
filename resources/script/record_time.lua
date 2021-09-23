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

--- @file record_time.lua

RecordTime = class("RecordTime")

function RecordTime:ctor()
end

function RecordTime:enter()
    self.date = Archive:getString("date", "")
    self.move("Display")
end

function RecordTime:updateDisplay()
    if self.date == "" then
        self.date = os.date("%Y-%m-%d %H:%M:%S")
    end

    local label = Label.getComponent(self.game_object)
    label:setText("Last Visit: "..self.date)

    self.move("Idle")
end

function RecordTime:updateIdle()
end

function RecordTime:exit()
    local now = os.date("%Y-%m-%d %H:%M:%S")
    Archive:setString("date", now)
end