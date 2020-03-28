#pragma once


#include "Include/Exceptions/NullReferenceException.h"
#include "Source/Game/Object Management/ObjectCounter.h"

namespace ArtemisEngine
{
	template<class T>
	class SafeObjRef;

	// Provides a pointer that allows you to safely check
	// whether the object it points to has been destroyed.
	//
	// All references are weak, meaning they don't keep
	// the pointed object from being destroyed.
	template<class T>
	class SafePtr
	{
	public:
		SafePtr()
		{
			counter = nullptr;
		}
		SafePtr(const SafePtr<T>& other)
		{
			if (other.IsCounterPtrNull())
				throw NullReferenceException("Attempted to copy null safeptr");
			
			this->counter = other.counter;
			this->counter->AddWatcher();
		}
		SafePtr(SafePtr<T>&& other)
		{
			this->counter = other.counter;

			other.counter = nullptr;
		}
		SafePtr(ObjectCounter* counter)
		{
			this->counter = counter;
		}
		~SafePtr()
		{
			if(!IsCounterPtrNull())
				counter->RemoveWatcher();
		}
		
		// Returns whether the pointer is valid for dereferencing.
		bool IsValid() const
		{
			return !IsCounterPtrNull() && counter->IsAlive();
		}

		// Does this pointer not hold a reference to anything?
		bool IsCounterPtrNull() const
		{
			return counter == nullptr;
		}

		// Returns a raw pointer to the pointed to object.
		T* GetRaw() const
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

		template<class TOther>
		bool operator==(const SafePtr<TOther>& other) const
		{
			return other.counter == this->counter;
		}
		template<class TOther>
		bool operator!=(const SafePtr<TOther>& other) const
		{
			return other.counter != this->counter;
		}

		template<class TOther>
		operator SafePtr<TOther>()
		{
			static_assert(std::is_base_of<T, TOther>::value, "Downcast failed. T must be base class to TOher");

			return SafePtr<TOther>(counter);
		}
		SafePtr<T>& operator=(const SafePtr<T>& other)
		{
			if (other.IsCounterPtrNull())
				throw NullReferenceException("Attempted to copy null safeptr");

			this->counter = other.counter;
			this->counter->AddWatcher();
		}
		SafePtr<T>& operator=(SafePtr<T>&& other)
		{
			this->counter = other.counter;

			other.counter = nullptr;

			return *this;
		}

	private:
		ObjectCounter* counter;
	};
}