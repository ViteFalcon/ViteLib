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