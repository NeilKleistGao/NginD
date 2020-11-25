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

/// @file file.h
/// @date 2020/10/28

/**
@brief
    This file includes the file object class's declaration. It may be easier and
more convenient to access a file using file class. All file operations in this
engine is based on it.
*/


#ifndef NGIND_FILE_H
#define NGIND_FILE_H

#include <iostream>
#include <cstdio>

#include "coroutine/coroutine.h"
#include "memory/auto_collection_object.h"

namespace ngind {

/**
@class
    The general file operation class. It's a subclass of AutoCollectionObject so you
needn't delete file object by yourself but if you need keep it for a while, you
should call addSustain.

@see kernel/memory/auto_collection_object.h
*/
class File : public AutoCollectionObject {
public:
    /// @public
    File();
    /// @public
    /// @param const std::string&: the path of file
    explicit File(const std::string&);

    /// @public
    /// @param const std::string&: the path of file
    /// @param const std::string&: the mode of file, same as fopen
    File(const std::string&, const std::string&);

    File(const File&) = delete;
    File(File&&) = delete;

    /// @public
    ~File();

    /// @public
    /// @static
    /// @property The names of some special files such as stdin, stdout, stderr
    const static std::string STDIN, STDOUT, STDERR;

    /// @public
    /// @fn Write a line into a file. Make sure this file is writable.
    /// @param const std::string&: the words will be written
    /// @return void
    void writeLine(const std::string&);

    /// @public
    /// @fn Read a line from a file. Make sure this file is readable.
    /// @param void
    /// @return std::string, the content of this file
    std::string readLine();

    /// @public
    /// @fn Write something into a file. Make sure this file is writable.
    /// @param const std::string&: the words will be written
    /// @return void
    void write(const std::string&);

    /// @public
    /// @fn Write something into a file. Make sure this file is writable.
    /// @param const char*: the words will be written
    /// @param const size_t&: the length of content
    /// @return void
    void write(const char*, const size_t&);

    /// @public
    /// @fn Read characters from file. Make sure this file is readable.
    /// @param const size_t&: the length of content to be read
    /// @return char*, the pointer of the head of buffer
    char* read(const size_t&);

    /// @public
    /// @fn Read all content from file. Make sure this file is readable.
    /// @param void
    /// @return std::string, all things in file
    std::string readToEnd();

    /// @public
    /// @fn Flush this file.
    /// @param void
    /// @return void
    inline void flush() {
        fflush(this->_fp);
    }

    /// @public
    /// @fn Check whether this file is open.
    /// @param void
    /// @return bool, true if file is open
    inline bool isOpen() const {
        return this->_open;
    }

    /// @public
    /// @fn Check whether this file is readable.
    /// @param void
    /// @return bool, true if file is readable
    inline bool isReadable() const {
        return this->_readable;
    }

    /// @public
    /// @fn Check whether this file is writable.
    /// @param void
    /// @return bool, true if file is writable
    inline bool isWriteable() const {
        return this->_writeable;
    }

    /// @public
    /// @fn Check whether this file is in binary mode.
    /// @param void
    /// @return bool, true if file is in binary mode
    inline bool isBinary() const {
        return this->_binary;
    }

    /// @public
    /// @fn Open a file in write/read mode.
    /// @param const std::string&: the path of file
    /// @return void
    void open(const std::string&);

    /// @public
    /// @fn Open a file.
    /// @param const std::string&: the path of file
    /// @param const std::string&: the mode of file, same as fopen
    /// @return void
    void open(const std::string&, const std::string&);

    /// @public
    /// @fn Close the open file, saving if needed.
    /// @param void
    /// @return void
    void close();

    /// @public
    /// @fn Read file async.
    /// @param const size_t&: the length of content to be read
    /// @param typename Coroutine<char*, const size_t&>::callback: callback function called when reading finishes
    /// @return Coroutine<char*, const size_t&>, the coroutine object
    Coroutine<char*, const size_t&> readAsync(const size_t&, typename Coroutine<char*, const size_t&>::callback);

    /// @public
    /// @fn Write file async.
    /// @param const std::string&: the content to be written
    /// @param typename Coroutine<void, const std::string&>::callback: callback function called when writing finishes
    /// @return Coroutine<void, const std::string&>, the coroutine object
    Coroutine<void, const std::string&> writeAsync(const std::string&, typename Coroutine<void, const std::string&>::callback);

    /// @public
    /// @fn Write file async.
    /// @param const char*: the content to be written
    /// @param const size_t&: the length of content
    /// @param typename Coroutine<void, const char*, const size_t&>::callback: callback function called when writing finishes
    /// @return Coroutine<void, const char*, const size_t&>, the coroutine object
    Coroutine<void, const char*, const size_t&> writeAsync(const char*, const size_t&, typename Coroutine<void, const char*, const size_t&>::callback);

private:
    /// @private
    /// @property The real file pointer
    FILE* _fp;
    /// @private
    /// @property The states of this file
    bool _open, _readable, _writeable, _binary, _redirect;
};

} // namespace ngind

#endif //NGIND_FILE_H
