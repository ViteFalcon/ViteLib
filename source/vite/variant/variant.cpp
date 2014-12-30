#include "variant.h"

using namespace vite;

const std::type_info& Variant::VOID_TYPE = typeid(void);

template<>
const char* vite::Variant::as<const char*>() const
{
    return as<std::string>().c_str();
}
