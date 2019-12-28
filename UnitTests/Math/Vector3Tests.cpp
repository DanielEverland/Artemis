#include "gtest/gtest.h"
#include "pch.h"
//
//#include "Engine/Vector3.h"
//
//namespace Math::Vectors
//{
//    using ArtemisEngine::Vector3;
//
//    TEST(Vector3, ConstructorXY)
//    {
//        Vector3 vector(10.0, 20.25);
//
//        EXPECT_EQ(vector.x, 10.0);
//        EXPECT_EQ(vector.y, 20.25);
//    }
//    TEST(Vector3, ConstructorXYZ)
//    {
//        Vector3 vector(10.0, 20.25, 30.20);
//
//        EXPECT_EQ(vector.x, 10.0);
//        EXPECT_EQ(vector.y, 20.25);
//        EXPECT_EQ(vector.z, 30.20);
//    }
//    TEST(Vector3, IntConstructorXY)
//    {
//        Vector3 vector(1, 2);
//
//        EXPECT_EQ(vector.x, 1);
//        EXPECT_EQ(vector.y, 2);
//    }
//    TEST(Vector3, IntConstructorXYZ)
//    {
//        Vector3 vector(1, 2, 3);
//
//        EXPECT_EQ(vector.x, 1);
//        EXPECT_EQ(vector.y, 2);
//        EXPECT_EQ(vector.z, 3);
//    }
//    TEST(Vector3, MemberAssignment)
//    {
//        Vector3 vector;
//
//        vector.x = 5;
//        vector.y = 10;
//        vector.z = 1;
//
//        EXPECT_EQ(vector.x, 5);
//        EXPECT_EQ(vector.y, 10);
//        EXPECT_EQ(vector.z, 1);
//    }
//    TEST(Vector3, CrossProduct)
//    {
//        Vector3 a(1, 2, 3);
//        Vector3 b(4, 5, 6);
//
//        Vector3 c = Vector3::GetCrossProduct(a, b);
//
//        EXPECT_EQ(c.x, -3);
//        EXPECT_EQ(c.y, 6);
//        EXPECT_EQ(c.z, -3);
//    }
//}