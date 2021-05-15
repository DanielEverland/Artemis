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
		void* StartPosition;
		size_t Size;
	};
}
