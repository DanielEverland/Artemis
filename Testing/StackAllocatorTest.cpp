#include "pch.h"


#include "Exception/ArgumentException.h"
#include "Exception/OutOfMemoryException.h"
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

TEST_F(StackAllocatorTest, ReallocationSamePointer)
{
	const void* firstPtr = Allocator.Allocate(sizeof(A), alignof(A));
	Allocator.Deallocate(firstPtr);
	const void* secondPtr = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_EQ(firstPtr, secondPtr);
}

#ifdef _DEBUG
TEST_F(StackAllocatorTest, OutOfMemory)
{
	StackAllocator smallAllocator(malloc(sizeof(A)), sizeof(A));

	// This won't work, since it also needs size for the header
	EXPECT_THROW(smallAllocator.Allocate(sizeof(A), alignof(A)), OutOfMemoryException);
}

TEST_F(StackAllocatorTest, DeallocateNonTopException)
{
	const void* firstPtr = Allocator.Allocate(sizeof(A), alignof(A));
	const void* secondPtr = Allocator.Allocate(sizeof(A), alignof(A));
	const void* thirdPtr = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NO_THROW(Allocator.Deallocate(thirdPtr));
	EXPECT_THROW(Allocator.Deallocate(firstPtr), ArgumentException);
	EXPECT_NO_THROW(Allocator.Deallocate(secondPtr));
}
#endif

#ifdef ENABLE_ASSERT
TEST_F(StackAllocatorTest, ZeroSizeCreationAssert)
{
	EXPECT_THROW(StackAllocator(AllocatorStart, 0), ArgumentException);
}

TEST_F(StackAllocatorTest, OnlyHeaderSizeCreationAssert)
{
	EXPECT_THROW(StackAllocator(AllocatorStart, 1), ArgumentException);
}

TEST_F(StackAllocatorTest, InvalidStartPointerAssert)
{
	EXPECT_THROW(StackAllocator(nullptr, sizeof(A)), ArgumentException);
}

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