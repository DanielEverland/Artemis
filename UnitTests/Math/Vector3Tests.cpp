#include "gtest/gtest.h"
#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Include/Game/Vector3.h"
#include "Include/Game/Vector2.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

    TEST(Vector3, ConstructorXY)
    {
        Vector3 vector(10.0, 20.25);


        ExpectNear(10.0, vector.X);
        ExpectNear(20.25, vector.Y);
    }
    TEST(Vector3, ConstructorXYZ)
    {
        Vector3 vector(10.0, 20.25, 30.20);


        ExpectNear(10.0, vector.X);
        ExpectNear(20.25, vector.Y);
        ExpectNear(30.20, vector.Z);
    }
    TEST(Vector3, InitializerListConstructor)
    {
        Vector3 vector({ 43.51, 2.0, 12.3, 153.0154 });


        ExpectNear(43.51, vector.X);
        ExpectNear(2.0, vector.Y);
        ExpectNear(12.3, vector.Z);
    }
    TEST(Vector3, IntConstructorXY)
    {
        Vector3 vector(1, 2);


        ExpectEqual(1, vector.X);
        ExpectEqual(2, vector.Y);
    }
    TEST(Vector3, IntConstructorXYZ)
    {
        Vector3 vector(1, 2, 3);


        ExpectEqual(1, vector.X);
        ExpectEqual(2, vector.Y);
        ExpectEqual(3, vector.Z);
    }
    TEST(Vector3, MemberAssignment)
    {
        Vector3 vector;


        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;


        ExpectEqual(5, vector.X);
        ExpectEqual(10, vector.Y);
        ExpectEqual(1, vector.Z);
    }
    TEST(Vector3, CrossProduct)
    {
        Vector3 a(1, 2, 3);
        Vector3 b(4, 5, 6);


        Vector3 c = Vector3::GetCrossProduct(a, b);


        ExpectEqual(-3, c.X);
        ExpectEqual(6, c.Y);
        ExpectEqual(-3, c.Z);
    }
    TEST(Vector3, UpgradeVector2)
    {
        Vector3 expectedResult(154.14, 12.4, 0);
        Vector2 vector(154.14, 12.4);


        Vector3 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(Vector3, UpgradeIntVector2)
    {
        Vector3 expectedResult(154, 12, 0);
        Vector2 vector(154, 12);


        Vector3 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
}