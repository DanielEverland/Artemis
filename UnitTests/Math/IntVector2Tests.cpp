#include "pch.h"

#include "Engine/IntVector2.h"

namespace Math::Vectors
{
    using ArtemisEngine::IntVector2;

    TEST(IntVector2, ConstructorXY)
    {
        IntVector2 vector(1, 2);

        EXPECT_EQ(vector.x, 1);
        EXPECT_EQ(vector.y, 2);
    }
    TEST(IntVector2, MemberAssignment)
    {
        IntVector2 vector;

        vector.x = 5;
        vector.y = 10;

        EXPECT_EQ(vector.x, 5);
        EXPECT_EQ(vector.y, 10);
    }
}