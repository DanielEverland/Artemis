#include "pch.h"

#include "Memory/AllocatorUtility.h"

using namespace ArtemisEngine;

struct A
{
	char c : 6;
	__int64 d : 64;
	int b : 32;
	char a : 8;
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