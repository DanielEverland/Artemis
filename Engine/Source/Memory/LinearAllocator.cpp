﻿#include "LinearAllocator.h"

#include <Core/Math.h>
#include <Exception/ArgumentException.h>

#include "AllocatorUtility.h"
#include "Exception/OutOfMemoryException.h"

using namespace ArtemisEngine;

LinearAllocator::LinearAllocator() : BaseAllocator(), CurrentPosition(nullptr)
{
}

LinearAllocator::LinearAllocator(void* start, size_t size) : BaseAllocator(start, size)
{
	CurrentPosition = StartPosition;
}

LinearAllocator::~LinearAllocator() = default;

void* LinearAllocator::Allocate(const size_t size, const uint8 alignment)
{
	Assert(size > 0, ArgumentException("Cannot allocate memory of non-positive size"))
	Assert(alignment > 0, ArgumentException("Cannot allocate memory with an alignment of 0"))
	Assert(Math::IsPowerOfTwo(alignment), ArgumentException("Alignment must be power of two!"))

	const uintptr_t currentAddress = GetAlignedPosition(alignment);
	auto* const finalPointer = reinterpret_cast<void*>(currentAddress);

	Assert(!IsOutOfBounds(finalPointer, size), OutOfMemoryException("LinearAllocator failed allocation due to running out of memory"))
	
	ForwardPosition(size);
	
	return finalPointer;
}

void LinearAllocator::Clear()
{
	CurrentPosition = StartPosition;
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
