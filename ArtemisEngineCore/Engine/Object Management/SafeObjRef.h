#pragma once

#include <memory>

#include "Engine/SafePtr.h"

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
		SafeObjRef(T*&& ptr)
		{
			obj = shared_ptr<T>(ptr);
		}
		
		// Creates a SafePtr to the referenced object.
		SafePtr<T> GetSafePtr()
		{
			return SafePtr<T>(std::weak_ptr<T>(obj), obj.get());
		}

	private:
		// This pointer should _never_ be shared outside of this class
		// Use it as if it were a unique_ptr
		shared_ptr<T> obj;
	};
}