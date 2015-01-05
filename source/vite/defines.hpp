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

#   define vCURRENT_FILENAME (strrchr(__FILE__,'\\') \
    ? strrchr(__FILE__,'\\')+1 \
    : __FILE__ \
    )
#else
#   define vCURRENT_FILENAME (strrchr(__FILE__,'/') \
    ? strrchr(__FILE__,'/')+1 \
    : __FILE__ \
    )
#endif

#define vINLINE inline

#define vSTRINGIFY(a) # a

#define vCOMBINE(a,b) a ## b

#define vWHERE __FUNCTION__<<"["<<vFILENAME<<" @ Line: "<<__LINE__<<"]"

#if vOS_IS_WINDOWS
#   if vCOMPILER_IS_MSVC
#       pragma warning(disable: 4251)
#       define vDLL_EXPORT __declspec(dllexport)
#       define vDLL_IMPORT __declspec(dllimport)
    #elif vCOMPILER_IS_GNUC
#       define vDLL_EXPORT __attribute__ ((dllexport))
#       define vDLL_IMPORT __attribute__ ((dllimport))
#   endif
#   define vLIB_LOCAL
#else
#   if vCOMPILER_IS_GNUC
#       define vDLL_EXPORT __attribute__ ((visibility ("default")))
#       define vDLL_IMPORT
#       define vLIB_LOCAL __attribute__ ((visibility ("hidden")))
#   else
#       define vDLL_EXPORT
#       define vDLL_IMPORT
#       define vLIB_LOCAL
#   endif
#endif

#if defined(ViteLib_EXPORTS)
#   define vLIB_EXPORT vDLL_EXPORT
#else
#   define vLIB_EXPORT vDLL_IMPORT
#endif

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#   define vCURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#   define vCURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#   define vCURRENT_FUNCTION __FUNCSIG__
#elif vCOMPILER_IS_MSVC
#   define vCURRENT_FUNCTION __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#   define vCURRENT_FUNCTION __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#   define vCURRENT_FUNCTION __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#   define vCURRENT_FUNCTION __func__
#else
#   define vCURRENT_FUNCTION "(unknown)"
#endif

#define vCURRENT_LINE __LINE__