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

#include <utility>
#include <ostream>

namespace vite
{
    template <class Tag, typename Type, Type DefaultValue>
    class Id
    {
    public: // static
        static Id Invalid()
        {
            return Id();
        }

    public:
        explicit Id(const Type& value) : mValue(value) {}
        Id(const Id& other) : mValue(other.mValue) {}
        Id(Id&& other) : mValue(std::move(other.mValue)) {}

        Id& operator = (const Id& other)
        {
            mValue = other.mValue;
            return *this;
        }

        bool operator == (const Id& other) const
        {
            return mValue == other.mValue;
        }

        bool operator != (const Id& other) const
        {
            return mValue != other.mValue;
        }

        bool operator < (const Id& other) const
        {
            using std::less;
            return less<Type>()(mValue, other.mValue);
        }

        bool isInvalid() const
        {
            return mValue == DefaultValue;
        }

        std::size_t getHashCode() const
        {
            using std::hash;
            return hash<Type>()(mValue);
        }

        friend std::ostream& operator << (std::ostream& os, const Id& id)
        {
            return os << id.mValue;
        }

    private: // Method
        Id() : mValue(DefaultValue) {}

    private: // Fields
        Type mValue;
    };
}

namespace std
{
    template<class Tag, typename Type, Type DefaultValue>
    struct hash < vite::Id<Tag, Type, DefaultValue> >
    {
        typedef vite::Id<Tag, Type, DefaultValue> argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& value) const
        {
            return value.getHashCode();
        }
    };
}

namespace boost
{
    template <class Tag, typename Type, Type DefaultValue>
    size_t hash_value(const vite::Id < Tag, Type, DefaultValue > &id)
    {
        return id.getHashCode();
    }
}