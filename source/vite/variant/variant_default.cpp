#include "variant_default.h"

template<>
bool vite::VariantDefault()
{
    return false;
}

template<>
char vite::VariantDefault()
{
    return '\0';
}

template<>
unsigned char vite::VariantDefault()
{
    return '\0';
}

template<>
std::int8_t vite::VariantDefault()
{
    return '\0';
}

template<>
short vite::VariantDefault()
{
    return 0;
}

template<>
unsigned short vite::VariantDefault()
{
    return 0;
}

template<>
int vite::VariantDefault()
{
    return 0;
}

template<>
unsigned int vite::VariantDefault()
{
    return 0;
}

template<>
long vite::VariantDefault()
{
    return 0L;
}

template<>
unsigned long vite::VariantDefault()
{
    return 0L;
}

template<>
long long vite::VariantDefault()
{
    return 0L;
}

template<>
unsigned long long vite::VariantDefault()
{
    return 0L;
}

template<>
float vite::VariantDefault()
{
    return 0.0f;
}

template<>
double vite::VariantDefault()
{
    return 0.0;
}

template<>
long double vite::VariantDefault()
{
    return 0.0;
}

template<>
std::string vite::VariantDefault()
{
    return std::string();
}
