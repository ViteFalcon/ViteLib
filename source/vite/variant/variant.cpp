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
#include "variant.h"

namespace vite
{
    const std::type_info& Variant::VOID_TYPE = typeid(void);

    template<>
    Optional<const char*> Variant::maybeAs<const char*>() const
    {
        const Optional<String> result = maybeAs<String>();
        if (result.isAbsent())
        {
            Optional<const char*>::absent();
        }
        return Optional<const char*>::of(result.getValue().asUTF8_c_str());
    }

    template<>
    Optional<const wchar_t*> Variant::maybeAs<const wchar_t*>() const
    {
        const Optional<String> result = maybeAs<String>();
        if (result.isAbsent())
        {
            Optional<const wchar_t*>::absent();
        }
        return Optional<const wchar_t*>::of(result.getValue().asWStr_c_str());
    }

    template <>
    Optional<std::string> Variant::maybeAs<std::string>() const
    {
        const Optional<String> result = maybeAs<String>();
        if (result.isAbsent())
        {
            Optional<std::string>::absent();
        }
        return Optional<std::string>::of(result.getValue().asUTF8());
    }

    template<>
    Optional<std::wstring> Variant::maybeAs<std::wstring>() const
    {
        const Optional<String> result = maybeAs<String>();
        if (result.isAbsent())
        {
            Optional<std::wstring>::absent();
        }
        return Optional<std::wstring>::of(result.getValue().asWStr());
    }
}