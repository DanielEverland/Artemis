#include "pch.h"

#include "Memory/FreeListAllocator.h"
#include "Exception/ArgumentException.h"
#include "Exception/OutOfMemoryException.h"
#include "Memory/AllocatorUtility.h"

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
	__int64 d : 64;
};

class FreeListAllocatorTest : public ::testing::Test
{
public:
	FreeListAllocatorTest()
	{
		AllocatorSize = 1 * 1024;
		AllocatorStart = malloc(AllocatorSize);
		Allocator = FreeListAllocator(AllocatorStart, AllocatorSize);
	}


protected:
	size_t AllocatorSize;
	void* AllocatorStart;
	FreeListAllocator Allocator;
};

constexpr size_t MemoryBlockSize = sizeof(size_t) * 2;

TEST_F(FreeListAllocatorTest, SingleAllocation)
{
	EXPECT_NE(Allocator.Allocate(sizeof(A), alignof(A)), nullptr);
}

TEST_F(FreeListAllocatorTest, DeallocateEmpty)
{
	EXPECT_NO_THROW(Allocator.Deallocate(AllocatorStart));
}

TEST_F(FreeListAllocatorTest, DeallocateExisting)
{
	void* obj = Allocator.Allocate(sizeof(A), alignof(A));
	EXPECT_NO_THROW(Allocator.Deallocate(obj));
}

TEST_F(FreeListAllocatorTest, DeallocateMiddle)
{
	void* first = Allocator.Allocate(sizeof(A), alignof(A));
	void* second = Allocator.Allocate(sizeof(A), alignof(A));
	void* third = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(first, nullptr);
	EXPECT_NE(second, nullptr);
	EXPECT_NE(third, nullptr);
	
	EXPECT_NO_THROW(Allocator.Deallocate(second));
}

TEST_F(FreeListAllocatorTest, DeallocateMerge)
{
	void* first = Allocator.Allocate(sizeof(A), alignof(A));
	void* second = Allocator.Allocate(sizeof(A), alignof(A));
	void* third = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(first, nullptr);
	EXPECT_NE(second, nullptr);
	EXPECT_NE(third, nullptr);

	EXPECT_NO_THROW(Allocator.Deallocate(first));
	EXPECT_NO_THROW(Allocator.Deallocate(third));
	EXPECT_NO_THROW(Allocator.Deallocate(second));
}

TEST_F(FreeListAllocatorTest, Reallocate)
{
	void* first = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(first, nullptr);
	EXPECT_NO_THROW(Allocator.Deallocate(first));

	void* second = Allocator.Allocate(sizeof(A), alignof(A));
	EXPECT_NE(second, nullptr);
	EXPECT_EQ(first, second);
}

TEST_F(FreeListAllocatorTest, DeallocatorBreakEarly)
{
	void* first = Allocator.Allocate(sizeof(A), alignof(A));
	void* second = Allocator.Allocate(sizeof(A), alignof(A));
	void* third = Allocator.Allocate(sizeof(A), alignof(A));
	void* fourth = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(first, nullptr);
	EXPECT_NE(second, nullptr);
	EXPECT_NE(third, nullptr);
	EXPECT_NE(fourth, nullptr);

	EXPECT_NO_THROW(Allocator.Deallocate(third));
	EXPECT_NO_THROW(Allocator.Deallocate(first));
	EXPECT_NO_THROW(Allocator.Deallocate(second));
	EXPECT_NO_THROW(Allocator.Deallocate(fourth));
}

TEST_F(FreeListAllocatorTest, ReallocateManyTimes)
{
	for (int i = 0; i < 1000; i++)
	{
		void* first = Allocator.Allocate(sizeof(A), alignof(A));

		EXPECT_NE(first, nullptr);
		EXPECT_NO_THROW(Allocator.Deallocate(first));

		void* second = Allocator.Allocate(sizeof(A), alignof(A));
		EXPECT_NE(second, nullptr);
		EXPECT_EQ(first, second);
		EXPECT_NO_THROW(Allocator.Deallocate(second));
	}
}

// Ensure that if a given block is too small to allocate a given type, we continue to a block after that.
TEST_F(FreeListAllocatorTest, DifferentSizedAllocations)
{
	void* firstA = Allocator.Allocate(sizeof(A), alignof(A));
	void* secondA = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(firstA, nullptr);
	EXPECT_NE(secondA, nullptr);

	EXPECT_NO_THROW(Allocator.Deallocate(firstA));
	
	void* firstB = Allocator.Allocate(sizeof(B), alignof(B));
	void* thirdA = Allocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(firstB, nullptr);
	EXPECT_NE(thirdA, nullptr);

	const auto firstAAddress = reinterpret_cast<uintptr_t>(firstA);
	const auto secondAAddress = reinterpret_cast<uintptr_t>(secondA);
	const auto thirdAAddress = reinterpret_cast<uintptr_t>(thirdA);
	const auto firstBAddress = reinterpret_cast<uintptr_t>(firstB);

	EXPECT_GT(thirdAAddress, firstAAddress);
	EXPECT_GT(secondAAddress, firstAAddress);
	EXPECT_LT(firstBAddress, secondAAddress);
}

TEST_F(FreeListAllocatorTest, MergeBlocksWhenMiddleIsAllocated)
{
	const size_t customSize = sizeof(B) + sizeof(A) * 2 + MemoryBlockSize * 2;
	auto customAllocator = FreeListAllocator(malloc(customSize), customSize);
		
	auto* a = customAllocator.Allocate(sizeof(B), alignof(B));
	auto* b = customAllocator.Allocate(sizeof(A), alignof(A));

	EXPECT_NE(a, nullptr);
	EXPECT_NE(b, nullptr);

	EXPECT_NO_THROW(customAllocator.Deallocate(a));
	auto* c = customAllocator.Allocate(sizeof(C), alignof(C));

	EXPECT_NE(c, nullptr);
}

TEST_F(FreeListAllocatorTest, MergeBlocksWithoutMiddle)
{
	// Size of B + size of a memory block
	const size_t smallTestSize = sizeof(B) + MemoryBlockSize;
	void* SmallAllocatorStart = malloc(smallTestSize);
	auto SmallAllocator = FreeListAllocator(SmallAllocatorStart, smallTestSize);

	// SmallAllocator has an exact size of B
	EXPECT_NO_THROW(SmallAllocator.Allocate(sizeof(B), alignof(B)));
}

#ifdef ENABLE_ASSERT
TEST_F(FreeListAllocatorTest, SmallSizeCreationAssert)
{
	EXPECT_THROW(FreeListAllocator(AllocatorStart, 8), ArgumentException);
}

TEST_F(FreeListAllocatorTest, InvalidStartPointerAssert)
{
	EXPECT_THROW(FreeListAllocator(nullptr, sizeof(A)), ArgumentException);
}

TEST_F(FreeListAllocatorTest, ValidAllocation)
{
	EXPECT_NO_THROW(FreeListAllocator(AllocatorStart, sizeof(A)));
}

TEST_F(FreeListAllocatorTest, ZeroSizeAssertion)
{
	EXPECT_THROW(Allocator.Allocate(0, alignof(A)), ArgumentException);
}

TEST_F(FreeListAllocatorTest, AlignmentZeroDisallowed)
{
	EXPECT_THROW(Allocator.Allocate(sizeof(A), 0), ArgumentException);
}

TEST_F(FreeListAllocatorTest, NonPowerOfTwoAlignment)
{
	EXPECT_THROW(Allocator.Allocate(sizeof(A), 3), ArgumentException);
}

TEST_F(FreeListAllocatorTest, OutOfMemoryException)
{
	// Size of B + size of a memory block
	const size_t smallTestSize = sizeof(B) + MemoryBlockSize;
	void* SmallAllocatorStart = malloc(smallTestSize);
	auto SmallAllocator = FreeListAllocator(SmallAllocatorStart, smallTestSize);
	
	// SmallAllocator has an exact size of B
	EXPECT_NO_THROW(SmallAllocator.Allocate(sizeof(B), alignof(B)));
	EXPECT_THROW(SmallAllocator.Allocate(sizeof(B), alignof(B)), OutOfMemoryException);
}

TEST_F(FreeListAllocatorTest, DeallocateNullAssert)
{
	EXPECT_THROW(Allocator.Deallocate(nullptr), ArgumentException);
}

TEST_F(FreeListAllocatorTest, DeallocateOutOfBoundsPointer)
{
	EXPECT_THROW(Allocator.Deallocate(AllocatorUtility::SubtractPointer<void>(AllocatorStart, 1)), ArgumentException);
	EXPECT_THROW(Allocator.Deallocate(AllocatorUtility::AddPointer<void>(AllocatorStart, AllocatorSize + 1)), ArgumentException);
}
#endif