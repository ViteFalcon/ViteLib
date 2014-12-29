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
