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
#include "variant_default.h"

template<>
vLIB_EXPORT bool vite::VariantDefault()
{
    return false;
}

template<>
vLIB_EXPORT char vite::VariantDefault()
{
    return '\0';
}

template<>
vLIB_EXPORT unsigned char vite::VariantDefault()
{
    return '\0';
}

template<>
vLIB_EXPORT std::int8_t vite::VariantDefault()
{
    return '\0';
}

template<>
vLIB_EXPORT short vite::VariantDefault()
{
    return 0;
}

template<>
vLIB_EXPORT unsigned short vite::VariantDefault()
{
    return 0;
}

template<>
vLIB_EXPORT int vite::VariantDefault()
{
    return 0;
}

template<>
vLIB_EXPORT unsigned int vite::VariantDefault()
{
    return 0;
}

template<>
vLIB_EXPORT long vite::VariantDefault()
{
    return 0L;
}

template<>
vLIB_EXPORT unsigned long vite::VariantDefault()
{
    return 0L;
}

template<>
vLIB_EXPORT long long vite::VariantDefault()
{
    return 0L;
}

template<>
vLIB_EXPORT unsigned long long vite::VariantDefault()
{
    return 0L;
}

template<>
vLIB_EXPORT float vite::VariantDefault()
{
    return 0.0f;
}

template<>
vLIB_EXPORT double vite::VariantDefault()
{
    return 0.0;
}

template<>
vLIB_EXPORT long double vite::VariantDefault()
{
    return 0.0;
}

template<>
vLIB_EXPORT std::string vite::VariantDefault()
{
    return std::string();
}
