#pragma once

#include <memory>
#include <utility>

#include "Include/Game/SafePtr.h"

namespace ArtemisEngine
{
	using std::shared_ptr;

	// Used to safely contain object which can be destroyed at
	// any time, even if other object have a reference to them.
	//
	// Useful for object types like GameObjects or Components.
	//
	// Encapsulate the actual objects internally using this class
	// Return a SafePtr to other objects who wish to reference
	// the object.
	template<class T>
	class SafeObjRef
	{
	public:
		SafeObjRef(const SafeObjRef<T>& other) = delete;
		SafeObjRef(SafeObjRef<T>&& other)
		{
			this->counter = other.counter;

			other.counter = nullptr;
		}
		SafeObjRef(T*&& ptr)
		{
			counter = new ObjectCounter(std::move(ptr));
		}
		~SafeObjRef()
		{
			// Can be true if moved
			if(counter != nullptr)
				counter->Delete();
		}
		
		// Creates a SafePtr to the referenced object.
		SafePtr<T> GetSafePtr()
		{
			return counter->GetSafePtr<T>();
		}

		// Returns a raw pointer to the referenced object.
		T* GetRaw() const
		{
			return counter->GetRaw<T>();
		}

		SafeObjRef<T>& operator=(const SafeObjRef<T>& other) = delete;
		SafeObjRef<T>& operator=(SafeObjRef<T>&& other)
		{
			this->counter = other.counter;

			other.counter = nullptr;

			return *this;
		}

	private:
		ObjectCounter* counter;
	};
}