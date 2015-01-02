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
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable : 4503)
#endif

#include "config.h"
#include "../defines.hpp"
#include "../exception.hpp"

#include <fstream>
#include <unordered_map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace vite
{
    class Config::ConfigValues
    {
    public:
        typedef std::unordered_map<String, Variant> MapType;
        typedef MapType::const_iterator const_iterator;

        void insert(const String& key, const Variant& value)
        {
            mMap[key] = value;
        }

        const_iterator find(const String& key) const
        {
            return mMap.find(key);
        }

        const_iterator end() const
        {
            return mMap.end();
        }

        void swap(ConfigValues& other)
        {
            other.mMap.swap(mMap);
        }
    private:
        MapType mMap;
    };
}

vite::Config::Config(const String& filePath)
    : mConfigurations(new vite::Config::ConfigValues())
{
}

vite::Config::~Config()
{
    delete mConfigurations;
}


void vite::Config::loadFile(const String& filePath)
{
    try
    {
        std::ifstream file;
#if vOS_IS_WINDOWS
        file.open(filePath.asWStr_c_str(), std::ios::in | std::ios::binary);
#else
        file.open(filePath.asUTF8_c_str(), std::ios::in | std::ios::binary);
#endif
        if (!file.is_open())
        {
            vTHROW(FileNotFoundException() << ErrorInfoFileName(filePath));
        }

        String fileContent = String::FromStream(file);
        std::wstringstream textStream;
        textStream.write(fileContent.asWStr_c_str(), fileContent.size());

        using namespace boost::property_tree;
        wptree propertyTree;
        ini_parser::read_ini(textStream, propertyTree);
        wptree::iterator
            sectionItr = propertyTree.begin(),
            sectionEnd = propertyTree.end();
        ConfigValues configuration;
        while (sectionItr != sectionEnd)
        {
            const String sectionName = sectionItr->first;
            wptree::iterator
                settingItr = sectionItr->second.begin(),
                settingEnd = sectionItr->second.end();
            while (settingItr != settingEnd)
            {
                const String settingName((sectionName + L"." + settingItr->first).asUTF8_c_str());
                const Variant settingValue(settingItr->second.get_value<std::wstring>());

                configuration.insert(settingName, settingValue);

                ++settingItr;
            }
            ++sectionItr;
        }
        mConfigurations->swap(configuration);
    }
    catch (boost::exception& ex)
    {
        ex << ErrorInfoFileName(filePath);
        throw;
    }
    catch (std::exception& ex)
    {
        vTHROW(Exception()
            << ErrorInfoDetail(ex.what())
            << ErrorInfoFileName(filePath)
            << ErrorInfoCausedBy(ex));
    }
}

vite::Variant vite::Config::get(const String& key) const
{
    const ConfigValues::const_iterator valueIterator = mConfigurations->find(key);
    if (valueIterator == mConfigurations->end())
    {
        vTHROW(ItemNotFoundException() << ErrorInfoDetail(key));
    }
    return valueIterator->second;
}

#if defined(_MSC_VER)
#   pragma warning(pop)
#endif