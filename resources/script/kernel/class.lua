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

--- @file class.lua

function class(classname)
    local cls = {
        ctor = function() end,
    }

    cls.__cname = classname
    cls.__ctype = 2
    cls.__index = cls
    cls.game_object = nil
    cls.this = nil
    cls.subscriber = {}

    function cls.new(...)
        local instance = setmetatable({}, cls)
        instance.class = cls
        instance.move = function(state_name) instance.this.move(instance.this, state_name) end
        instance.halt = function() instance.this.halt(instance.this) end
        instance.notify = function(msg, data) instance.this.notify(instance.this, instance, msg, data) end
        instance.notifyAll = function(msg, data) instance.this.notifyAll(instance.this, instance, msg, data) end
        instance:ctor(...)
        return instance
    end

    return cls
end