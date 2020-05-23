#include "pch.h"

#include "Public/Game/IntVector2.h"

namespace Maths::Vectors
{
    using ArtemisEngine::IntVector2;

    TEST(IntVector2, ConstructorXY)
    {
        IntVector2 vector(1, 2);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
    }
    TEST(IntVector2, MemberAssignment)
    {
        IntVector2 vector;

        vector.X = 5;
        vector.Y = 10;

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(10, vector.Y);
    }
}