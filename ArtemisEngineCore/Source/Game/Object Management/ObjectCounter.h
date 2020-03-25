#pragma once

#include "Include/Exceptions/InvalidOperationException.h"

namespace ArtemisEngine
{
	template<class T>
	class SafePtr;

	class ObjectCounter
	{
	public:
		ObjectCounter(void*&& obj);
		~ObjectCounter() = default;

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