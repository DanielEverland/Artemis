#include "pch.h"

#include "Engine/IntVector4.h"

namespace Math::Vectors
{
    using ArtemisEngine::IntVector4;

    TEST(IntVector4, ConstructorXY)
    {
        IntVector4 vector(5, 4);

        EXPECT_EQ(vector.x, 5);
        EXPECT_EQ(vector.y, 4);
    }
    TEST(IntVector4, ConstructorXYZ)
    {
        IntVector4 vector(-24, 5, 5);

        EXPECT_EQ(vector.x, -24);
        EXPECT_EQ(vector.y, 5);
        EXPECT_EQ(vector.z, 5);
    }
    TEST(IntVector4, ConstructorXYZW)
    {
        IntVector4 vector(0, 54, 1, 4);

        EXPECT_EQ(vector.x, 0);
        EXPECT_EQ(vector.y, 54);
        EXPECT_EQ(vector.z, 1);
        EXPECT_EQ(vector.w, 4);
    }
    TEST(IntVector4, MemberAssignment)
    {
        IntVector4 vector;

        vector.x = 1;
        vector.y = 2;
        vector.z = 3;
        vector.w = 4;

        EXPECT_EQ(vector.x, 1);
        EXPECT_EQ(vector.y, 2);
        EXPECT_EQ(vector.z, 3);
        EXPECT_EQ(vector.w, 4);
    }
}