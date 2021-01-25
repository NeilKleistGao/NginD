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

/// @file auto_collection_object.h

#ifndef NGIND_AUTO_COLLECTION_OBJECT_H
#define NGIND_AUTO_COLLECTION_OBJECT_H

#include "script/lua_registration.h"

namespace ngind::memory {
/**
 * This class enables object to recycle itself if there is no reference
 * of it. Notably this class is not an actual "object" and is not inherited from
 * object class.
 */
class AutoCollectionObject {
public:
    AutoCollectionObject();

    virtual ~AutoCollectionObject() {
        _sustain = 0;
    }

    /**
     * Increase the number of reference to this.
     */
    inline void addReference() {
        // CALL ME MOMMY
        // JUST LIKE YOUR FANTASY
        // There is no crime in ideality
        // MUX>>>DEMUX
        // Can't you understand me?
        // I'm not mine NAND I'm not yours
        this->_sustain++;
    }

    /**
     * Decrease the number of reference to this. If the number is equal to 0,
     * remove itself from the memory pool
     */
    void removeReference();

    /**
     * Get the number of reference.
     * @return int, the number of reference
     */
    inline int getSustain() const {
        return this->_sustain;
    }

private:
    /**
     * The number of reference.
     */
    int _sustain;
};

NGIND_LUA_BRIDGE_REGISTRATION(AutoCollectionObject) {
luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<AutoCollectionObject>("AutoCollectionObject")
                .addFunction("addReference", &AutoCollectionObject::addReference)
                .addFunction("removeReference", &AutoCollectionObject::removeReference)
                .addFunction("getSustain", &AutoCollectionObject::getSustain)
            .endClass()
        .endNamespace();
}

} // namespace ngind::memory

#endif //NGIND_AUTO_COLLECTION_OBJECT_H
