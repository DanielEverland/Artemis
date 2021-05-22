#pragma once

#include "BaseAllocator.h"

namespace ArtemisEngine
{
	class StackAllocator : public BaseAllocator
	{
	public:
		StackAllocator();
		StackAllocator(void* start, size_t size);
		~StackAllocator() override;

		void* Allocate(size_t size, uint8 alignment) override;
		void Deallocate();
	};
}