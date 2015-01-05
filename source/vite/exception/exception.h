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
#pragma once

#include <exception>

#include "../defines.hpp"
#include "error_detail.h"

#if vCOMPILER_IS_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4275)
#endif

namespace vite
{
    struct vLIB_EXPORT Exception : public std::exception
    {
    public:
        static void Throw(Exception& exception, const char* currentFunction, const char* currentFile, int currentLine);
    public:
        Exception();
        Exception(const char* typeName);

        virtual const char* what() const override;

        Exception& operator << (const inner::ErrorInfo& info);

    private:
        std::string toString() const;

        class ErrorDetails;
        ErrorDetails* details;
    };
}


#define vDEFINE_EXCEPTION_WIH_NAMESPACE(classname, namespace_name) namespace namespace_name {\
    struct classname : vite::Exception\
    {\
        classname() : vite::Exception(vSTRINGIFY(classname)) {}\
    };\
}
#define vDECLARE_LIB_EXCEPTION(classname)  namespace vite {\
    struct vLIB_EXPORT classname : Exception\
    {\
        classname();\
    };\
}

vDECLARE_LIB_EXCEPTION(FileNotFoundException)
vDECLARE_LIB_EXCEPTION(IllegalArgumentException)
vDECLARE_LIB_EXCEPTION(InvalidOperationException)
vDECLARE_LIB_EXCEPTION(InvalidStateException)
vDECLARE_LIB_EXCEPTION(ItemNotFoundException)
vDECLARE_LIB_EXCEPTION(NotImplementedException)
vDECLARE_LIB_EXCEPTION(RuntimeException)

#if vCOMPILER_IS_MSVC
#   pragma warning(pop)
#endif