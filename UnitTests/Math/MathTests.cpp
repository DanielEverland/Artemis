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
TEST(Math, Absolute)
{
    ExpectEqual(1, Math::Absolute(1));
    ExpectEqual(1, Math::Absolute(-1));

    ExpectEqual(Math::Infinity, Math::Absolute(Math::Infinity));
    ExpectEqual(Math::Infinity, Math::Absolute(-Math::Infinity));

    ExpectNear(2.25, Math::Absolute(-2.25));
}
TEST(Math, CopySign)
{
    ExpectEqual(-1, Math::CopySign(1, -253));
    ExpectEqual(-Math::Infinity, Math::CopySign(Math::Infinity, -253));
    ExpectEqual(1.0, Math::CopySign(1.0, 52.0));
}
TEST(Math, ArcTan2)
{
    ExpectNear(0.785398163, Math::ArcTangent2(1, 1));
    ExpectNear(-0.643501108, Math::ArcTangent2(-3, 4));
    ExpectNear(-2.498091544, Math::ArcTangent2(-1.5, -2));
    ExpectNear(2.83870778521, Math::ArcTangent2(0.75, -2.4));
}
TEST(Math, Cosine)
{
    ExpectNear(0.87758256189, Math::Cosine(0.5));
    ExpectNear(0.54030230586, Math::Cosine(1));
    ExpectNear(-0.80114361554, Math::Cosine(-2.5));
}
TEST(Math, ArcCos)
{
    ExpectNear(1.04719755, Math::ArcCosine(0.5));
    ExpectNear(Math::Pi, Math::ArcCosine(-1));
    ExpectNear(2.41885841, Math::ArcCosine(-0.75));
}
TEST(Math, Sine)
{
    ExpectNear(0.8414709848, Math::Sine(1));
    ExpectNear(-0.5984721441, Math::Sine(-2.5));
}
TEST(Math, ArcSine)
{
    ExpectNear(0.523598776, Math::ArcSine(0.5));
    ExpectNear(-1.57079633, Math::ArcSine(-1));
}
TEST(Math, Tangent)
{
    ExpectNear(1.55740772465, Math::Tangent(1));
    ExpectNear(-0.54630248984, Math::Tangent(-0.5));
}
TEST(Math, ArcTangent)
{
    ExpectNear(-0.463647609, Math::ArcTangent(-0.5));
    ExpectNear(1.10714872, Math::ArcTangent(2));
}
TEST(Math, IsFloatingPointIntegral)
{
    ExpectTrue(Math::IsFloatingPointIntegral(-3.0));
    ExpectTrue(Math::IsFloatingPointIntegral(3.0));
    ExpectFalse(Math::IsFloatingPointIntegral(3.6));
}