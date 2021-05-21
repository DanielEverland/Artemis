#include "BaseAllocator.h"

using namespace ArtemisEngine;

BaseAllocator::BaseAllocator()
{
}

BaseAllocator::BaseAllocator(void* start, size_t size) : StartPosition(start), Size(size)
{
}

bool BaseAllocator::IsOutOfBounds(void* pointer, size_t size) const
{
	const auto queriedAddress = reinterpret_cast<uintptr_t>(pointer);
	const auto startAddress = reinterpret_cast<uintptr_t>(StartPosition);
	const uintptr_t endAddress = startAddress + Size;

	return (queriedAddress + size) > endAddress;
}
