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
#include <iostream>

TEST(VariantTests, EmtpyString_AsInt_ThrowsException)
{
    vite::Variant emptyString("");
    ASSERT_ANY_THROW(emptyString.as<int>());
}

TEST(VariantTests, NumberString_AsInt_ReturnsNumber)
{
    vite::Variant number("123");
    ASSERT_EQ(123, number.as<int>());
}

TEST(VariantTests, NumberString_AsFloat_ReturnsFloat)
{
    vite::Variant number("123");
    ASSERT_EQ(123.0f, number.as<float>());
}

TEST(VariantTests, FloatString_AsInt_ReturnsInt)
{
    vite::Variant number("123.45");
    ASSERT_EQ(123, number.as<int>());
}

TEST(VariantTests, NonNumberString_AsInt_ThrowsException)
{
    vite::Variant number("blah");
    ASSERT_ANY_THROW(number.as<int>());
}

TEST(VariantTests, FloatString_AsFloat_ReturnsFloat)
{
    vite::Variant number("123.45");
    ASSERT_EQ(123.45f, number.as<float>());
}

TEST(VariantTests, NonNumberString_AsFloat_ThrowsException)
{
    vite::Variant string("not a number");
    ASSERT_ANY_THROW(string.as<float>());
}

TEST(VariantTests, DoubleString_AsDouble_ReturnsDouble)
{
    vite::Variant number("123.45");
    ASSERT_EQ(123.45, number.as<double>());
}

TEST(VariantTests, NonNumberString_AsDouble_ThrowsException)
{
    vite::Variant string("not a number");
    ASSERT_ANY_THROW(string.as<double>());
}

TEST(VariantTests, NumberVariant_AsString_GetsCorrectString)
{
    vite::Variant number(1234);
    ASSERT_EQ("1234", number.as<std::string>());
}

TEST(VariantTests, FloatVariant_AsInt_GetsIntegerPart)
{
    vite::Variant floatValue(2.5f);
    ASSERT_EQ(2, floatValue.as<int>());
}

TEST(VariantTests, IntVariant_AsFloat_GetsIntegerPart)
{
    vite::Variant floatValue(2);
    ASSERT_EQ(2.0f, floatValue.as<int>());
}

TEST(VariantTests, FloatStringVariant_AsInt_GetsIntegerPart)
{
    vite::Variant floatValue("2.5");
    ASSERT_EQ(2, floatValue.as<int>());
}

TEST(VariantTests, FloatStringVariant_AsFloat_GetsIntegerPart)
{
    vite::Variant floatValue("2.5");
    ASSERT_EQ(2.5f, floatValue.as<float>());
}

TEST(VariantTests, FloatStringVariant_AsDouble_GetsIntegerPart)
{
    vite::Variant floatValue("2.5");
    ASSERT_EQ(2.5, floatValue.as<double>());
}

TEST(VariantTests, FloatStringVariant_WithF_AsFloat_GetsIntegerPart)
{
    vite::Variant floatValue("2.5f");
    ASSERT_EQ(2.5f, floatValue.as<float>());
}