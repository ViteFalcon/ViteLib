/**
* The MIT License (MIT)
*
* Copyright (c) 2014 Abi George Ullattil (Vite Falcon)

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

#include "../defines.hpp"
#include "../string.hpp"

#include <boost/exception/error_info.hpp>

#define vERROR_INFO_TAGNAME(name) vCOMBINE(name,ErrorTag)
#define vERROR_INFO_NAME(name) name
#define vERROR_INFO(name, type) struct vERROR_INFO_TAGNAME(name)\
{\
    vERROR_INFO_TAGNAME(name)(const type val)\
        : value(val)\
    {\
    }\
    const type value; \
}; \
typedef boost::error_info<vERROR_INFO_TAGNAME(name), type> vERROR_INFO_NAME(name)
#define vERROR_INFO_STRING(name) vERROR_INFO(name, vite::String)

namespace vite
{
    vERROR_INFO_STRING(Detail);
    vERROR_INFO_STRING(Hint);
    vERROR_INFO_STRING(Hint);
    vERROR_INFO(CausedBy, std::exception);
}