#include "pch.h"

#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Public/Game/IntVector3.h"
#include "Public/Game/Vector2.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

    TEST(IntVector3, ConstructorXY)
    {
        IntVector3 vector(1, 3);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(3, vector.Y);
    }
    TEST(IntVector3, ConstructorXYZ)
    {
        IntVector3 vector(19, 2, 5);

        EXPECT_EQ(19, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(5, vector.Z);
    }
    TEST(IntVector3, MemberAssignment)
    {
        IntVector3 vector;

        vector.X = 5;
        vector.Y = 10;
        vector.Z = 2;

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(10, vector.Y);
        EXPECT_EQ(2, vector.Z);
    }
    TEST(IntVector3, CrossProduct)
    {
        IntVector3 a(5, 4, 3);
        IntVector3 b(15, 20, 25);

        IntVector3 c = IntVector3::GetCrossProduct(a, b);

        EXPECT_EQ(40, c.X);
        EXPECT_EQ(-80, c.Y);
        EXPECT_EQ(40, c.Z);
    }
    TEST(IntVector3, UpgradeVector2)
    {
        IntVector3 expectedResult(154, 12, 0);
        Vector2 vector(154.14, 12.4);


        IntVector3 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
    TEST(IntVector3, UpgradeIntVector2)
    {
        IntVector3 expectedResult(154, 12, 0);
        Vector2 vector(154, 12);


        IntVector3 actualResult(vector);


        VectorExpectNear(expectedResult, actualResult);
    }
}