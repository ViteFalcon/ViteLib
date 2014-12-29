// vite::VariantTest.cpp : Defines the entry point for the console application.
//

#include <vite_lib_tests.h>
#include <vite/variant.hpp>
#include <iostream>

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