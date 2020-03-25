#pragma once

#include <vector>

#include "SafeObjRef.h"

namespace ArtemisEngine
{
	template<class T>
	class SafePtr;

	template<class T>
	class ObjectContainer
	{
	public:
		SafePtr<T> Add()
		{
			objects.push_back(SafeObjRef(new T()));
			return objects.back().GetSafePtr();
		}
		void Remove(SafePtr<T> toRemove)
		{
			Remove(toRemove.GetRaw());
		}
		void Remove(T* rawPtr)
		{
			for (auto ptr = objects.begin(); ptr != objects.end(); ptr++)
			{
				if (ptr->GetRaw() == rawPtr)
				{
					objects.erase(ptr);
					break;
				}
			}
		}
		bool Contains(SafePtr<T> ptr) const
		{
			if (!ptr.IsValid())
				return false;

			return Contains(ptr.GetRaw());
		}
		bool Contains(T* rawPtr) const
		{
			if (rawPtr == nullptr)
				return false;

			for (auto ptr = objects.begin(); ptr != objects.end(); ptr++)
			{
				if (ptr->GetRaw() == rawPtr)
					return true;
			}

			return false;
		}

	private:
		std::vector<SafeObjRef<T>> objects;
	};
}