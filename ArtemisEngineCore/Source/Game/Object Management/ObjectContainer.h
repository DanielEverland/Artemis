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
		template<class TAdd>
		SafePtr<TAdd> Add()
		{
			static_assert(std::is_base_of<T, TAdd>::value, "Type mismatch in ObjectContainer:Add(). TAdd must be a base type of T!");
			
			objects.push_back(std::move(SafeObjRef<T>(new TAdd())));
			return objects.back().GetSafePtr();
		}
		bool Remove(const SafePtr<T>& toRemove)
		{
			int origSize = objects.size();

			objects.erase(
				std::remove_if(objects.begin(), objects.end(), [&toRemove](const SafeObjRef<T>& obj) -> bool { return toRemove == obj; }),
				objects.end());

			return origSize != objects.size();
		}
		bool Remove(T* rawPtr)
		{
			int origSize = objects.size();

			objects.erase(
				std::remove_if(objects.begin(), objects.end(), [&rawPtr](const SafeObjRef<T>& obj) -> bool { return rawPtr == obj; }),
				objects.end());

			return origSize != objects.size();
		}
		bool Contains(SafePtr<T>& ptr) const
		{
			if (!ptr.IsValid())
				return false;

			auto iter = std::find(objects.begin(), objects.end(), ptr);

			return iter != objects.end();
		}
		bool Contains(T* rawPtr) const
		{
			if (rawPtr == nullptr)
				return false;

			auto iter = std::find(objects.begin(), objects.end(), rawPtr);

			return iter != objects.end();
		}

	private:
		std::vector<SafeObjRef<T>> objects;
	};
}