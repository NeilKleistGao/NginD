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

/// @file updatable_object.h
/// @date 2020/10/20

/**
@brief This file includes the interface of update-in-frames object
*/

#ifndef NGIND_UPDATABLE_OBJECT_H
#define NGIND_UPDATABLE_OBJECT_H

namespace ngind {

/**
@class
    An interface with update function called in each frame
*/
class UpdatableObject {
public:
    /// @public
    /// @fn Update state of this instance. It will be automatically
    /// called in each frame
    /// @param const float&: interval between two frames
    /// @return void
    virtual void update(const float&) = 0;
};
} // namespace ngind

#endif //NGIND_UPDATABLE_OBJECT_H
