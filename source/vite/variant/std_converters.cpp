#include "std_converters.h"
#include "variant_converter.h"
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
    bool ConvertVariant<std::string, bool>(const std::string& strValue)
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
    std::string ConvertVariant<bool, std::string>(const bool& value)
    {
        if (value)
        {
            return "true";
        }
        return "false";
    }

    template <>
    char ConvertVariant<std::string, char>(const std::string& value)
    {
        if (value.empty())
        {
            return '\0';
        }
        return value[0];
    }
    template <>
    std::string ConvertVariant<char, std::string>(const char& value)
    {
        std::string result(2, '\0');
        result[0] = value;
        return result;
    }

    template <>
    std::int8_t ConvertVariant<std::string, std::int8_t>(const std::string& value)
    {
        return std::int8_t(stoi(value));
    }
    template <>
    std::string ConvertVariant<std::int8_t, std::string>(const std::int8_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    std::uint8_t ConvertVariant<std::string, std::uint8_t>(const std::string& value)
    {
        return std::uint8_t(stoi(value));
    }
    template <>
    std::string ConvertVariant<std::uint8_t, std::string>(const std::uint8_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    std::int16_t ConvertVariant<std::string, std::int16_t>(const std::string& value)
    {
        return std::int16_t(stoi(value));
    }
    template <>
    std::string ConvertVariant<std::int16_t, std::string>(const std::int16_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    std::uint16_t ConvertVariant<std::string, std::uint16_t>(const std::string& value)
    {
        return std::uint16_t(stoi(value));
    }
    template <>
    std::string ConvertVariant<std::uint16_t, std::string>(const std::uint16_t& value)
    {
        char buffer[4] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    std::int32_t ConvertVariant<std::string, std::int32_t>(const std::string& value)
    {
        return std::int32_t(stol(value));
    }
    template <>
    std::string ConvertVariant<std::int32_t, std::string>(const std::int32_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _itoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _itoa((int)value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    std::uint32_t ConvertVariant<std::string, std::uint32_t>(const std::string& value)
    {
        return std::uint32_t(stol(value));
    }
    template <>
    std::string ConvertVariant<std::uint32_t, std::string>(const std::uint32_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _ultoa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _ultoa(value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    std::int64_t ConvertVariant<std::string, std::int64_t>(const std::string& value)
    {
        return std::int64_t(stoll(value));
    }
    template <>
    std::string ConvertVariant<std::int64_t, std::string>(const std::int64_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _i64toa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _i64toa(value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    long ConvertVariant<std::string, long>(const std::string& value)
    {
        return (long) ConvertVariant<std::string, std::int64_t>(value);
    }
    template <>
    std::string ConvertVariant<long, std::string>(const long& value)
    {
        return ConvertVariant<std::int64_t, std::string>(value);
    }

    template <>
    std::uint64_t ConvertVariant<std::string, std::uint64_t>(const std::string& value)
    {
        return std::uint64_t(stoll(value));
    }
    template <>
    std::string ConvertVariant<std::uint64_t, std::string>(const std::uint64_t& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        _ui64toa_s((int)value, buffer, sizeof(buffer), 10);
#else
        _ui64toa(value, buffer, 10);
#endif
        return std::string(buffer);
    }

    template <>
    unsigned long ConvertVariant<std::string, unsigned long>(const std::string& value)
    {
        return (unsigned long)ConvertVariant<std::string, std::uint64_t>(value);
    }
    template <>
    std::string ConvertVariant<unsigned long, std::string>(const unsigned long& value)
    {
        return ConvertVariant<std::uint64_t, std::string>(value);
    }

    template <>
    float ConvertVariant<std::string, float>(const std::string& value)
    {
        return float(stof(value));
    }
    template <>
    std::string ConvertVariant<float, std::string>(const float& value)
    {
        char buffer[21] = { 0 };
#if MSVC_COMPILER
        sprintf_s(buffer, sizeof(buffer), "%f", value);
#elif
        sprintf(buffer, "%f", value);
#endif
        return std::string(buffer);
    }

    template <>
    double ConvertVariant<std::string, double>(const std::string& value)
    {
        return double(stod(value));
    }
    template <>
    std::string ConvertVariant<double, std::string>(const double& value)
    {
        char buffer[40] = { 0 };
#if  MSVC_COMPILER
        sprintf_s(buffer, sizeof(buffer), "%f", value);
#elif
        sprintf(buffer, "%f", value);
#endif
        return std::string(buffer);
    }

    template <typename FromType, typename ToType>
    void RegisterCombination()
    {
        VariantConverter::add<FromType, ToType>();
        VariantConverter::add<ToType, FromType>();
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
        RegisterCombination<FromType, std::string>();
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
        RegisterStdCombinations<std::string>();
    }


    StdConverters::~StdConverters()
    {
    }
}