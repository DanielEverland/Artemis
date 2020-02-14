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
    ExpectTrue(Math::IsNaN(Math::NaN));
}
TEST(Math, IsNaN)
{
    ExpectEqual(Math::IsNaN(1.0), std::isnan(1.0));
    ExpectEqual(Math::IsNaN(Math::NaN), std::isnan(Math::NaN));
}