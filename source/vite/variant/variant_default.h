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
        std::stringstream errorMessage;
        errorMessage << "No default value specified for variant type of " << typeid(T).name();
        throw new std::runtime_error(errorMessage.str());
    }

    template<>
    bool VariantDefault<bool>();

    template<>
    char VariantDefault<char>();

    template<>
    unsigned char VariantDefault<unsigned char>();

    template<>
    std::int8_t VariantDefault<std::int8_t>();

    template<>
    std::uint8_t VariantDefault<std::uint8_t>();

    template<>
    short VariantDefault<short>();

    template<>
    unsigned short VariantDefault<unsigned short>();

    template<>
    int VariantDefault<int>();

    template<>
    unsigned int VariantDefault<unsigned int>();

    template<>
    long VariantDefault<long>();

    template<>
    unsigned long VariantDefault<unsigned long>();

    template<>
    long long VariantDefault<long long>();

    template<>
    unsigned long long VariantDefault<unsigned long long>();

    template<>
    float VariantDefault<float>();

    template<>
    double VariantDefault<double>();

    template<>
    long double VariantDefault<long double>();

    template<>
    std::string VariantDefault<std::string>();
}

