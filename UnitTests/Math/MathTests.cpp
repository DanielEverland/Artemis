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
TEST(Math, RadiansToDegrees)
{
    ExpectEqual(0, Math::RadiansToDegrees(0));
    ExpectNear(57.295779513082323, Math::RadiansToDegrees(1));
    ExpectNear(5.7295779513082321, Math::RadiansToDegrees(0.1));
    ExpectNear(-5.7295779513082321, Math::RadiansToDegrees(-0.1));
    ExpectNear(28.647889756541161, Math::RadiansToDegrees(0.5));
}
TEST(Math, DegreesToRadians)
{
    ExpectEqual(0, Math::RadiansToDegrees(0));
    ExpectNear(0.6108652381980153, Math::DegreesToRadians(35));
    ExpectNear(-0.6108652381980153, Math::DegreesToRadians(-35));
    ExpectNear(Math::Pi, Math::DegreesToRadians(180));
}
TEST(Math, Squared)
{
    ExpectEqual(4, Math::Square(2));
    ExpectEqual(4, Math::Square(-2));
    ExpectNear(0.0625, Math::Square(0.25));
    ExpectNear(30.25, Math::Square(5.5));
}
TEST(Math, Power)
{
    ExpectEqual(3125, Math::Power(5, 5));
    ExpectNear(0.2, Math::Power(5, -1));
    ExpectNear(55.9016994375, Math::Power(5, 2.5));
}
TEST(Math, SquareRoot)
{
    ExpectEqual(5, Math::SquareRoot(25));
    ExpectNear(1.41421356237, Math::SquareRoot(2));
    ExpectTrue(Math::IsNaN(Math::SquareRoot(-1)));
}