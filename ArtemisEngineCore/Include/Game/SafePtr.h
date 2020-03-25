#pragma once

#include "Source/Game/Object Management/ObjectCounter.h"

namespace ArtemisEngine
{
	// Provides a pointer that allows you to safely check
	// whether the object it points to has been destroyed.
	//
	// All references are weak, meaning they don't keep
	// the pointed object from being destroyed.
	template<class T>
	class SafePtr
	{
	public:
		SafePtr() = default;
		SafePtr(ObjectCounter* counter)
		{
			this->counter = counter;
		}
		~SafePtr() = default;
		
		// Returns whether the pointer is valid for dereferencing.
		bool IsValid()
		{
			return counter->IsAlive();
		}

		// Returns a raw pointer to the pointed to object.
		T* GetRaw()
		{
			return counter->GetRaw<T>();
		}

		// Dereferences the pointed to object.
		T* operator->()
		{
			return GetRaw();
		}

		// Implicitly converts to raw pointer of pointer to object.
		operator T* ()
		{
			return GetRaw();
		}

		// Returns whether the pointer can be safely dereferenced
		operator bool()
		{
			return IsValid();
		}

	private:
		ObjectCounter* counter;
	};
}