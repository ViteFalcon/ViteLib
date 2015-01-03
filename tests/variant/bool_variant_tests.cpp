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
#include <vite_lib_tests.h>
#include <vite/variant.hpp>

TEST(VariantTests, TrueBool_AsBool_ReturnsTrue)
{
    vite::Variant trueVariant(true);
    ASSERT_EQ(true, trueVariant.as<bool>());
}

TEST(VariantTests, TrueBool_AsString_ReturnsTrue)
{
    vite::Variant trueVariant(true);
    ASSERT_EQ("true", trueVariant.as<std::string>());
}

TEST(VariantTests, TrueString_AsBool_ReturnsTrue)
{
    vite::Variant trueVariant("true");
    ASSERT_TRUE(trueVariant.as<bool>());
}

TEST(VariantTests, FalseString_AsBool_ReturnsFalse)
{
    vite::Variant falseString("false");
    ASSERT_FALSE(falseString.as<bool>());
}

TEST(VariantTests, YesString_AsBool_ReturnsTrue)
{
    vite::Variant yesVariant("yes");
    ASSERT_TRUE(yesVariant.as<bool>());
}

TEST(VariantTests, NoString_AsBool_ReturnsFalse)
{
    vite::Variant no("no");
    ASSERT_FALSE(no.as<bool>());
}

TEST(VariantTests, OneString_AsBool_ReturnsTrue)
{
    vite::Variant one("1");
    ASSERT_TRUE(one.as<bool>());
}

TEST(VariantTests, ZeroString_AsBool_ReturnsFalse)
{
    vite::Variant zero("0");
    ASSERT_FALSE(zero.as<bool>());
}

TEST(VariantTests, NonBoolString_AsBool_ThrowsException)
{
    vite::Variant someString("blah");
    ASSERT_ANY_THROW(someString.as<bool>());
}

TEST(VariantTests, EmptyString_AsBool_ThrowsException)
{
    vite::Variant emptyString("");
    ASSERT_ANY_THROW(emptyString.as<bool>());
}