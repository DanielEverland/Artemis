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

		void Delete();
		bool IsAlive() const;
		void RemoveWatcher();
		
		template<class T>
		T* GetRaw() const
		{
			return static_cast<T*>(obj);
		}

		template<class T>
		SafePtr<T> GetSafePtr()
		{
			watchers++;
			return SafePtr<T>(this);
		}

	private:
		void DeleteSelfIfReady();

		void* obj;
		int watchers;
		bool isAlive;
	};
}