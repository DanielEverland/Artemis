#include "pch.h"

#include "Engine/Math.h"
#include "Utility/Comparison/ComparisonUtility.h"

TEST(Math, NormalizeAngle)
{
    ExpectEqual(90, Math::NormalizeAngle(450));
    ExpectEqual(179, Math::NormalizeAngle(-181));
    ExpectEqual(0, Math::NormalizeAngle(720));
}
TEST(Math, NaNConst)
{
    ExpectTrue(std::isnan(Math::NaN));
}
TEST(Math, IsNaN)
{
    ExpectFalse(Math::IsNaN(1.0));
    ExpectTrue(Math::IsNaN(Math::NaN));
}
TEST(Math, Remainder)
{
    ExpectEqual(1, Math::Remainder(7, 3));
    ExpectNear(2.1, Math::Remainder(5.1, 3));
    ExpectNear(-2.1, Math::Remainder(-5.1, 3));
}