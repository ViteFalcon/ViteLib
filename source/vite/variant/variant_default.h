#pragma once
#include <cinttypes>
#include <sstream>

namespace vite
{
    template <typename T>
    T VariantDefault()
    {
        std::stringstream errorMessage;
        errorMessage << "No default value specified for variant type of " << typeid(T).name();
        throw new std::runtime_error(errorMessage.str());
    }

    template<>
    bool VariantDefault<bool>();

    template<>
    char VariantDefault<char>();

    template<>
    unsigned char VariantDefault<unsigned char>();

    template<>
    std::int8_t VariantDefault<std::int8_t>();

    template<>
    std::uint8_t VariantDefault<std::uint8_t>();

    template<>
    short VariantDefault<short>();

    template<>
    unsigned short VariantDefault<unsigned short>();

    template<>
    int VariantDefault<int>();

    template<>
    unsigned int VariantDefault<unsigned int>();

    template<>
    long VariantDefault<long>();

    template<>
    unsigned long VariantDefault<unsigned long>();

    template<>
    long long VariantDefault<long long>();

    template<>
    unsigned long long VariantDefault<unsigned long long>();

    template<>
    float VariantDefault<float>();

    template<>
    double VariantDefault<double>();

    template<>
    long double VariantDefault<long double>();

    template<>
    std::string VariantDefault<std::string>();
}

