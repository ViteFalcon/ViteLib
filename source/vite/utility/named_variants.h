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
#include "../variant.hpp"
#include <unordered_map>

namespace vite
{
    class vLIB_EXPORT NamedVariants
    {
    public: // static
        static const NamedVariants EMPTY;
    public:
        NamedVariants() = default;

        template<typename T>
        void set(const String& name, const T& value)
        {
            setVariant(name, Variant(value));
        }

        template<>
        void set<Variant>(const String& name, const Variant& value);

        template <typename T>
        vINLINE Optional<T> get(const String& name) const
        {
            auto value = get(name);
            if (value.isPresent())
            {
                return value.getValue().maybeAs<T>();
            }
            return Optional<T>::Absent();
        }

        bool hasKey(const String& name) const;

        vINLINE bool isEmpty() const
        {
            return mVariants.empty();
        }

    private: // methods
        void setVariant(const String& name, const Variant& value);

        Optional<Variant> getVariant(const String& name) const;

    private:
        typedef std::unordered_map<String, Variant> Map;

        Map mVariants;
    };
}