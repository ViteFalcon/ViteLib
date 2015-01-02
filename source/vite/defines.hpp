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

#define vOS_WINDOWNS    1
#define vOS_MACOS       2
#define vOS_LINUX       3

#define vCOMPILER_MSVC  1
#define vCOMPILER_GNUC  2
#define vCOMPILER_CLANG 3

#if defined(_WIN32) || defined(_WIN64)
#   define vOS vOS_WINDOWNS
#elif defined(__APPLE_CC__)
#   define vOS vOS_MACOS
#else
#   define vOS vOS_LINUX
#endif

// Find the compiler
#if defined(_MSC_VER)
#   define vCOMPILER vCOMPILER_MSVC
#   define vCOMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
#   define vCOMPILER vCOMPILER_GNUC
#   define vCOMPILER_VERSION (((__GNUC__)*100) + \
    (__GNUC_MINOR__*10) + \
    __GNUC_PATCHLEVEL__)
#elif defined(__clang__)
#   define vCOMPILER vCOMPILER_CLANG
#   define vCOMPILER_VERSION __clang_major__*10000 + __clang_minor__*100 + __clang_patchlevel__
#else
#   pragma error "Unknown compiler! Abort! Abort!"
#endif

#define vOS_IS_WINDOWS  vOS == vOS_WINDOWNS
#define vOS_IS_LINUX    vOS == vOS_LINUX
#define vOS_IS_MACOS    vOS == vOS_MACOS

#define vCOMPILER_IS_MSVC   vCOMPILER == vCOMPILER_MSVC
#define vCOMPILER_IS_GNUC   vCOMPILER == vCOMPILER_GNUC
#define vCOMPILER_IS_CLANG  vCOMPILER == vCOMPILER_CLANG

#if defined(_WIN32)

#   define vFILENAME (strrchr(__FILE__,'\\') \
    ? strrchr(__FILE__,'\\')+1 \
    : __FILE__ \
    )
#else
#   define vFILENAME (strrchr(__FILE__,'/') \
    ? strrchr(__FILE__,'/')+1 \
    : __FILE__ \
    )
#endif

#define vINLINE inline

#define vSTRINGIFY(a) # a

#define vCOMBINE(a,b) a ## b

#define vWHERE __FUNCTION__<<"["<<vFILENAME<<" @ Line: "<<__LINE__<<"]"
