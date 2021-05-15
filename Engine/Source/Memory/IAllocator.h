#pragma once

#include <Core.h>

namespace ArtemisEngine
{	
	class IAllocator
	{
	public:
		virtual ~IAllocator() = default;
		
		virtual void* Allocate(size_t size, uint8 alignment = DEFAULT_ALIGNMENT) = 0;

	private:
		static const uint8 DEFAULT_ALIGNMENT;
	};
}