#include "AllocatorUtility.h"

using namespace ArtemisEngine;

#pragma warning(disable:4302)
uint8 AllocatorUtility::GetMemoryAddressAdjustment(void* address, uint8 alignment)
{
	const uint8 adjustment = alignment - (reinterpret_cast<uint8>(address) & static_cast<uint8>(alignment - 1));

	if (adjustment == alignment)
		return 0;

	return adjustment;
}