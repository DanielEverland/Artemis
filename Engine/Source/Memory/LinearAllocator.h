#pragma once

#include <Core.h>
#include <Memory/BaseAllocator.h>

namespace ArtemisEngine
{
	class LinearAllocator : public BaseAllocator
	{
	public:
		LinearAllocator();
		LinearAllocator(void* start, size_t size);
		virtual ~LinearAllocator();
		
		void* Allocate(const size_t size, const uint8 alignment) override;
		void Clear() override;
		
	private:
		void* CurrentPosition;

		[[nodiscard]] uintptr_t GetAlignedPosition(const uint8 alignment) const;
		void ForwardPosition(const size_t size);
	};
}
