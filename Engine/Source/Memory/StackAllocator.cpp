#include "StackAllocator.h"

#include <Core/Macros.h>
#include <Core/Math.h>
#include <Exception/ArgumentException.h>

using namespace ArtemisEngine;

StackAllocator::StackAllocator() : BaseAllocator()
{
}

StackAllocator::StackAllocator(void* start, size_t size) : BaseAllocator(start, size)
{
}

StackAllocator::~StackAllocator() = default;

NO_WARNING_BEGIN
void* StackAllocator::Allocate(size_t size, uint8 alignment)
{
	Assert(size > 0, ArgumentException("Cannot allocate memory of non-positive size"))
	Assert(alignment > 0, ArgumentException("Cannot allocate memory with an alignment of 0"))
	Assert(Math::IsPowerOfTwo(alignment), ArgumentException("Alignment must be power of two!"))

	return nullptr;
}

void StackAllocator::Deallocate()
{
}
