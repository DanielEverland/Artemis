#include "pch.h"

#include "Engine/IntVector2.h"

namespace Maths::Vectors
{
    using ArtemisEngine::IntVector2;

    TEST(IntVector2, ConstructorXY)
    {
        IntVector2 vector(1, 2);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
    }
    TEST(IntVector2, MemberAssignment)
    {
        IntVector2 vector;

        vector.x = 5;
        vector.y = 10;

        EXPECT_EQ(5, vector.x);
        EXPECT_EQ(10, vector.y);
    }
}