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
#include "vite_lib_tests.h"
#include "test_ini_writer.h"

#include <vite/config.hpp>

#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;

class ConfigTest : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        //
    }

    inline TestIniWriter writer()
    {
        return TestIniWriter(TEST_FILE.c_str());
    }

    inline vite::Config openConfig() const
    {
        return vite::Config(TEST_FILE.c_str());
    }

    virtual void TearDown() override
    {
        if (bf::exists(TEST_FILE))
        {
            bf::remove(TEST_FILE);
        }
    }

private:
    static const bf::path TEST_FILE;
};

const bf::path ConfigTest::TEST_FILE("test_cfg.ini");

TEST_F(ConfigTest, BooleanRootValue_WhenTrue)
{
    const char* key = "bool_key";
    writer().addEntry(key, "true").close();
    vite::Config config = openConfig();
    ASSERT_TRUE(config.get(key).as<bool>());
}

TEST_F(ConfigTest, BooleanRootValue_WhenFalse)
{
    const char* key = "bool_key";
    writer().addEntry(key, "false").close();
    vite::Config config = openConfig();
    ASSERT_FALSE(config.get(key).as<bool>());
}

TEST_F(ConfigTest, BooleanSectionValue_WhenTrue)
{
    const char* section = "test";
    const char* key = "bool_key";
    writer().addSection(section).addEntry(key, "true").close();
    vite::Config config = openConfig();
    ASSERT_TRUE(config.get("test.bool_key").as<bool>());
}