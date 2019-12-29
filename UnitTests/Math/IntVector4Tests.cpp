#include "pch.h"

#include "Engine/IntVector4.h"

namespace Math::Vectors
{
    using ArtemisEngine::IntVector4;

    TEST(IntVector4, ConstructorXY)
    {
        IntVector4 vector(5, 4);

        EXPECT_EQ(5, vector.x);
        EXPECT_EQ(4, vector.y);
    }
    TEST(IntVector4, ConstructorXYZ)
    {
        IntVector4 vector(-24, 5, 5);

        EXPECT_EQ(-24, vector.x);
        EXPECT_EQ(5, vector.y);
        EXPECT_EQ(5, vector.z);
    }
    TEST(IntVector4, ConstructorXYZW)
    {
        IntVector4 vector(0, 54, 1, 4);

        EXPECT_EQ(0, vector.x);
        EXPECT_EQ(54, vector.y);
        EXPECT_EQ(1, vector.z);
        EXPECT_EQ(4, vector.w);
    }
    TEST(IntVector4, MemberAssignment)
    {
        IntVector4 vector;

        vector.x = 1;
        vector.y = 2;
        vector.z = 3;
        vector.w = 4;

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
        EXPECT_EQ(3, vector.z);
        EXPECT_EQ(4, vector.w);
    }
}