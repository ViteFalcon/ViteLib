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

#include <typeinfo>

namespace vite
{
    class VariantValue
    {
    public:
        VariantValue() = default;
        virtual ~VariantValue() = default;

        virtual const std::type_info& getType() const = 0;
        virtual VariantValue* clone() const = 0;
        virtual const void* data() const = 0;
        virtual bool equals(const VariantValue&) const = 0;
    };

    template <typename T>
    class VariantValueImpl : public VariantValue
    {
    public:
        VariantValueImpl(const T& value)
            : mValue(value) {}

        VariantValueImpl(const T&& value)
            : mValue(value) {}

        virtual const std::type_info& getType() const override
        {
            return typeid(T);
        }

        virtual VariantValue* clone() const override
        {
            return new VariantValueImpl(T(mValue));
        }

        virtual const void* data() const override
        {
            return &mValue;
        }

        virtual bool equals(const VariantValue& other) const override
        {
            if (getType() != other.getType())
            {
                return false;
            }
            return mValue == static_cast<const VariantValueImpl<T>&>(other).mValue;
        }
    private:
        T mValue;
    };
}
