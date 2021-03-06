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
    if Input.getKeyReleased(KEY_CODE.LEFT) then
        local name = Game.getCurrentWorldName()
        Game.destroyAndLoadWorld(WORLD_SWITCH_TABLE[name].prev)
    elseif Input.getKeyReleased(KEY_CODE.RIGHT) then
        local name = Game.getCurrentWorldName()
        Game.destroyAndLoadWorld(WORLD_SWITCH_TABLE[name].next)
    elseif Input.getKeyReleased(KEY_CODE.ESCAPE) then
        Game.quit()
    end
end

function WorldSwitch:exit()
end

WORLD_SWITCH_TABLE = {}
WORLD_SWITCH_TABLE["welcome"] = {}
WORLD_SWITCH_TABLE["welcome"]["next"] = "colorful-labels"
WORLD_SWITCH_TABLE["welcome"]["prev"] = "shader"
WORLD_SWITCH_TABLE["colorful-labels"] = {}
WORLD_SWITCH_TABLE["colorful-labels"]["next"] = "audio"
WORLD_SWITCH_TABLE["colorful-labels"]["prev"] = "welcome"
WORLD_SWITCH_TABLE["audio"] = {}
WORLD_SWITCH_TABLE["audio"]["next"] = "i18n"
WORLD_SWITCH_TABLE["audio"]["prev"] = "colorful-labels"
WORLD_SWITCH_TABLE["i18n"] = {}
WORLD_SWITCH_TABLE["i18n"]["next"] = "animation"
WORLD_SWITCH_TABLE["i18n"]["prev"] = "audio"
WORLD_SWITCH_TABLE["animation"] = {}
WORLD_SWITCH_TABLE["animation"]["next"] = "button"
WORLD_SWITCH_TABLE["animation"]["prev"] = "i18n"
WORLD_SWITCH_TABLE["button"] = {}
WORLD_SWITCH_TABLE["button"]["next"] = "capture"
WORLD_SWITCH_TABLE["button"]["prev"] = "animation"
WORLD_SWITCH_TABLE["capture"] = {}
WORLD_SWITCH_TABLE["capture"]["next"] = "physics"
WORLD_SWITCH_TABLE["capture"]["prev"] = "button"
WORLD_SWITCH_TABLE["physics"] = {}
WORLD_SWITCH_TABLE["physics"]["next"] = "joint"
WORLD_SWITCH_TABLE["physics"]["prev"] = "capture"
WORLD_SWITCH_TABLE["joint"] = {}
WORLD_SWITCH_TABLE["joint"]["next"] = "camera"
WORLD_SWITCH_TABLE["joint"]["prev"] = "physics"
WORLD_SWITCH_TABLE["camera"] = {}
WORLD_SWITCH_TABLE["camera"]["next"] = "archive"
WORLD_SWITCH_TABLE["camera"]["prev"] = "joint"
WORLD_SWITCH_TABLE["archive"] = {}
WORLD_SWITCH_TABLE["archive"]["next"] = "prefab"
WORLD_SWITCH_TABLE["archive"]["prev"] = "camera"
WORLD_SWITCH_TABLE["prefab"] = {}
WORLD_SWITCH_TABLE["prefab"]["next"] = "shader"
WORLD_SWITCH_TABLE["prefab"]["prev"] = "archive"
WORLD_SWITCH_TABLE["shader"] = {}
WORLD_SWITCH_TABLE["shader"]["next"] = "welcome"
WORLD_SWITCH_TABLE["shader"]["prev"] = "prefab"