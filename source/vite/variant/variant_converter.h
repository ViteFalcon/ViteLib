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

#include <functional>
#include <unordered_map>
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
    public: // Types
        typedef std::function<void*(const void* fromValue)> Converter;

    private: // Types
        typedef std::unordered_map<const std::type_info*, Converter> ToConverter;
        typedef std::unordered_map<const std::type_info*, ToConverter> Converters;

    public:
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

        template<typename FromType, typename ToType>
        static bool canConvert()
        {
            return canConvert(typeid(FromType), typeid(ToType));
        }

        template<typename ToType>
        static bool canConvert(const std::type_info& fromTypeInfo)
        {
            return canConvert(fromTypeInfo, typeid(ToType));
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
            void* value = convert(fromTypeInfo, fromValue, toTypeInfo);
            return static_cast<ToType*>(value);
        }
    private:
        static Converters sConverters;
        static StdConverters sStdConverters;

        static bool canConvert(const std::type_info& fromTypeInfo, const std::type_info& toTypeInfo);

        static void* convert(const std::type_info& fromTypeInfo, const void* fromValue, const std::type_info& toTypeInfo);
    public:
        VariantConverter() = delete;
        ~VariantConverter() = delete;
        VariantConverter& operator = (const VariantConverter& other) = delete;
    };
}
