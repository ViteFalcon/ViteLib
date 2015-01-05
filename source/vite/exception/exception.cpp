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
#include "exception.h"
#include <boost/exception/all.hpp>
#include <list>

#define vMAX_ERROR_MESSAGE_SIZE 10240

namespace vite
{
    class Exception::ErrorDetails
    {
    public:
        typedef std::list<vite::inner::ErrorInfo*> Details;

        ErrorDetails() = default;
        ~ErrorDetails()
        {
            Details::iterator itr = details.begin(), end = details.end();
            while (itr != end)
            {
                delete *itr++;
            }
            details.clear();
        }

        ErrorDetails& push_back(const vite::inner::ErrorInfo& detail)
        {
            details.push_back(detail.clone());
            return *this;
        }

        ErrorDetails& push_front(const vite::inner::ErrorInfo& detail)
        {
            details.push_front(detail.clone());
            return *this;
        }

        inline Details::const_iterator begin() const
        {
            return details.begin();
        }

        inline Details::const_iterator end() const
        {
            return details.end();
        }

    private:
        Details details;
    };

    struct ThrowFunction : inner::ErrorInfo
    {
        ThrowFunction(const char* function_)
            : function(function_) {}

        virtual inner::ErrorInfo* clone() const override
        {
            return new ThrowFunction(function);
        }

        virtual std::string toString() const override
        {
            std::stringstream errorDetail;
            errorDetail << "Thrown from function: " << function;
            return errorDetail.str();
        }
    private:
        const char* function;
    };

    struct ThrowFile : vite::inner::ErrorInfo
    {
        ThrowFile(const char* file_)
            : file(file_) {}

        virtual inner::ErrorInfo* clone() const override
        {
            return new ThrowFile(file);
        }

        virtual std::string toString() const override
        {
            std::stringstream errorDetail;
            errorDetail << "Thrown from file: " << file;
            return errorDetail.str();
        }
    private:
        const char* file;
    };

    struct ThrowLine : vite::inner::ErrorInfo
    {
        ThrowLine(const int line_)
            : line(line_) {}

        virtual inner::ErrorInfo* clone() const override
        {
            return new ThrowLine(line);
        }

        virtual std::string toString() const override
        {
            std::stringstream errorDetail;
            errorDetail << "Thrown in line: " << line;
            return errorDetail.str();
        }

    private:
        const int line;
    };
}

std::string vite::Exception::toString() const
{
    std::stringstream errorWhat;
    errorWhat << "Exception: " << typeid(*this).name();
    auto itr = details->begin(), end = details->end();
    while (itr != end)
    {
        vite::inner::ErrorInfo& errorInfo = *(*itr++);
        errorWhat << std::endl << "    " << errorInfo.toString();
    }
    return errorWhat.str().c_str();
}

const char* vite::Exception::what() const
{
    try {
        static char error_message[vMAX_ERROR_MESSAGE_SIZE];
        const std::string errorString = toString();
#if vCOMPILER_IS_MSVC
        memcpy_s(error_message, vMAX_ERROR_MESSAGE_SIZE, errorString.c_str(), errorString.length() + 1);
#else
        const size_t minSize = std::min<size_t>(errorString.length(), vMAX_ERROR_MESSAGE_SIZE);
        memcpy(error_message, errorString.c_str(), minSize);
#endif
        return error_message;
    } catch (...) {}
    return typeid(*this).name();
}

void vite::Exception::Throw(Exception& exception, const char* currentFunction, const char* currentFile, int currentLine)
{
    try {
        Exception::ErrorDetails& details = *exception.details;
        details.push_front(ThrowLine(currentLine)).push_front(ThrowFile(currentFile)).push_front(ThrowFunction(currentFunction));
    } catch (...) {}
    throw exception;
}

vite::Exception::Exception()
    : details(new ErrorDetails())
{
}

vite::Exception::Exception(const char* typeName)
#if _WIN32
    : std::exception(typeName)
    , details(new ErrorDetails())
#endif
{
}

vite::Exception& vite::Exception::operator<<(const vite::inner::ErrorInfo& info)
{
    try {
        details->push_back(info);
    } catch (...) {}
    return *this;
}

#define vDEFINE_LIB_EXCEPTION(classname)  vite::classname::classname() : Exception(vSTRINGIFY(classname)) {}

vDEFINE_LIB_EXCEPTION(FileNotFoundException)
vDEFINE_LIB_EXCEPTION(IllegalArgumentException)
vDEFINE_LIB_EXCEPTION(InvalidOperationException)
vDEFINE_LIB_EXCEPTION(InvalidStateException)
vDEFINE_LIB_EXCEPTION(ItemNotFoundException)
vDEFINE_LIB_EXCEPTION(NotImplementedException)
vDEFINE_LIB_EXCEPTION(RuntimeException)