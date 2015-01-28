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
#include "ioc.h"
#include "../exception.hpp"

#include <sstream>
#include <unordered_map>

namespace vite
{
    class InstanceOfImpl : public InstanceOf
    {
    protected:
        virtual std::string useInstanceFactoryForType(const std::shared_ptr<InstanceFactory>& factoryInstance, const std::type_info& forType) override
        {
            return useInstanceFactoryForTypeNamed(factoryInstance, forType.name());
        }

        virtual std::string useInstanceFactoryForTypeNamed(const std::shared_ptr<InstanceFactory>& factoryInstance, const std::string& name) override
        {
            mFactories[name] = factoryInstance;
            return name;
        }

        virtual Variant getInstanceForType(const std::type_info& type) override
        {
            return getInstanceNamed(type.name());
        }

        virtual Variant getInstanceNamed(const std::string& name) override;

        virtual bool hasFactoryForInstanceType(const std::type_info& type) override
        {
            return hasFactoryForInstanceNamed(type.name());
        }

        virtual bool hasFactoryForInstanceNamed(const std::string& name) override
        {
            return mFactories.count(name) != 0;
        }

    private:
        typedef std::shared_ptr<InstanceFactory> InstanceFactoryPtr;
        typedef std::unordered_map<std::string, InstanceFactoryPtr> InstanceFactories;

        InstanceFactories mFactories;
    };

    vite::Variant InstanceOfImpl::getInstanceNamed(const std::string& name)
    {
        auto itr = mFactories.find(name);
        if (itr == mFactories.end())
        {
            std::stringstream errorDetail;
            errorDetail << "Failed to find instance factory for '" << name << "'";
            vTHROW(ItemNotFoundException() << ErrorInfoDetail(errorDetail.str()));
        }
        return itr->second->getInstance();
    }

    InstanceFactory::~InstanceFactory()
    {
    }

    Variant& InstanceFactory::getInstance()
    {
        if (mInstance.empty())
        {
            mInstance = createInstance();
        }
        return mInstance;
    }

    InstanceOf& InstanceOf::GetSingleton()
    {
        static InstanceOfImpl impl;
        return impl;
    }
}