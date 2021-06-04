#pragma once

#include <Core.h>
#include <Memory/IAllocator.h>

namespace ArtemisEngine
{
	class BaseAllocator : public IAllocator
	{
	public:
		BaseAllocator();
		BaseAllocator(void* start, size_t size);
		virtual ~BaseAllocator() = default;

	protected:
		bool IsOutOfBounds(const void* const pointer, size_t size = 0) const;
		
		void* StartPosition;
		size_t Size;
	};
}
