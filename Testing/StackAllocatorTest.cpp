#include "pch.h"


#include "Exception/ArgumentException.h"
#include "Memory/StackAllocator.h"

using namespace ArtemisEngine;

struct A
{
	char c : 6;
	__int64 d : 64;
	int b : 32;
	char a : 8;
};

struct B
{
	char c;
};

struct C
{
	__int64 d;
	__int32 b;
	char a;
	char c;
	char unused[2];
};

class StackAllocatorTest : public ::testing::Test
{
public:
	StackAllocatorTest()
	{
		const size_t testSize = 1 * 1024;
		AllocatorStart = malloc(testSize);
		Allocator = StackAllocator(AllocatorStart, testSize);
	}

protected:
	void* AllocatorStart;
	StackAllocator Allocator;
};

#ifdef ENABLE_ASSERT
TEST_F(StackAllocatorTest, ZeroSizeAssertion)
{
	EXPECT_THROW(Allocator.Allocate(0, alignof(A)), ArgumentException);
}

TEST_F(StackAllocatorTest, AlignmentZeroDisallowed)
{
	EXPECT_THROW(Allocator.Allocate(sizeof(A), 0), ArgumentException);
}

TEST_F(StackAllocatorTest, NonPowerOfTwoAlignment)
{
	EXPECT_THROW(Allocator.Allocate(sizeof(A), 3), ArgumentException);
}
#endif