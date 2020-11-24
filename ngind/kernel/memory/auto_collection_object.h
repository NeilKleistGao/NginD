/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file auto_collection_object.h
/// @date 2020/9/20

/**
@brief
    This file includes the definition of object for auto memory collectable
object.
*/

#ifndef NGIND_AUTO_COLLECTION_OBJECT_H
#define NGIND_AUTO_COLLECTION_OBJECT_H

namespace ngind {
/**
@class
    This class enables object to recycle itself if there is no reference
of it. Notably this class is not an actual "object" and is not inherited from
object class.
*/
class AutoCollectionObject {
public:
    /// @public
    AutoCollectionObject();

    /// @public
    virtual ~AutoCollectionObject() = default;

    /// @public
    /// @fn Increase the number of reference to this
    /// @param void
    /// @return void
    inline void addReference() {
        // CALL ME MOMMY
        // JUST LIKE YOUR FANTASY
        // There is no crime in ideality
        // MUX>>>DEMUX
        // Can't you understand me?
        // I'm not mine NAND I'm not yours
        this->_sustain++;
    }

    /// @public
    /// @fn Decrease the number of reference to this. If the number is equal to 0,
    /// remove itself from the memory pool
    /// @param void
    /// @return void
    void removeReference();

    /// @public
    /// @fn Get the number of reference
    /// @param void
    /// @return short, the number of reference
    inline short getSustain() const {
        return this->_sustain;
    }

private:
    /// @private
    /// @property The number of reference
    short _sustain;
};
} // namespace ngind

#endif //NGIND_AUTO_COLLECTION_OBJECT_H
