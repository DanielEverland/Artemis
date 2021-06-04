#pragma once

#include "BaseAllocator.h"
#include "IDeallocator.h"

namespace ArtemisEngine
{
	class FreeListAllocator : public BaseAllocator, public IDeallocator
	{
	public:
		FreeListAllocator();
		FreeListAllocator(void* start, size_t size);

		void* Allocate(size_t size, uint8 alignment) override;
		void Deallocate(const void* const object) override;
		
	private:
		struct MemoryBlock
		{
			size_t Size;
			MemoryBlock* Next;
		};
		
		struct AllocationHeader
		{
			uint8 Adjustment;
			size_t Size;
		};
		
		MemoryBlock* AllBlocks;

		static MemoryBlock* SetBlock(MemoryBlock* block, size_t size, MemoryBlock* next);
		static MemoryBlock* SetBlock(uintptr_t address, size_t size, MemoryBlock* next);
	};
}
