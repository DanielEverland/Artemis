#include "gtest/gtest.h"
#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Engine/Vector4.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/IntVector2.h"
#include "Engine/IntVector3.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

    TEST(Vector4, InitializerListConstructor)
    {
        Vector4 vector({ 43.51, 2.0, 12.3, 153.0154, 12453.123 });


        TempExpectNear(43.51, vector.X);
        TempExpectNear(2.0, vector.Y);
        TempExpectNear(12.3, vector.Z);
        TempExpectNear(153.0154, vector.W);
    }
    TEST(Vector4, ConstructorXY)
    {
        Vector4 vector(10.0, 20.25);


        TempExpectNear(10.0, vector.X);
        TempExpectNear(20.25, vector.Y);
    }
    TEST(Vector4, ConstructorXYZ)
    {
        Vector4 vector(10.0, 20.25, 30.20);


        TempExpectNear(10.0, vector.X);
        TempExpectNear(20.25, vector.Y);
        TempExpectNear(30.20, vector.Z);
    }
    TEST(Vector4, ConstructorXYZW)
    {
        Vector4 vector(10.0, 20.25, 30.20, 40.12);


        TempExpectNear(10.0, vector.X);
        TempExpectNear(20.25, vector.Y);
        TempExpectNear(30.20, vector.Z);
        TempExpectNear(40.12, vector.W);
    }
    TEST(Vector4, IntConstructorXY)
    {
        Vector4 vector(1, 2);


        TempExpectEqual(1, vector.X);
        TempExpectEqual(2, vector.Y);
    }
    TEST(Vector4, IntConstructorXYZ)
    {
        Vector4 vector(1, 2, 3);


        TempExpectEqual(1, vector.X);
        TempExpectEqual(2, vector.Y);
        TempExpectEqual(3, vector.Z);
    }
    TEST(Vector4, IntConstructorXYZW)
    {
        Vector4 vector(1, 2, 3, 4);


        TempExpectEqual(1, vector.X);
        TempExpectEqual(2, vector.Y);
        TempExpectEqual(3, vector.Z);
        TempExpectEqual(4, vector.W);
    }
    TEST(Vector4, MemberAssignment)
    {
        Vector4 vector;


        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;
        vector.W = 100;


        TempExpectEqual(5, vector.X);
        TempExpectEqual(10, vector.Y);
        TempExpectEqual(1, vector.Z);
        TempExpectEqual(100, vector.W);
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