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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file program_resource.h

#ifndef NGIND_PROGRAM_RESOURCE_H
#define NGIND_PROGRAM_RESOURCE_H

#include "resource.h"
#include "rendering/program.h"

namespace ngind::resources {

/**
 * Resource class containing program data.
 */
class ProgramResource : public Resource {
public:
    ProgramResource();
    ~ProgramResource() override;

    /**
     * @see kernel/resources/resource.h
     */
    void load(const std::string&) override;

    /**
     * Get program object
     * @return Program*, the program object
     */
    inline rendering::Program* get() const {
        return _program;
    }

    /**
     * Get program object
     * @return Program*, the program object
     */
    inline rendering::Program* operator-> () const {
        return get();
    }
private:
    /**
     * The program object
     */
    rendering::Program* _program;
};

} // namespace ngind::resources

#endif //NGIND_PROGRAM_RESOURCE_H
