#pragma once

#include <memory>
#include <utility>

#include "Include/Exceptions/InvalidOperationException.h"
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
			if (!IsValid())
				throw NullReferenceException("Cannot get SafePtr from invalid SaveObjRef");

			return counter->GetSafePtr<T>();
		}

		// Returns a raw pointer to the referenced object.
		T* GetRaw() const
		{
			if(!IsValid())
				throw NullReferenceException("Cannot get raw ptr from invalid SaveObjRef");

			return counter->GetRaw<T>();
		}

		// Returns whether this object has a reference
		bool IsValid() const
		{
			return counter != nullptr;
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