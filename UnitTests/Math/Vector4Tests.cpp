#include "gtest/gtest.h"
#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Public/Game/Vector4.h"
#include "Public/Game/Vector2.h"
#include "Public/Game/Vector3.h"
#include "Public/Game/IntVector2.h"
#include "Public/Game/IntVector3.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

    TEST(Vector4, InitializerListConstructor)
    {
        Vector4 vector({ 43.51, 2.0, 12.3, 153.0154, 12453.123 });


        ExpectNear(43.51, vector.X);
        ExpectNear(2.0, vector.Y);
        ExpectNear(12.3, vector.Z);
        ExpectNear(153.0154, vector.W);
    }
    TEST(Vector4, ConstructorXY)
    {
        Vector4 vector(10.0, 20.25);


        ExpectNear(10.0, vector.X);
        ExpectNear(20.25, vector.Y);
    }
    TEST(Vector4, ConstructorXYZ)
    {
        Vector4 vector(10.0, 20.25, 30.20);


        ExpectNear(10.0, vector.X);
        ExpectNear(20.25, vector.Y);
        ExpectNear(30.20, vector.Z);
    }
    TEST(Vector4, ConstructorXYZW)
    {
        Vector4 vector(10.0, 20.25, 30.20, 40.12);


        ExpectNear(10.0, vector.X);
        ExpectNear(20.25, vector.Y);
        ExpectNear(30.20, vector.Z);
        ExpectNear(40.12, vector.W);
    }
    TEST(Vector4, IntConstructorXY)
    {
        Vector4 vector(1, 2);


        ExpectEqual(1, vector.X);
        ExpectEqual(2, vector.Y);
    }
    TEST(Vector4, IntConstructorXYZ)
    {
        Vector4 vector(1, 2, 3);


        ExpectEqual(1, vector.X);
        ExpectEqual(2, vector.Y);
        ExpectEqual(3, vector.Z);
    }
    TEST(Vector4, IntConstructorXYZW)
    {
        Vector4 vector(1, 2, 3, 4);


        ExpectEqual(1, vector.X);
        ExpectEqual(2, vector.Y);
        ExpectEqual(3, vector.Z);
        ExpectEqual(4, vector.W);
    }
    TEST(Vector4, MemberAssignment)
    {
        Vector4 vector;


        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;
        vector.W = 100;


        ExpectEqual(5, vector.X);
        ExpectEqual(10, vector.Y);
        ExpectEqual(1, vector.Z);
        ExpectEqual(100, vector.W);
    }
    TEST(Vector4, UpgradeVector2)
    {
        Vector4 expectedResult(154.14, 12.4, 0, 0);
        Vector2 vector(154.14, 12.4);


        Vector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(Vector4, UpgradeIntVector2)
    {
        Vector4 expectedResult(154, 12, 0, 0);
        IntVector2 vector(154, 12);


        Vector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(Vector4, UpgradeVector3)
    {
        Vector4 expectedResult(154.14, 12.4, 56.99, 0);
        Vector3 vector(154.14, 12.4, 56.99);


        Vector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(Vector4, UpgradeIntVector3)
    {
        Vector4 expectedResult(154, 12, 54, 0);
        IntVector3 vector(154, 12, 54);


        Vector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
}