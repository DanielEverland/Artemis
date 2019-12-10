#include "pch.h"

#include "Engine/Vector2.h"

TEST(Vector2, Addition)
{
    using ArtemisEngine::Vector2;

    Vector2 a(12, -54);
    Vector2 b(12.1, 54.34);

    Vector2 c = a + b;

    EXPECT_EQ(a[0] + b[0], c[0]);
    EXPECT_EQ(a[1] + b[1], c[1]);
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}