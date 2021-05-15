#pragma once

#include "Core/Types.h"

namespace ArtemisEngine
{
	class AllocatorUtility
	{
	public:
		static uint8 GetMemoryAddressAdjustment(void* address, uint8 alignment);
	};
}
