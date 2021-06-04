#include "BaseAllocator.h"
#include "Exception/ArgumentException.h"

using namespace ArtemisEngine;

BaseAllocator::BaseAllocator()
{
}

BaseAllocator::BaseAllocator(void* start, size_t size) : StartPosition(start), Size(size)
{
	Assert(size > 0, ArgumentException("Allocator size must be larger than 0!"));
	Assert(start != nullptr, ArgumentException("Start pointer is null"));
}

bool BaseAllocator::IsOutOfBounds(const void* const pointer, size_t size) const
{
	const auto queriedAddress = reinterpret_cast<uintptr_t>(pointer);
	const auto startAddress = reinterpret_cast<uintptr_t>(StartPosition);
	const uintptr_t endAddress = startAddress + Size;

	return (queriedAddress + size) > endAddress || queriedAddress < startAddress;
}
