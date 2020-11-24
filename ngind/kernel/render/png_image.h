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
// LAST MODIFY: 2020/11/1
// FILENAME: png_image.h

#ifndef NGIND_PNG_IMAGE_H
#define NGIND_PNG_IMAGE_H

#include <string>

#include "glfw3.h"

#include "rgba.h"
#include "math/vector.h"

namespace ngind {

class PNGImage {
public:
    const static std::string IMAGE_RESOURCE_PATH;

    PNGImage();
    explicit PNGImage(const std::string&);
    ~PNGImage();

    void loadPNG(const std::string& filename);

    inline GLFWimage *getImageData() {
        return _image;
    }

    inline Vector2D getImageSize() {
        return Vector2D{_image->width, _image->height};
    }

private:
    GLFWimage *_image;
};

} // namespace ngind

#endif //NGIND_PNG_IMAGE_H
