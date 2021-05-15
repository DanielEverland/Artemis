#include "BaseAllocator.h"

using namespace ArtemisEngine;

BaseAllocator::BaseAllocator()
{
}

BaseAllocator::BaseAllocator(void* start, size_t size) : StartPosition(start), Size(size)
{
}
