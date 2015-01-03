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

TEST(VariantTests, EmptyVariant_IsEmpty)
{
    vite::Variant variant;
    ASSERT_TRUE(variant.empty());
}

TEST(VariantTests, EmptyVariant_AsBool_ReturnsFalse)
{
    vite::Variant emptyVariant;
    ASSERT_FALSE(emptyVariant.as<bool>());
}

TEST(VariantTests, EmptyVariant_AsInt8_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::int8_t>());
}

TEST(VariantTests, EmptyVariant_AsUInt8_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::uint8_t>());
}

TEST(VariantTests, EmptyVariant_AsInt16_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::int16_t>());
}

TEST(VariantTests, EmptyVariant_AsUInt16_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::uint16_t>());
}

TEST(VariantTests, EmptyVariant_AsInt32_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::int32_t>());
}

TEST(VariantTests, EmptyVariant_AsUInt32_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::uint32_t>());
}

TEST(VariantTests, EmptyVariant_AsInt64_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::int64_t>());
}

TEST(VariantTests, EmptyVariant_AsUInt64_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0, emptyVariant.as<std::uint64_t>());
}

TEST(VariantTests, EmptyVariant_AsFloat_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0.0f, emptyVariant.as<float>());
}

TEST(VariantTests, EmptyVariant_AsDouble_ReturnsZero)
{
    vite::Variant emptyVariant;
    ASSERT_EQ(0.0, emptyVariant.as<double>());
}

TEST(VariantTests, EmptyVariant_AsString_ReturnsEmptyString)
{
    vite::Variant emptyVariant;
    ASSERT_EQ("", emptyVariant.as<std::string>());
}
