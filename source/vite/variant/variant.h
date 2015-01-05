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

#include <sstream>
#include <typeinfo>
#include <utility>

#include "../defines.hpp"
#include "../optional.hpp"
#include "../string.hpp"
#include "variant_value.h"
#include "variant_converter.h"
#include "variant_default.h"

namespace vite
{
    class vLIB_EXPORT Variant
    {
    public:
        Variant() : mValueHeld(nullptr) {}

        Variant(const char* value)
            : mValueHeld(new VariantValueImpl<vite::String>(vite::String(value))) {}

        Variant(const std::string& value)
            : mValueHeld(new VariantValueImpl<vite::String>(vite::String(value))) {}

        Variant(const wchar_t* value)
            : mValueHeld(new VariantValueImpl<vite::String>(vite::String(value))) {}

        Variant(const std::wstring& value)
            : mValueHeld(new VariantValueImpl<vite::String>(vite::String(value))) {}

        template <typename T>
        Variant(const T& value)
            : mValueHeld(new VariantValueImpl<T>(value)) {}

        Variant(const Variant& other)
            : mValueHeld(other.mValueHeld->clone()) {}

        Variant(Variant&& other)
            : mValueHeld(std::move(other.mValueHeld)) {}

        ~Variant() { delete mValueHeld; }

        /**
         * Swap values of this instance with another RoVariant
         */
        inline void swap(Variant& other)
        {
            std::swap(mValueHeld, other.mValueHeld);
        }

        /**
         * Assignment operator
         */
        inline Variant& operator = (const Variant& rhs)
        {
            swap(Variant(rhs));
            return *this;
        }

        /**
         * Move assignment operation
         */
        inline Variant& operator = (Variant&& rhs)
        {
            mValueHeld = std::move(rhs.mValueHeld);
            return *this;
        }

        inline const std::type_info& getType() const
        {
            if (mValueHeld)
            {
                return mValueHeld->getType();
            }
            return VOID_TYPE;
        }

        template <typename T>
        inline bool isType() const
        {
            return typeid(T) == getType();
        }

        /**
         * Return if this variant has a value stored.
         */
        inline bool empty() const
        {
            return nullptr == mValueHeld;
        }

        /**
        Returns true if variant has a value assigned to it. False otherwise.
        **/
        inline operator bool() const
        {
            return !empty();
        }

        /**
        Check if another variant type is equal to this instance.
        **/
        inline bool equals(const Variant& rhs) const
        {
            if (mValueHeld)
            {
                return mValueHeld->equals(*rhs.mValueHeld);
            }
            return false;
        }

        /**
        Equality operator
        **/
        inline bool operator == (const Variant& rhs) const
        {
            return equals(rhs);
        }

        /**
        Inequality operator
        **/
        inline bool operator != (const Variant& rhs) const
        {
            return !equals(rhs);
        }

        /**
         * Less than operator.
         */
        inline bool operator < (const Variant& rhs) const
        {
            return mValueHeld < rhs.mValueHeld;
        }

        template <typename ToType>
        Optional<ToType> maybeAs() const
        {
            if (mValueHeld == nullptr)
            {
                return Optional<ToType>::absent();
            }
            if (typeid(ToType) == mValueHeld->getType())
            {
                return Optional<ToType>::of(getData<ToType>());
            }
            if (VariantConverter::canConvert<ToType>(mValueHeld->getType()))
            {
                return Optional<ToType>::of(*VariantConverter::convert<ToType>(mValueHeld->getType(), mValueHeld->data()));
            }
            return Optional<ToType>::absent();
        }

        template<>
        Optional<const char*> maybeAs<const char*>() const;

        template<>
        Optional<const wchar_t*> maybeAs<const wchar_t*>() const;

        template <>
        Optional<std::string> maybeAs<std::string>() const;

        template<>
        Optional<std::wstring> maybeAs<std::wstring>() const;

        template <typename ToType>
        ToType as() const
        {
            if (mValueHeld == nullptr)
            {
                return VariantDefault<ToType>();
            }
            auto result = maybeAs<ToType>();
            if (result.isAbsent())
            {
                std::stringstream errorMessage;
                errorMessage << "Failed to convert variant to type " << typeid(ToType).name();
                vTHROW(InvalidOperationException() << ErrorInfoDetail(errorMessage.str()));
            }
            return result.getValue();
        }

    private:
        template <typename U>
        inline const U& getData() const
        {
            return *static_cast<const U*>(mValueHeld->data());
        }
    private:
        static const std::type_info& VOID_TYPE;

        VariantValue* mValueHeld;
    };
}