#include "gtest/gtest.h"
#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Engine/Vector3.h"
#include "Engine/Vector2.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

    TEST(Vector3, ConstructorXY)
    {
        Vector3 vector(10.0, 20.25);


        TempExpectNear(10.0, vector.X);
        TempExpectNear(20.25, vector.Y);
    }
    TEST(Vector3, ConstructorXYZ)
    {
        Vector3 vector(10.0, 20.25, 30.20);


        TempExpectNear(10.0, vector.X);
        TempExpectNear(20.25, vector.Y);
        TempExpectNear(30.20, vector.Z);
    }
    TEST(Vector3, InitializerListConstructor)
    {
        Vector3 vector({ 43.51, 2.0, 12.3, 153.0154 });


        TempExpectNear(43.51, vector.X);
        TempExpectNear(2.0, vector.Y);
        TempExpectNear(12.3, vector.Z);
    }
    TEST(Vector3, IntConstructorXY)
    {
        Vector3 vector(1, 2);


        TempExpectEqual(1, vector.X);
        TempExpectEqual(2, vector.Y);
    }
    TEST(Vector3, IntConstructorXYZ)
    {
        Vector3 vector(1, 2, 3);


        TempExpectEqual(1, vector.X);
        TempExpectEqual(2, vector.Y);
        TempExpectEqual(3, vector.Z);
    }
    TEST(Vector3, MemberAssignment)
    {
        Vector3 vector;


        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;


        TempExpectEqual(5, vector.X);
        TempExpectEqual(10, vector.Y);
        TempExpectEqual(1, vector.Z);
    }
    TEST(Vector3, CrossProduct)
    {
        Vector3 a(1, 2, 3);
        Vector3 b(4, 5, 6);


        Vector3 c = Vector3::GetCrossProduct(a, b);


        TempExpectEqual(-3, c.X);
        TempExpectEqual(6, c.Y);
        TempExpectEqual(-3, c.Z);
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