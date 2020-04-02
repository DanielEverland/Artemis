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
		template<class U>
		SafeObjRef(U*&& ptr)
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch. U must inherit from T");

			counter = new ObjectCounter(std::move(ptr));
		}
		~SafeObjRef()
		{
			// Can be true if moved
			if(counter != nullptr)
				counter->Delete();
		}
		
		// Creates a SafePtr to the referenced object.
		template<class U>
		SafePtr<U> GetSafePtr()
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch. U must inherit from T");

			if (!IsValid())
				throw NullReferenceException("Cannot get SafePtr from invalid SaveObjRef");
			
			if (CanGetSafePtr<U>())
			{
				return counter->GetSafePtr<U>();
			}
			else
			{
				return SafePtr<U>(nullptr);
			}
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

		// Returns whether U derives from this instance template type
		template<class U>
		bool CanGetSafePtr() const
		{
			return dynamic_cast<U*>(counter->GetRaw<T>());
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

	// SafeObjRef == SafePtr
	template<class T1, class T2>
	bool operator==(const SafeObjRef<T1>& objRef, const SafePtr<T2>& objPtr)
	{
		return objRef.GetRaw() == objPtr.GetRaw();
	}
	template<class T1, class T2>
	bool operator==(const SafePtr<T1>& objPtr, const SafeObjRef<T2>& objRef)
	{
		return objRef.GetRaw() == objPtr.GetRaw();
	}

	// SafeObjRef != SafePtr
	template<class T1, class T2>
	bool operator!=(const SafeObjRef<T1>& objRef, const SafePtr<T2>& objPtr)
	{
		return objRef.GetRaw() != objPtr.GetRaw();
	}
	template<class T1, class T2>
	bool operator!=(const SafePtr<T1>& objPtr, const SafeObjRef<T2>& objRef)
	{
		return objRef.GetRaw() != objPtr.GetRaw();
	}

	// SafeObjRef == T*
	template<class T1, class T2>
	bool operator==(const SafeObjRef<T1>& objRef, const T2* rawPtr)
	{
		return objRef.GetRaw() == rawPtr;
	}
	template<class T1, class T2>
	bool operator==(const T1* rawPtr, const SafeObjRef<T2>& objRef)
	{
		return objRef.GetRaw() == rawPtr;
	}

	// SafeObjRef != T*
	template<class T1, class T2>
	bool operator!=(const SafeObjRef<T1>& objRef, const T2* rawPtr)
	{
		return objRef.GetRaw() != rawPtr;
	}
	template<class T1, class T2>
	bool operator!=(const T1* rawPtr, const SafeObjRef<T2>& objRef)
	{
		return objRef.GetRaw() != rawPtr;
	}
}