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

#include "named_variants.h"

namespace vite
{
    const NamedVariants NamedVariants::EMPTY;

    template<>
    void vite::NamedVariants::set<Variant>(const String& name, const Variant& value)
    {
        setVariant(name, value);
    }

    void NamedVariants::setVariant(const String& name, const Variant& value)
    {
        mVariants[name] = value;
    }

    Optional<Variant> NamedVariants::getVariant(const String& name) const
    {
        auto itr = mVariants.find(name);
        if (itr == mVariants.end())
        {
            return Optional<Variant>::Absent();
        }
        return Optional<Variant>::Of(itr->second);
    }

    bool NamedVariants::hasKey(const String& name) const
    {
        return mVariants.count(name) != 0;
    }
}