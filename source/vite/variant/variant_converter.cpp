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
#include "variant_converter.h"
#include "../exception.hpp"

vite::VariantConverter::Converters vite::VariantConverter::sConverters;
vite::StdConverters vite::VariantConverter::sStdConverters;

bool vite::VariantConverter::canConvert(const std::type_info& fromTypeInfo, const std::type_info& toTypeInfo)
{
    const Converters::const_iterator fromConverterItr = sConverters.find(&fromTypeInfo);
    if (fromConverterItr == sConverters.cend())
    {
        return false;
    }
    const ToConverter::const_iterator toConverterItr = fromConverterItr->second.find(&toTypeInfo);
    return toConverterItr != fromConverterItr->second.cend();
}

void* vite::VariantConverter::convert(const std::type_info& fromTypeInfo, const void* fromValue, const std::type_info& toTypeInfo)
{
    auto fromConverterItr = sConverters.find(&fromTypeInfo);
    if (fromConverterItr == sConverters.cend())
    {
        std::stringstream errorMessage;
        errorMessage << "Variant conversions doesn't have any conversion methods for types from " << fromTypeInfo.name();
        vTHROW(InvalidOperationException() << ErrorInfoDetail(errorMessage.str()));
    }
    auto toConverterItr = fromConverterItr->second.find(&toTypeInfo);
    if (toConverterItr == fromConverterItr->second.cend())
    {
        std::stringstream errorMessage;
        errorMessage << "Variant conversions doesn't exist from " << fromTypeInfo.name() << " to " << toTypeInfo.name();
        vTHROW(InvalidOperationException() << ErrorInfoDetail(errorMessage.str()));
    }
    Converter converter = toConverterItr->second;
    return converter(fromValue);
}