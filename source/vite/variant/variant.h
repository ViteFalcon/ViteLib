#pragma once
#include <sstream>
#include <typeinfo>
#include <utility>

#include "../string.hpp"
#include "variant_value.h"
#include "variant_converter.h"
#include "variant_default.h"

namespace vite
{
    class Variant
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
        ToType as() const
        {
            if (mValueHeld == nullptr)
            {
                return VariantDefault<ToType>();
            }
            else if (typeid(ToType) == mValueHeld->getType())
            {
                return ToType(*(static_cast<const ToType*>(mValueHeld->data())));
            }
            return *VariantConverter::convert<ToType>(mValueHeld->getType(), mValueHeld->data());
        }

        template<>
        const char* as<const char*>() const;
    private:
        static const std::type_info& VOID_TYPE;

        VariantValue* mValueHeld;
    };
}