#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector3.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector3;

    TEST(Vector3, ConstructorXY)
    {
        Vector3 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.x);
        EXPECT_EQ(20.25, vector.y);
    }
    TEST(Vector3, ConstructorXYZ)
    {
        Vector3 vector(10.0, 20.25, 30.20);

        EXPECT_EQ(10.0, vector.x);
        EXPECT_EQ(20.25, vector.y);
        EXPECT_EQ(30.20, vector.z);
    }
    TEST(Vector3, IntConstructorXY)
    {
        Vector3 vector(1, 2);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
    }
    TEST(Vector3, IntConstructorXYZ)
    {
        Vector3 vector(1, 2, 3);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
        EXPECT_EQ(3, vector.z);
    }
    TEST(Vector3, MemberAssignment)
    {
        Vector3 vector;

        vector.x = 5;
        vector.y = 10;
        vector.z = 1;

        EXPECT_EQ(5, vector.x);
        EXPECT_EQ(10, vector.y);
        EXPECT_EQ(1, vector.z);
    }
    TEST(Vector3, CrossProduct)
    {
        Vector3 a(1, 2, 3);
        Vector3 b(4, 5, 6);

        Vector3 c = Vector3::GetCrossProduct(a, b);

        EXPECT_EQ(-3, c.x);
        EXPECT_EQ(6, c.y);
        EXPECT_EQ(-3, c.z);
    }
}