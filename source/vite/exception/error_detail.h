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

#include "../defines.hpp"
#include "../string.hpp"

namespace vite
{
    namespace inner
    {
        struct ErrorInfo
        {
            virtual ErrorInfo* clone() const = 0;
            virtual std::string toString() const = 0;
        };

        template <typename ErrorInfoType>
        struct ErrorDetail : ErrorInfo
        {
        public:
            ErrorDetail(const char* name_, const ErrorInfoType _value)
                : name(name_), value(_value) {}

            virtual ErrorInfo* clone() const override
            {
                return new ErrorDetail<ErrorInfoType>(name.c_str(), value);
            }

            virtual std::string toString() const override
            {
                std::stringstream errorDetail;
                errorDetail << name << ": " << value;
                return errorDetail.str();
            }
        protected:
            const std::string name;
            const ErrorInfoType value;
        };
    }
}

#define vERROR_INFO_NAME(name) vCOMBINE(ErrorInfo,name)
#define vERROR_INFO(name, type) struct vERROR_INFO_NAME(name) : vite::inner::ErrorDetail<type>\
{\
    vERROR_INFO_NAME(name)(const type val)\
        : ErrorDetail(vSTRINGIFY(name), val)\
    {\
    }\
}
#define vERROR_INFO_STRING(name) vERROR_INFO(name, vite::String)

#define vLIB_DECLARE_ERROR_INFO(name, type) struct vLIB_EXPORT vERROR_INFO_NAME(name) : vite::inner::ErrorDetail<type>\
{\
    vERROR_INFO_NAME(name)(const type val);\
}
#define vLIB_DEFINE_ERROR_INFO(name, type) vERROR_INFO_NAME(name)::vERROR_INFO_NAME(name)(const type val) : vite::inner::ErrorDetail<type>(vSTRINGIFY(name), val){}

#define vLIB_DECLARE_ERROR_INFO_STRING(name) vLIB_DECLARE_ERROR_INFO(name, vite::String)
#define vLIB_DEFINE_ERROR_INFO_STRING(name) vLIB_DEFINE_ERROR_INFO(name, vite::String)

namespace vite
{
    vLIB_DECLARE_ERROR_INFO_STRING(Detail);
    vLIB_DECLARE_ERROR_INFO_STRING(Hint);
    vLIB_DECLARE_ERROR_INFO_STRING(FileName);

    struct vLIB_EXPORT ErrorInfoCausedBy : inner::ErrorInfo
    {
    public:
        ErrorInfoCausedBy(const std::exception& cause_);
        virtual inner::ErrorInfo* clone() const override;
        virtual std::string toString() const override;
    private:
        const std::exception& cause;
    };
}