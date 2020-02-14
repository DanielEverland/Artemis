#include "gtest/gtest.h"
#include "pch.h"

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

        EXPECT_EQ(43.51, vector.X);
        EXPECT_EQ(2.0, vector.Y);
        EXPECT_EQ(12.3, vector.Z);
        EXPECT_EQ(153.0154, vector.W);
    }
    TEST(Vector4, ConstructorXY)
    {
        Vector4 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
    }
    TEST(Vector4, ConstructorXYZ)
    {
        Vector4 vector(10.0, 20.25, 30.20);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
        EXPECT_EQ(30.20, vector.Z);
    }
    TEST(Vector4, ConstructorXYZW)
    {
        Vector4 vector(10.0, 20.25, 30.20, 40.12);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
        EXPECT_EQ(30.20, vector.Z);
        EXPECT_EQ(40.12, vector.W);
    }
    TEST(Vector4, IntConstructorXY)
    {
        Vector4 vector(1, 2);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
    }
    TEST(Vector4, IntConstructorXYZ)
    {
        Vector4 vector(1, 2, 3);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(3, vector.Z);
    }
    TEST(Vector4, IntConstructorXYZW)
    {
        Vector4 vector(1, 2, 3, 4);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(3, vector.Z);
        EXPECT_EQ(4, vector.W);
    }
    TEST(Vector4, MemberAssignment)
    {
        Vector4 vector;

        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;
        vector.W = 100;

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(10, vector.Y);
        EXPECT_EQ(1, vector.Z);
        EXPECT_EQ(100, vector.W);
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
}