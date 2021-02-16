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

--- @file i18n.lua

LANGUAGE_CODE = {}
LANGUAGE_CODE.EN_US = -1
LANGUAGE_CODE.ZH_CN = 0
LANGUAGE_CODE.JA_JP = 1
LANGUAGE_CODE.FR_FR = 2
LANGUAGE_CODE.DE_DE = 3

I18N = {}
I18N.__i18n = engine.I18N.getInstance()

I18N.loadLanguagePack = function(code, filename)
    I18N.__i18n.loadLanguagePack(I18N.__i18n, code, filename)
end

I18N.use = function(code)
    I18N.__i18n.use(I18N.__i18n, code)
end

I18N.getByName = function(name)
    return I18N.__i18n.getByName(I18N.__i18n, name)
end