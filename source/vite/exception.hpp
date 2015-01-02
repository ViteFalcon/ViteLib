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

#include "defines.hpp"
#include "exception/error_detail.h"
#include "exception/exception.h"


#define vDEFINE_EXCEPTION_WIH_NAMESPACE(classname, namespace_name) namespace namespace_name {\
    struct classname : vite::Exception\
    {\
        classname() : vite::Exception(vSTRINGIFY(classname)) {}\
    };\
}
#define vDEFINE_EXCEPTION(classname)  namespace vite {\
    struct classname : Exception\
    {\
        classname() : Exception(vSTRINGIFY(classname)) {}\
    };\
}

vDEFINE_EXCEPTION(FileNotFoundException);
vDEFINE_EXCEPTION(IllegalArgumentException)
vDEFINE_EXCEPTION(InvalidStateException)
vDEFINE_EXCEPTION(ItemNotFoundException)
vDEFINE_EXCEPTION(NotImplementedException)
vDEFINE_EXCEPTION(RuntimeException)

#define vTHROW(exception) boost::exception_detail::throw_exception_(exception,BOOST_CURRENT_FUNCTION,vFILENAME,__LINE__)
#define vTHROW_IF(condition, exception) if (condition) { vTHROW(exception); }