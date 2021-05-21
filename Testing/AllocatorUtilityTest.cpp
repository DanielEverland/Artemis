#include "pch.h"

#include <Exception/ArgumentException.h>
#include <Memory/AllocatorUtility.h>

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

class AllocatorUtilityTest : public ::testing::Test
{
public:
	AllocatorUtilityTest()
	{
		TestPtr = malloc(sizeof(A));
	}

protected:
	void* TestPtr;
};

TEST_F(AllocatorUtilityTest, PerfectAlignment)
{
	uint8 returnedAdjustment = AllocatorUtility::GetMemoryAddressAdjustment(TestPtr, alignof(A));
	
	EXPECT_EQ(returnedAdjustment, 0);
}

TEST_F(AllocatorUtilityTest, MisalignedPointerNextAddress)
{
	const uint8 offset = 1;
	auto currentAddress = reinterpret_cast<uintptr_t>(TestPtr);
	currentAddress += offset;
	TestPtr = reinterpret_cast<void*>(currentAddress);

	uint8 expectedAdjustment = alignof(A) - offset;
	
	const uint8 returnedAdjustment = AllocatorUtility::GetMemoryAddressAdjustment(TestPtr, alignof(A));

	EXPECT_EQ(expectedAdjustment, returnedAdjustment);
}

TEST_F(AllocatorUtilityTest, NaturalAdjustment)
{
	// This test wil dynamically allocate objects that need to be adjusted
	// 8 BYTES  8 BYTES
	// |        |        |        |
	//
	// This will allocate the following:
	//     A
	// |////////|
	//
	// Then we allocate B of 1 byte:
	//     A         B
	// |////////|/       |
	//
	// At this point if we allocate A again it needs an adjustment of 7 bytes
	//     A         B       A
	// |////////|/       |////////|
	//
	// Therefore the expected adjustment is 7.
	const uint8 expectedAdjustment = 7;
	
	const auto currentAddress = reinterpret_cast<uintptr_t>(TestPtr);
	const uint8 adjustmentA = AllocatorUtility::GetMemoryAddressAdjustment(TestPtr, alignof(B));
	const uintptr_t bAddress = currentAddress + adjustmentA + sizeof(B);
	void* bPtr = reinterpret_cast<void*>(bAddress);
	const uint8 actualAdjustment = AllocatorUtility::GetMemoryAddressAdjustment(bPtr, alignof(A));

	EXPECT_EQ(expectedAdjustment, actualAdjustment);
}

TEST_F(AllocatorUtilityTest, NonPowerOfTwoAlignment)
{
	EXPECT_THROW(AllocatorUtility::GetMemoryAddressAdjustment(TestPtr, 3), ArgumentException);
}