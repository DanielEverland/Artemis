#pragma once

#include "Core/Types.h"

namespace ArtemisEngine
{
	class AllocatorUtility
	{
	public:
		static uint8 GetMemoryAddressAdjustment(void* address, uint8 alignment);
		static uint8 GetMemoryAddressAdjustmentWithHeader(void* address, uint8 alignment, uint8 headerSize);
		static uintptr_t GetAddress(const void* ptr);

		template<class T>
		static T* GetPointer(uintptr_t address);

		template<class T>
		static T* SubtractPointer(const void* obj, size_t adjustment);

		template<class T>
		static T* AddPointer(const void* obj, size_t adjustment);
	};

	template <class T>
	T* AllocatorUtility::GetPointer(uintptr_t address)
	{
		return reinterpret_cast<T*>(address);
	}

	template <class T>
	T* AllocatorUtility::SubtractPointer(const void* obj, const size_t adjustment)
	{
		return GetPointer<T>(GetAddress(obj) - adjustment);
	}

	template <class T>
	T* AllocatorUtility::AddPointer(const void* obj, const size_t adjustment)
	{
		return GetPointer<T>(GetAddress(obj) + adjustment);
	}
}
