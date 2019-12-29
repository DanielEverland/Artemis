#include "pch.h"

#include "Engine/IntVector3.h"

namespace Math::Vectors
{
    using ArtemisEngine::IntVector3;

    TEST(IntVector3, ConstructorXY)
    {
        IntVector3 vector(1, 3);

        EXPECT_EQ(vector.x, 1);
        EXPECT_EQ(vector.y, 3);
    }
    TEST(IntVector3, ConstructorXYZ)
    {
        IntVector3 vector(19, 2, 5);

        EXPECT_EQ(vector.x, 19);
        EXPECT_EQ(vector.y, 2);
        EXPECT_EQ(vector.z, 5);
    }
    TEST(IntVector3, MemberAssignment)
    {
        IntVector3 vector;

        vector.x = 5;
        vector.y = 10;
        vector.z = 2;

        EXPECT_EQ(vector.x, 5);
        EXPECT_EQ(vector.y, 10);
        EXPECT_EQ(vector.z, 2);
    }
    TEST(IntVector3, CrossProduct)
    {
        IntVector3 a(5, 4, 3);
        IntVector3 b(15, 20, 25);

        IntVector3 c = IntVector3::GetCrossProduct(a, b);

        EXPECT_EQ(c.x, 40);
        EXPECT_EQ(c.y, -80);
        EXPECT_EQ(c.z, 40);
    }
}