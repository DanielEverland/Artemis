#pragma once

#include "BaseAllocator.h"
#include "IDeallocator.h"

namespace ArtemisEngine
{
	class StackAllocator : public BaseAllocator, public IDeallocator
	{
	public:
		StackAllocator();
		StackAllocator(void* start, size_t size);
		~StackAllocator() override;

		void* Allocate(size_t size, uint8 alignment) override;
		void Deallocate(const void* const block) override;
		
	private:
		struct AllocationHeader
		{
			uint8 Adjustment;

#if _DEBUG
			void* Previous;
#endif
		};
		
		void* Current{};

#if _DEBUG
		void* Previous{};
#endif
		
		static uint8 GetHeaderSize();

		void ForwardPosition(uintptr_t alignedAddress, size_t size);
		void CreateAllocationHeader(uintptr_t alignedAddress, uint8 adjustment) const;
	};
}
