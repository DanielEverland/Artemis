#include "pch.h"

#include "Engine/IntVector3.h"

namespace Maths::Vectors
{
    using ArtemisEngine::IntVector3;

    TEST(IntVector3, ConstructorXY)
    {
        IntVector3 vector(1, 3);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(3, vector.y);
    }
    TEST(IntVector3, ConstructorXYZ)
    {
        IntVector3 vector(19, 2, 5);

        EXPECT_EQ(19, vector.x);
        EXPECT_EQ(2, vector.y);
        EXPECT_EQ(5, vector.z);
    }
    TEST(IntVector3, MemberAssignment)
    {
        IntVector3 vector;

        vector.x = 5;
        vector.y = 10;
        vector.z = 2;

        EXPECT_EQ(5, vector.x);
        EXPECT_EQ(10, vector.y);
        EXPECT_EQ(2, vector.z);
    }
    TEST(IntVector3, CrossProduct)
    {
        IntVector3 a(5, 4, 3);
        IntVector3 b(15, 20, 25);

        IntVector3 c = IntVector3::GetCrossProduct(a, b);

        EXPECT_EQ(40, c.x);
        EXPECT_EQ(-80, c.y);
        EXPECT_EQ(40, c.z);
    }
}