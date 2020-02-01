#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector4.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector4;

    TEST(Vector4, ConstructorXY)
    {
        Vector4 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.x);
        EXPECT_EQ(20.25, vector.y);
    }
    TEST(Vector4, ConstructorXYZ)
    {
        Vector4 vector(10.0, 20.25, 30.20);

        EXPECT_EQ(10.0, vector.x);
        EXPECT_EQ(20.25, vector.y);
        EXPECT_EQ(30.20, vector.z);
    }
    TEST(Vector4, ConstructorXYZW)
    {
        Vector4 vector(10.0, 20.25, 30.20, 40.12);

        EXPECT_EQ(10.0, vector.x);
        EXPECT_EQ(20.25, vector.y);
        EXPECT_EQ(30.20, vector.z);
        EXPECT_EQ(40.12, vector.w);
    }
    TEST(Vector4, IntConstructorXY)
    {
        Vector4 vector(1, 2);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
    }
    TEST(Vector4, IntConstructorXYZ)
    {
        Vector4 vector(1, 2, 3);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
        EXPECT_EQ(3, vector.z);
    }
    TEST(Vector4, IntConstructorXYZW)
    {
        Vector4 vector(1, 2, 3, 4);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
        EXPECT_EQ(3, vector.z);
        EXPECT_EQ(4, vector.w);
    }
    TEST(Vector4, MemberAssignment)
    {
        Vector4 vector;

        vector.x = 5;
        vector.y = 10;
        vector.z = 1;
        vector.w = 100;

        EXPECT_EQ(5, vector.x);
        EXPECT_EQ(10, vector.y);
        EXPECT_EQ(1, vector.z);
        EXPECT_EQ(100, vector.w);
    }
}