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
#include "std_converters.h"
#include "variant_converter.h"
#include "../string.hpp"
#include <cinttypes>
#include <cstdlib>
#include "case_insenstive_string.h"

#if defined(_MSC_VER)
#   define MSVC_COMPILER 1
#elif
#   define MSVC_COMPILER 0
#endif

namespace vite
{
    template<>
    bool ConvertVariant<vite::String, bool>(const vite::String& strValue)
    {
        vite::istring value(strValue);
        if (value == "1" || value == "true" || value == "yes")
        {
            return true;
        }
        else if (value == "0" || value == "false" || value == "no")
        {
            return false;
        }
        std::stringstream errorMessage;
        errorMessage << "Invalid boolean string '" << strValue << "'.";
        throw std::runtime_error(errorMessage.str());
    }
    template<>
    bool ConvertVariant<char, bool>(const char& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::int8_t, bool>(const std::int8_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::uint8_t, bool>(const std::uint8_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::int16_t, bool>(const std::int16_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::uint16_t, bool>(const std::uint16_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::int32_t, bool>(const std::int32_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::uint32_t, bool>(const std::uint32_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::int64_t, bool>(const std::int64_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<std::uint64_t, bool>(const std::uint64_t& value)
    {
        return value != 0;
    }
    template<>
    bool ConvertVariant<long, bool>(const long& value)
    {
        return value != 0L;
    }
    template<>
    bool ConvertVariant<unsigned long, bool>(const unsigned long& value)
    {
        return value != 0L;
    }
    template<>
    bool ConvertVariant<float, bool>(const float& value)
    {
        return value != 0.0f;
    }
    template<>
    bool ConvertVariant<double, bool>(const double& value)
    {
        return value != 0.0;
    }
    template<>
    std::int8_t ConvertVariant<bool, std::int8_t>(const bool& value)
    {
        if (value)
        {
            return std::int8_t(1);
        }
        return std::int8_t(0);
    }
    template<>
    std::uint8_t ConvertVariant<bool, std::uint8_t>(const bool& value)
    {
        if (value)
        {
            return std::uint8_t(1);
        }
        return std::uint8_t(0);
    }
    template<>
    std::int16_t ConvertVariant<bool, std::int16_t>(const bool& value)
    {
        if (value)
        {
            return std::int16_t(1);
        }
        return std::int16_t(0);
    }
    template<>
    std::uint16_t ConvertVariant<bool, std::uint16_t>(const bool& value)
    {
        if (value)
        {
            return std::uint16_t(1);
        }
        return std::uint16_t(0);
    }
    template<>
    std::int32_t ConvertVariant<bool, std::int32_t>(const bool& value)
    {
        if (value)
        {
            return std::int32_t(1);
        }
        return std::int32_t(0);
    }
    template<>
    std::uint32_t ConvertVariant<bool, std::uint32_t>(const bool& value)
    {
        if (value)
        {
            return std::uint32_t(1);
        }
        return std::uint32_t(0);
    }
    template<>
    std::int64_t ConvertVariant<bool, std::int64_t>(const bool& value)
    {
        if (value)
        {
            return std::int64_t(1);
        }
        return std::int64_t(0);
    }
    template<>
    std::uint64_t ConvertVariant<bool, std::uint64_t>(const bool& value)
    {
        if (value)
        {
            return std::uint64_t(1);
        }
        return std::uint64_t(0);
    }
    template<>
    float ConvertVariant<bool, float>(const bool& value)
    {
        if (value)
        {
            return float(1);
        }
        return float(0);
    }
    template<>
    double ConvertVariant<bool, double>(const bool& value)
    {
        if (value)
        {
            return double(1.0);
        }
        return double(0.0);
    }
    template<>
    vite::String ConvertVariant<bool, vite::String>(const bool& value)
    {
        if (value)
        {
            return "true";
        }
        return "false";
    }

    template <>
    char ConvertVariant<vite::String, char>(const vite::String& value)
    {
        if (value.empty())
        {
            return '\0';
        }
        return value.asUTF8()[0];
    }
    template <>
    vite::String ConvertVariant<char, vite::String>(const char& value)
    {
        vite::String result(2, '\0');
        result[0] = value;
        return result;
    }

    template <>
    std::int8_t ConvertVariant<vite::String, std::int8_t>(const vite::String& value)
    {
        return std::int8_t(stoi(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::int8_t, vite::String>(const std::int8_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    std::uint8_t ConvertVariant<vite::String, std::uint8_t>(const vite::String& value)
    {
        return std::uint8_t(stoi(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::uint8_t, vite::String>(const std::uint8_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    std::int16_t ConvertVariant<vite::String, std::int16_t>(const vite::String& value)
    {
        return std::int16_t(stoi(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::int16_t, vite::String>(const std::int16_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    std::uint16_t ConvertVariant<vite::String, std::uint16_t>(const vite::String& value)
    {
        return std::uint16_t(stoi(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::uint16_t, vite::String>(const std::uint16_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    std::int32_t ConvertVariant<vite::String, std::int32_t>(const vite::String& value)
    {
        return std::int32_t(stol(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::int32_t, vite::String>(const std::int32_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    std::uint32_t ConvertVariant<vite::String, std::uint32_t>(const vite::String& value)
    {
        return std::uint32_t(stol(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::uint32_t, vite::String>(const std::uint32_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _ultoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _ultoa(value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    std::int64_t ConvertVariant<vite::String, std::int64_t>(const vite::String& value)
    {
        return std::int64_t(stoll(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::int64_t, vite::String>(const std::int64_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _i64toa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _i64toa(value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    long ConvertVariant<vite::String, long>(const vite::String& value)
    {
        return (long) ConvertVariant<vite::String, std::int64_t>(value);
    }
    template <>
    vite::String ConvertVariant<long, vite::String>(const long& value)
    {
        return ConvertVariant<std::int64_t, vite::String>(value);
    }

    template <>
    std::uint64_t ConvertVariant<vite::String, std::uint64_t>(const vite::String& value)
    {
        return std::uint64_t(stoll(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<std::uint64_t, vite::String>(const std::uint64_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _ui64toa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _ui64toa(value, buffer, 10);
#endif
        return vite::String(buffer);
    }

    template <>
    unsigned long ConvertVariant<vite::String, unsigned long>(const vite::String& value)
    {
        return (unsigned long)ConvertVariant<vite::String, std::uint64_t>(value);
    }
    template <>
    vite::String ConvertVariant<unsigned long, vite::String>(const unsigned long& value)
    {
        return ConvertVariant<std::uint64_t, vite::String>(value);
    }

    template <>
    float ConvertVariant<vite::String, float>(const vite::String& value)
    {
        return float(stof(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<float, vite::String>(const float& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        sprintf_s(buffer, sizeof(buffer), "%f", value);
#elif
        sprintf(buffer, "%f", value);
#endif
        return vite::String(buffer);
    }

    template <>
    double ConvertVariant<vite::String, double>(const vite::String& value)
    {
        return double(stod(value.asUTF8()));
    }
    template <>
    vite::String ConvertVariant<double, vite::String>(const double& value)
    {
        char buffer[40] = { 0 };
#if  MSVC_COMPILER
        sprintf_s(buffer, sizeof(buffer), "%f", value);
#elif
        sprintf(buffer, "%f", value);
#endif
        return vite::String(buffer);
    }

    template<>
    std::string ConvertVariant<vite::String, std::string>(const vite::String& value)
    {
        return value.asUTF8();
    }

    template<>
    std::wstring ConvertVariant<vite::String, std::wstring>(const vite::String& value)
    {
        return value.asWStr();
    }

    template <typename FromType, typename ToType>
    void RegisterCombination()
    {
        VariantConverter::add<FromType, ToType>();
        VariantConverter::add<ToType, FromType>();
    }

    template <typename T>
    void RegisterStringCombination()
    {
        RegisterCombination<T, vite::String>();
        VariantConverter::add<T, std::string>([](const void* value) -> void* {
            const T& typeValue = *static_cast<const T*>(value);
            return new std::string(ConvertVariant<T, vite::String>(typeValue).asUTF8());
        });
        VariantConverter::add<T, std::wstring>([](const void* value) -> void* {
            const T& typeValue = *static_cast<const T*>(value);
            return new std::wstring(ConvertVariant<T, vite::String>(typeValue).asWStr());
        });
    }

    template <typename FromType>
    void RegisterStdCombinations()
    {
        RegisterCombination<FromType, bool>();
        RegisterCombination<FromType, char>();
        RegisterCombination<FromType, unsigned char>();
        RegisterCombination<FromType, std::int8_t>();
        RegisterCombination<FromType, std::uint8_t>();
        RegisterCombination<FromType, short>();
        RegisterCombination<FromType, unsigned short>();
        RegisterCombination<FromType, std::int16_t>();
        RegisterCombination<FromType, std::uint16_t>();
        RegisterCombination<FromType, int>();
        RegisterCombination<FromType, unsigned int>();
        RegisterCombination<FromType, std::int32_t>();
        RegisterCombination<FromType, std::uint32_t>();
        RegisterCombination<FromType, long>();
        RegisterCombination<FromType, unsigned long>();
        RegisterCombination<FromType, std::int64_t>();
        RegisterCombination<FromType, float>();
        RegisterCombination<FromType, double>();
        RegisterStringCombination<FromType>();
    }

    StdConverters::StdConverters()
    {
        RegisterStdCombinations<bool>();
        RegisterStdCombinations<char>();
        RegisterStdCombinations<unsigned char>();
        RegisterStdCombinations<std::int8_t>();
        RegisterStdCombinations<std::uint8_t>();
        RegisterStdCombinations<short>();
        RegisterStdCombinations<unsigned short>();
        RegisterStdCombinations<std::int16_t>();
        RegisterStdCombinations<std::uint16_t>();
        RegisterStdCombinations<int>();
        RegisterStdCombinations<unsigned int>();
        RegisterStdCombinations<std::int32_t>();
        RegisterStdCombinations<std::uint32_t>();
        RegisterStdCombinations<long>();
        RegisterStdCombinations<unsigned long>();
        RegisterStdCombinations<std::int64_t>();
        RegisterStdCombinations<std::uint64_t>();
        RegisterStdCombinations<float>();
        RegisterStdCombinations<double>();
        RegisterStdCombinations<vite::String>();
    }

    StdConverters::~StdConverters()
    {
    }
}