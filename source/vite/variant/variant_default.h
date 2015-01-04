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

#include <cinttypes>
#include <sstream>

namespace vite
{
    template <typename T>
    T VariantDefault()
    {
        return T();
    }

    template<>
    extern bool VariantDefault<bool>();

    template<>
    extern char VariantDefault<char>();

    template<>
    extern unsigned char VariantDefault<unsigned char>();

    template<>
    extern std::int8_t VariantDefault<std::int8_t>();

    template<>
    extern std::uint8_t VariantDefault<std::uint8_t>();

    template<>
    extern short VariantDefault<short>();

    template<>
    extern unsigned short VariantDefault<unsigned short>();

    template<>
    extern int VariantDefault<int>();

    template<>
    extern unsigned int VariantDefault<unsigned int>();

    template<>
    extern long VariantDefault<long>();

    template<>
    extern unsigned long VariantDefault<unsigned long>();

    template<>
    extern long long VariantDefault<long long>();

    template<>
    extern unsigned long long VariantDefault<unsigned long long>();

    template<>
    extern float VariantDefault<float>();

    template<>
    extern double VariantDefault<double>();

    template<>
    extern long double VariantDefault<long double>();

    template<>
    extern std::string VariantDefault<std::string>();
}

