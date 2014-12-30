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
