#include "pch.h"

#include "Engine/IntVector4.h"

namespace Maths::Vectors
{
    using ArtemisEngine::IntVector4;

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
}