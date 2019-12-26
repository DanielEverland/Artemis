#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector2.h"

namespace Math::Vectors
{
    using ArtemisEngine::Vector2;

    TEST(Vector2, ConstructorXY)
    {
        Vector2 vector(10.0, 20.25);

        EXPECT_EQ(vector[0], 10);
        EXPECT_EQ(vector[1], 20.25);
    }
}