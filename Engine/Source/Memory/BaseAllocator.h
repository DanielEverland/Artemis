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

		virtual void Clear() = 0;

	protected:
		void* StartPosition;
		size_t Size;
	};
}
