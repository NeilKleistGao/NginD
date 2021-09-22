/** MIT License
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

/// @file lua_registration.h

#include "lua_state.h"

#ifndef NGIND_LUA_REGISTRATION_H
#define NGIND_LUA_REGISTRATION_H

#define __NGIND_LUA_BRIDGE_REGISTRATION_CAT(__X__, __Y__) __X__##__Y__
#define NGIND_LUA_BRIDGE_REGISTRATION_CAT(__X__, __Y__) __NGIND_LUA_BRIDGE_REGISTRATION_CAT(__X__, __Y__)

/**
 * Macro for lua registration.
 */
#define NGIND_LUA_BRIDGE_REGISTRATION(__NAME__)                                                                                        \
static void NGIND_LUA_BRIDGE_REGISTRATION_CAT(__NAME__, __lua_bridge_register) ();                                                                                                   \
namespace {                                                                                                                            \
struct NGIND_LUA_BRIDGE_REGISTRATION_CAT(__NAME__, __register__) {                                                                     \
    NGIND_LUA_BRIDGE_REGISTRATION_CAT(__NAME__, __register__) () {                                                                     \
        NGIND_LUA_BRIDGE_REGISTRATION_CAT(__NAME__, __lua_bridge_register) ();                                                                                                       \
    }                                                                                                                                  \
};                                                                                                                                     \
}                                                                                                                                      \
static const NGIND_LUA_BRIDGE_REGISTRATION_CAT(__NAME__, __register__) NGIND_LUA_BRIDGE_REGISTRATION_CAT(__REGISTER__, __LINE__);      \
static void NGIND_LUA_BRIDGE_REGISTRATION_CAT(__NAME__, __lua_bridge_register) ()

#endif //NGIND_LUA_REGISTRATION_H
