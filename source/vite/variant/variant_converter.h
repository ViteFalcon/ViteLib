#pragma once
#include <functional>
#include <hash_map>
#include <sstream>
#include <typeinfo>

#include "std_converters.h"

namespace vite
{
    template <typename FromType, typename ToType>
    ToType ConvertVariant(const FromType& value)
    {
        return ToType(value);
    }

    class VariantConverter
    {
    public:
        typedef std::function<void*(const void* fromValue)> Converter;

        template <typename FromType, typename ToType>
        static void add()
        {
            auto converter = [](const void* value) -> void* {
                return new ToType(ConvertVariant<FromType, ToType>(*static_cast<const FromType*>(value)));
            };
            add<FromType, ToType>(static_cast<Converter>(converter));
        }

        template <typename FromType, typename ToType>
        static void add(Converter converter)
        {
            const std::type_info* fromType = &typeid(FromType);
            const std::type_info* toType = &typeid(ToType);
            sConverters[fromType][toType] = converter;
        }

        template <typename FromType, typename ToType>
        static ToType* convert(const FromType* fromValue)
        {
            const std::type_info& fromTypeInfo = typeid(FromType);
            convert<ToType>(fromTypeInfo, fromValue);
        }

        template <typename ToType>
        static ToType* convert(const std::type_info& fromTypeInfo, const void* fromValue)
        {
            const std::type_info& toTypeInfo = typeid(ToType);
            void* value = sConverters[&fromTypeInfo][&toTypeInfo](fromValue);
            return static_cast<ToType*>(value);
        }
    private:
        typedef std::hash_map<const std::type_info*, Converter> ToConverter;
        typedef std::hash_map<const std::type_info*, ToConverter> Converters;

        static Converters sConverters;
        static StdConverters sStdConverters;
    public:
        VariantConverter() = delete;
        ~VariantConverter() = delete;
        VariantConverter& operator = (const VariantConverter& other) = delete;
    };
}
