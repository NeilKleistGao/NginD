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

/// @file galois_field.h

#ifndef NGIND_GALOIS_FIELD_H
#define NGIND_GALOIS_FIELD_H

namespace ngind::math {

class GaloisField {
public:
    GaloisField() = delete;
    ~GaloisField() = delete;

    static unsigned int multiply(const unsigned int& n, const unsigned int& s);
private:

    static unsigned int multiplyBy2(const unsigned int& s);

    static inline unsigned int multiplyBy3(const unsigned int& s) {
        return multiplyBy2(s) ^ s;
    }

    static inline unsigned int multiplyBy4(const unsigned int& s) {
        return multiplyBy2(multiplyBy2(s));
    }

    static inline unsigned int multiplyBy8(const unsigned int& s) {
        return multiplyBy2(multiplyBy4(s));
    }

    static inline unsigned int multiplyBy9(const unsigned int& s) {
        return multiplyBy8(s) ^ s;
    }

    static inline unsigned int multiplyBy11(const unsigned int& s) {
        return multiplyBy9(s) ^ multiplyBy2(s);
    }

    static inline unsigned int multiplyBy12(const unsigned int& s) {
        return multiplyBy8(s) ^ multiplyBy4(s);
    }

    static inline unsigned int multiplyBy13(const unsigned int& s) {
        return multiplyBy12(s) ^ s;
    }

    static inline unsigned int multiplyBy14(const unsigned int& s) {
        return multiplyBy12(s) ^ multiplyBy2(s);
    }
};

} // namespace ngind::math

#endif //NGIND_GALOIS_FIELD_H
