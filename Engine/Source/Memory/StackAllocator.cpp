#include "StackAllocator.h"

#include <Core/Macros.h>
#include <Core/Math.h>
#include <Exception/ArgumentException.h>

#include "AllocatorUtility.h"
#include "Exception/OutOfMemoryException.h"

using namespace ArtemisEngine;

StackAllocator::StackAllocator() : BaseAllocator()
{
}

StackAllocator::StackAllocator(void* start, size_t size) : BaseAllocator(start, size)
{
	Assert(size > sizeof(AllocationHeader), ArgumentException("StackAllocator size must be larger than size of header!"));
	Current = StartPosition;

#if _DEBUG
	Previous = nullptr;
#endif
}

StackAllocator::~StackAllocator() = default;

void* StackAllocator::Allocate(size_t size, uint8 alignment)
{
	Assert(size > 0, ArgumentException("Cannot allocate memory of non-positive size"))
	Assert(alignment > 0, ArgumentException("Cannot allocate memory with an alignment of 0"))
	Assert(Math::IsPowerOfTwo(alignment), ArgumentException("Alignment must be power of two!"))

	const uint8 adjustment = AllocatorUtility::GetMemoryAddressAdjustmentWithHeader(Current, alignment, GetHeaderSize());
	const auto currentPositionAddress = reinterpret_cast<uintptr_t>(Current);
	const uintptr_t alignedAddress = currentPositionAddress + adjustment;
	auto* const finalPointer = reinterpret_cast<void*>(alignedAddress);

	Assert(!IsOutOfBounds(finalPointer, size), OutOfMemoryException("StackAllocator failed allocation due to running out of memory"))

	CreateAllocationHeader(alignedAddress, adjustment);
	ForwardPosition(alignedAddress, size);

#if _DEBUG
	Previous = finalPointer;
#endif

	return finalPointer; 
}

void StackAllocator::Deallocate(const void* const blockToDeallocate)
{
	Assert(blockToDeallocate == Previous, ArgumentException("Deallocated block must be the top of the stack"))

	const auto blockAddress = reinterpret_cast<uintptr_t>(blockToDeallocate);
	auto* const header = reinterpret_cast<AllocationHeader*>(blockAddress - sizeof(AllocationHeader));

	Current = reinterpret_cast<void*>(blockAddress - header->Adjustment);

#if _DEBUG
	Previous = header->Previous;
#endif
}

void StackAllocator::CreateAllocationHeader(const uintptr_t alignedAddress, const uint8 adjustment) const
{
	const uintptr_t allocationHeaderAddress = alignedAddress - GetHeaderSize();
	auto* const header = reinterpret_cast<AllocationHeader*>(allocationHeaderAddress);

	header->Adjustment = adjustment;

#if _DEBUG
	header->Previous = Previous;
#endif
}

void StackAllocator::ForwardPosition(uintptr_t alignedAddress, size_t size)
{
	Current = reinterpret_cast<void*>(alignedAddress + size);
}

uint8 StackAllocator::GetHeaderSize()
{
	return sizeof(AllocationHeader);
}
