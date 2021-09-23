/**
 * @copybrief
 * MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file rgba.h

#ifndef NGIND_COLOR_H
#define NGIND_COLOR_H

#include "script/lua_registration.h"

namespace ngind::rendering {

/**
 * RGBA color data.
 */
struct Color {
    Color() = default;
    explicit Color(const std::string& code) : r(), g(), b(), a() {
        auto color = convertHexString(code.substr(1));
        r = (color & 0xFF000000) >> 24;
        g = (color & 0x00FF0000) >> 16;
        b = (color & 0x0000FF00) >> 8;
        a = color & 0x000000FF;
    }

    /**
     * R,G,B,A components.
     */
    unsigned char r, g, b, a;
private:
    static unsigned int convertHexString(const std::string& str) {
        unsigned int res = 0;
        for (const auto& ch : str) {
            res <<= 4;
            if (isdigit(ch)) {
                res += static_cast<unsigned int>(ch - '0');
            }
            else if (islower(ch)) {
                res += static_cast<unsigned int>(ch - 'a' + 10);
            }
            else {
                res += static_cast<unsigned int>(ch - 'A' + 10);
            }
        }

        return res;
    }
};

NGIND_LUA_BRIDGE_REGISTRATION(RGBA) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<Color>("Color")
                .addProperty("r", &Color::r)
                .addProperty("g", &Color::g)
                .addProperty("b", &Color::b)
                .addProperty("a", &Color::a)
            .endClass()
        .endNamespace();
}

} // namespace ngind::rendering

#endif //NGIND_COLOR_H
