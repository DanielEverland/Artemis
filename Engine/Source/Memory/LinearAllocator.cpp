#include "LinearAllocator.h"

#include <Exception/ArgumentException.h>

#include "AllocatorUtility.h"

using namespace ArtemisEngine;

LinearAllocator::LinearAllocator() : BaseAllocator(), CurrentPosition(nullptr)
{
}

LinearAllocator::LinearAllocator(void* start, size_t size) : BaseAllocator(start, size)
{
	CurrentPosition = StartPosition;
}

LinearAllocator::~LinearAllocator() = default;

#pragma warning(disable:4100)
void* LinearAllocator::Allocate(const size_t size, const uint8 alignment)
{
	Assert(size > 0, ArgumentException("Cannot allocate memory of non-positive size"))
	Assert(alignment > 0, ArgumentException("Cannot allocate memory with an alignment of 0"))

	const uintptr_t currentAddress = GetAlignedPosition(alignment);
	auto* const finalPointer = reinterpret_cast<void*>(currentAddress);
	ForwardPosition(size);
	
	return finalPointer;
}

uintptr_t LinearAllocator::GetAlignedPosition(const uint8 alignment) const
{
	const uint8 adjustment = AllocatorUtility::GetMemoryAddressAdjustment(CurrentPosition, alignment);
	const auto currentPositionAddress = reinterpret_cast<uintptr_t>(CurrentPosition);
	return currentPositionAddress + adjustment;
}

void LinearAllocator::ForwardPosition(const size_t size)
{
	const auto currentPositionAddress = reinterpret_cast<uintptr_t>(CurrentPosition);
	const uintptr_t newAddress = currentPositionAddress + size;
	CurrentPosition = reinterpret_cast<void*>(newAddress);
}
