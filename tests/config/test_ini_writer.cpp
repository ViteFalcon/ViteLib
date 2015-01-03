/**
* The MIT License (MIT)
*
* Copyright (c) 2015 Abi George Ullattil (Vite Falcon)

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "test_ini_writer.h"

TestIniWriter::TestIniWriter(const vite::String& filename)
    : stream(filename.asUTF8(), std::ios::binary|std::ios::out)
{
}

TestIniWriter::TestIniWriter(TestIniWriter&& other)
    : stream(std::move(other.stream))
{
}

TestIniWriter::~TestIniWriter()
{
    close();
}

TestIniWriter& TestIniWriter::addSection(const char* section)
{
    stream << "[" << section << "]" << std::endl;
    return *this;
}

TestIniWriter& TestIniWriter::addEntry(const char* key, const char* value)
{
    stream << key << " = " << value << std::endl;
    return *this;
}

void TestIniWriter::close()
{
    if (stream.is_open())
    {
        stream.close();
    }
}

