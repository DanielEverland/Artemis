#pragma once

#include "Include/Exceptions/InvalidOperationException.h"

namespace ArtemisEngine
{
	template<class T>
	class SafePtr;

	// Object used by SafeObjRef and SafePtr to determine
	// whether an object has been destroyed or not
	//
	// This should always be allocated dynamically since
	// it is in charge of destroying itself. This is
	// because it can persist after its owner has been
	// destroyed, while it still has watchers
	class ObjectCounter
	{
	public:
		ObjectCounter(void*&& obj);
		~ObjectCounter()
		{
		}

		ObjectCounter(const ObjectCounter& other) = delete;
		ObjectCounter(ObjectCounter&& other) = delete;

		void Delete();
		bool IsAlive() const;
		void RemoveWatcher();
		void AddWatcher();
		
		template<class T>
		T* GetRaw() const
		{
			return static_cast<T*>(obj);
		}

		template<class T>
		SafePtr<T> GetSafePtr()
		{
			AddWatcher();
			return SafePtr<T>(this);
		}

		ObjectCounter& operator=(const ObjectCounter& other) = delete;
		ObjectCounter& operator=(ObjectCounter&& other) = delete;

	private:
		void DeleteSelfIfReady();

		void* obj;
		int watchers;
		bool isAlive;
	};
}