#pragma once

#include <memory>

namespace ArtemisEngine
{
	template<class T>
	class SafeObjRef;

	using std::weak_ptr;

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
		~SafePtr() = default;
		
		// Returns whether the pointer is valid for dereferencing.
		bool IsValid()
		{
			return !ptr.expired();
		}

		// Dereferences the pointed to object.
		T* operator->()
		{
			return rawPtr;
		}

		// Implicitly converts to raw pointer of pointer to object.
		operator T* ()
		{
			return rawPtr;
		}

		// Returns whether the pointer can be safely dereferenced
		operator bool()
		{
			return IsValid();
		}

	private:
		friend class SafeObjRef<T>;
		SafePtr(weak_ptr<T>& objReference, T* rawPtr)
		{
			this->ptr = objReference;
			this->rawPtr = rawPtr;
		}

		// The weak pointer is used to check for validity
		// The raw pointer is used for dereferencing
		weak_ptr<T> ptr;
		T* rawPtr;
	};
}