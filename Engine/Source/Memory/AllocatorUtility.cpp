#include "AllocatorUtility.h"

using namespace ArtemisEngine;

uint8 AllocatorUtility::GetMemoryAddressAdjustment(void* address, uint8 alignment)
{
#pragma warning(disable:4302)
	const uint8 adjustment = alignment - (reinterpret_cast<uint8>(address) & static_cast<uint8>(alignment - 1));
#pragma warning(default:4302)

	if (adjustment == alignment)
		return 0;

	return adjustment;
}