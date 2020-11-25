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
// FILENAME: png_image.cc

#include "GL/glew.h"

#include "png_image.h"

#include <iostream>
#include <cstdio>
#include "png.h"

namespace ngind {
const std::string PNGImage::IMAGE_RESOURCE_PATH = "resources/images";

PNGImage::PNGImage() : _image(nullptr) {

}

PNGImage::PNGImage(const std::string& filename) : PNGImage() {
    this->loadPNG(filename);
}

PNGImage::~PNGImage() {
    delete this->_image->pixels;
    this->_image->pixels = nullptr;
    delete this->_image;
    this->_image = nullptr;
}

void PNGImage::loadPNG(const std::string& filename) {
    FILE* fp = fopen((filename).c_str(),
            "rb");
    if (!fp) {
        fclose(fp);
        return;
    }

    constexpr size_t HEADER_LENGTH = 8;
    unsigned char header[HEADER_LENGTH];
    fread(header, sizeof(unsigned char), HEADER_LENGTH, fp);
    if (png_sig_cmp(header, 0, HEADER_LENGTH)) {
        fclose(fp);
        return;
    }

    png_structp struct_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!struct_ptr) {
        fclose(fp);
        return;
    }
    png_infop info_ptr = png_create_info_struct(struct_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&struct_ptr, nullptr, nullptr);
        fclose(fp);
        return;
    }

    png_init_io(struct_ptr, fp);
    png_set_sig_bytes(struct_ptr, HEADER_LENGTH);

    png_read_info(struct_ptr, info_ptr);
    this->_image = new(std::nothrow) GLFWimage();
    this->_image->width = png_get_image_width(struct_ptr, info_ptr);
    this->_image->height = png_get_image_height(struct_ptr, info_ptr);

    if (png_get_color_type(struct_ptr, info_ptr) == PNG_COLOR_TYPE_RGB_ALPHA) {
        png_set_swap_alpha(struct_ptr);
    }

    png_set_interlace_handling(struct_ptr);
    png_read_update_info(struct_ptr, info_ptr);

    if (setjmp(png_jmpbuf(struct_ptr))) {
        fclose(fp);
        return;
    }

    this->_image->pixels =
            new unsigned char[this->_image->width * this->_image->height * 4];
    auto * temp = new png_bytep[this->_image->height];
    for (int i = 0; i < this->_image->height; i++) {
        temp[i] = (png_bytep)png_malloc(struct_ptr, png_get_rowbytes(struct_ptr, info_ptr));
    }

    png_read_image(struct_ptr, temp);
    for (int i = 0, j = 0; j < this->_image->height; j++) {
        for (int k = 0; k < this->_image->width * 4; k += 4, i += 4) {
            this->_image->pixels[i] = temp[j][k + 1];
            this->_image->pixels[i + 1] = temp[j][k + 2];
            this->_image->pixels[i + 2] = temp[j][k + 3];
            this->_image->pixels[i + 3] = temp[j][k];
        }
    }

    delete[] temp;
    fclose(fp);
}

} // namespace ngind