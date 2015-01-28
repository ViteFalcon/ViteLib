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
#include "../variant.hpp"

#include <typeinfo>

namespace vite
{
    class InstanceOf;

    class vLIB_EXPORT InstanceFactory
    {
    public:
        InstanceFactory() = default;
        virtual ~InstanceFactory();

        virtual Variant& getInstance();

    protected:
        virtual Variant createInstance() = 0;

    private:
        Variant mInstance;
    };

    template <typename T>
    class InstanceFactoryImpl : public InstanceFactory
    {
    protected:
        virtual Variant createInstance() override
        {
            return Variant(new T());
        }
    };

    class InstanceOf;

    template <typename T>
    class InstanceBuilder
    {
    public:
        InstanceBuilder(InstanceOf& creator) : mCreator(creator) {}
        InstanceBuilder(InstanceBuilder&& other) : mCreator(other.mCreator) {}

        template <typename InstanceType> 
        std::string useInstanceOf()
        {
            return useInstanceFactory<InstanceFactoryImpl<InstanceType>>();
        }

        template <typename FactoryType>
        std::string useInstanceFactory();
    private:
        InstanceOf& mCreator;
    };

    class vLIB_EXPORT InstanceOf
    {
    public: // static
        template <typename T>
        static inline InstanceBuilder<T> ForClass()
        {
            return InstanceBuilder<T>(GetSingleton());
        }

        template <typename T>
        static T& Get()
        {
            Variant instance = GetSingleton().getInstanceForType(typeid(T));
            return *instance.as<T*>();
        }

        template <typename T>
        static T& Get(const std::string& name)
        {
            Variant instance = GetSingleton().getInstanceNamed(name);
            return *instance.as<T*>();
        }

        template <typename T>
        static bool Exists()
        {
            return GetSingleton().hasFactoryForInstanceType(typeid(T));
        }

        static bool Exists(const std::string& name)
        {
            return GetSingleton().hasFactoryForInstanceNamed(name);
        }

    public: // methods
        template <typename FactoryType>
        std::string useInstanceFactory(const std::type_info& forType)
        {
            return useInstanceFactoryForType(std::make_shared<FactoryType>(), forType);
        }

    protected: // methods
        InstanceOf() = default;
        ~InstanceOf() = default;

        InstanceOf(const InstanceOf& other) = delete;
        InstanceOf& operator = (const InstanceOf& other) = delete;

        virtual std::string useInstanceFactoryForType(const std::shared_ptr<InstanceFactory>& factoryInstance, const std::type_info& forType) = 0;
        virtual std::string useInstanceFactoryForTypeNamed(const std::shared_ptr<InstanceFactory>& factoryInstance, const std::string& name) = 0;

        virtual Variant getInstanceForType(const std::type_info& type) = 0;
        virtual Variant getInstanceNamed(const std::string& name) = 0;

        virtual bool hasFactoryForInstanceType(const std::type_info& type) = 0;
        virtual bool hasFactoryForInstanceNamed(const std::string& name) = 0;

    private: // static
        static InstanceOf& GetSingleton();
    };

    template <typename T>
    template <typename FactoryType>
    std::string InstanceBuilder<T>::useInstanceFactory()
    {
        return mCreator.useInstanceFactory<FactoryType>(typeid(T));
    }
}