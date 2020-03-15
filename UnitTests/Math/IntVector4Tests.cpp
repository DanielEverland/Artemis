#include "pch.h"

#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Include/Game/IntVector4.h"
#include "Include/Game/IntVector3.h"
#include "Include/Game/IntVector2.h"
#include "Include/Game/Vector2.h"
#include "Include/Game/Vector3.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

    TEST(IntVector4, ConstructorXY)
    {
        IntVector4 vector(5, 4);

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(4, vector.Y);
    }
    TEST(IntVector4, ConstructorXYZ)
    {
        IntVector4 vector(-24, 5, 5);

        EXPECT_EQ(-24, vector.X);
        EXPECT_EQ(5, vector.Y);
        EXPECT_EQ(5, vector.Z);
    }
    TEST(IntVector4, ConstructorXYZW)
    {
        IntVector4 vector(0, 54, 1, 4);

        EXPECT_EQ(0, vector.X);
        EXPECT_EQ(54, vector.Y);
        EXPECT_EQ(1, vector.Z);
        EXPECT_EQ(4, vector.W);
    }
    TEST(IntVector4, MemberAssignment)
    {
        IntVector4 vector;

        vector.X = 1;
        vector.Y = 2;
        vector.Z = 3;
        vector.W = 4;

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(3, vector.Z);
        EXPECT_EQ(4, vector.W);
    }
    TEST(IntVector4, UpgradeVector2)
    {
        IntVector4 expectedResult(154, 12, 0, 0);
        Vector2 vector(154.14, 12.5);


        IntVector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(IntVector4, UpgradeIntVector2)
    {
        IntVector4 expectedResult(154, 12, 0, 0);
        IntVector2 vector(154, 12);


        IntVector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(IntVector4, UpgradeVector3)
    {
        IntVector4 expectedResult(154, 12, 56, 0);
        Vector3 vector(154.14, 12.4, 56.99);


        IntVector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(IntVector4, UpgradeIntVector3)
    {
        IntVector4 expectedResult(154, 12, 54, 0);
        IntVector3 vector(154, 12, 54);


        IntVector4 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
}