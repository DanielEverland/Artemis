#include "pch.h"

#include <Memory/LinearAllocator.h>
#include <Memory/AllocatorUtility.h>

#include "Exception/ArgumentException.h"

using namespace ArtemisEngine;

class LinearAllocatorTest : public ::testing::Test
{
public:
	LinearAllocatorTest()
	{
		const size_t testSize = 1 * 1024;
		void* testMemory = malloc(testSize);
		Allocator = LinearAllocator(testMemory, testSize);
	}
	
protected:
	LinearAllocator Allocator;
};

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

TEST_F(LinearAllocatorTest, SimpleAllocation)
{
	void* allocatedMemory = Allocator.Allocate(10, 1);

	EXPECT_TRUE(allocatedMemory != nullptr);
}

TEST_F(LinearAllocatorTest, ZeroSizeAssertion)
{
	EXPECT_THROW(Allocator.Allocate(0, alignof(A)), ArgumentException);
}

TEST_F(LinearAllocatorTest, AlignmentZeroDisallowed)
{
	EXPECT_THROW(Allocator.Allocate(sizeof(A), 0), ArgumentException);
}

TEST_F(LinearAllocatorTest, DoubleAllocationDifference)
{
	void* firstMemory = Allocator.Allocate(sizeof(A), alignof(A));
	void* secondMemory = Allocator.Allocate(sizeof(A), alignof(A));
		
	EXPECT_TRUE(firstMemory != nullptr);
	EXPECT_TRUE(secondMemory != nullptr);
	EXPECT_NE(firstMemory, secondMemory);
}

TEST_F(LinearAllocatorTest, DoubleAllocationAlignment)
{
	const size_t requestedSizeA = sizeof(A);
	const size_t alignmentA = alignof(A);

	const size_t requestedSizeB = sizeof(C);
	const size_t alignmentB = alignof(C);
	
	const auto firstAddress = reinterpret_cast<uintptr_t>(Allocator.Allocate(requestedSizeA, alignmentA));
	const auto secondAddress = reinterpret_cast<uintptr_t>(Allocator.Allocate(requestedSizeB, alignmentB));
	const uintptr_t delta = secondAddress - firstAddress;
	
	EXPECT_EQ(delta, requestedSizeA);
}

TEST_F(LinearAllocatorTest, OffsetAllocationTest)
{
	const size_t requestedSizeA = sizeof(A);
	const size_t alignmentA = alignof(A);

	const size_t requestedSizeB = sizeof(B);
	const size_t alignmentB = alignof(B);
	
	const auto firstAddress = reinterpret_cast<uintptr_t>(Allocator.Allocate(requestedSizeB, alignmentB));
	const auto secondAddress = reinterpret_cast<uintptr_t>(Allocator.Allocate(requestedSizeA, alignmentA));
	const uintptr_t delta = secondAddress - firstAddress;

	// We expect the delta to be 8, even though the size of B is only 1.
	// This is because it's been shifted 7 bytes to become aligned.
	EXPECT_EQ(requestedSizeB, 1);
	EXPECT_EQ(delta, 8);
}

