#include "LinearAllocator.h"

#include <Exception/ArgumentException.h>

#include "AllocatorUtility.h"

using namespace ArtemisEngine;

LinearAllocator::LinearAllocator() : BaseAllocator()
{
}

LinearAllocator::LinearAllocator(void* start, size_t size) : BaseAllocator(start, size)
{
	CurrentPosition = StartPosition;
}

LinearAllocator::~LinearAllocator()
{
}

#pragma warning(disable:4100)
void* LinearAllocator::Allocate(const size_t size, const uint8 alignment)
{
	if(size == 0)
	{
		throw ArgumentException("Cannot allocate memory of non-positive size");
	}

	if(alignment == 0)
	{
		throw ArgumentException("Cannot allocate memory with an alignment of 0");
	}

	const uintptr_t currentAddress = GetAlignedPosition(alignment);
	CurrentPosition = reinterpret_cast<void*>(currentAddress + size);
	
	return CurrentPosition;
}

uintptr_t LinearAllocator::GetAlignedPosition(const uint8 alignment) const
{
	const uint8 adjustment = AllocatorUtility::GetMemoryAddressAdjustment(CurrentPosition, alignment);
	const auto currentPositionAddress = reinterpret_cast<uintptr_t>(CurrentPosition);
	return currentPositionAddress + adjustment;
}

void LinearAllocator::ForwardPosition(uintptr_t currentAddress, size_t size, uint8 alignment)
{
	const uintptr_t newPos = currentAddress + size + alignment;
	CurrentPosition = reinterpret_cast<void*>(newPos);
}
