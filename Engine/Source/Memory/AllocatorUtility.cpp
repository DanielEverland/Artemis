#include "AllocatorUtility.h"

#include <Core/Macros.h>
#include <Core/Math.h>
#include <Exception/ArgumentException.h>

using namespace ArtemisEngine;

uint8 AllocatorUtility::GetMemoryAddressAdjustment(void* address, uint8 alignment)
{
	Assert(Math::IsPowerOfTwo(alignment), ArgumentException("Alignment must be power of two!"))
	
#pragma warning(disable:4302)
	const uint8 adjustment = alignment - (reinterpret_cast<uint8>(address) & static_cast<uint8>(alignment - 1));
#pragma warning(default:4302)

	if (adjustment == alignment)
		return 0;

	return adjustment;
}

uint8 AllocatorUtility::GetMemoryAddressAdjustmentWithHeader(void* address, uint8 alignment, uint8 headerSize)
{
	Assert(headerSize > 0, ArgumentException("Header size must be a positive unsigned int"));
	
	uint8 adjustment = GetMemoryAddressAdjustment(address, alignment);
	
	if(adjustment < headerSize)
	{
		adjustment += alignment * ((headerSize - adjustment) / alignment);

		if(headerSize % alignment > 0)
			adjustment += alignment;
	}

	return adjustment;
}

uintptr_t AllocatorUtility::GetAddress(const void* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}
