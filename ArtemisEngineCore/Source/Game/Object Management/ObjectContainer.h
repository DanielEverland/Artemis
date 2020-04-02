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
		template<class U>
		SafePtr<U> Add()
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in Add(). Passed type does not derive from type of container!");
			
			objects.push_back(std::move(SafeObjRef<T>(new U())));
			return objects.back().GetSafePtr<U>();
		}
		template<class U>
		bool Remove(const SafePtr<U>& toRemove)
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in Remove(SafePtr<U>&). Passed type does not derive from type of container!");

			int origSize = objects.size();

			objects.erase(
				std::remove_if(objects.begin(), objects.end(), [&toRemove](const SafeObjRef<T>& obj) -> bool { return toRemove == obj; }),
				objects.end());

			return origSize != objects.size();
		}
		template<class U>
		bool Remove(U* rawPtr)
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in Remove(U*). Passed type does not derive from type of container!");

			int origSize = objects.size();

			objects.erase(
				std::remove_if(objects.begin(), objects.end(), [&rawPtr](const SafeObjRef<T>& obj) -> bool { return rawPtr == obj; }),
				objects.end());

			return origSize != objects.size();
		}
		template<class U>
		bool Contains(SafePtr<U>& ptr) const
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in Contains(SafePtr<U>&). Passed type does not derive from type of container!");

			if (!ptr.IsValid())
				return false;

			auto iter = std::find(objects.begin(), objects.end(), ptr);

			return iter != objects.end();
		}
		template<class U>
		bool Contains(U* rawPtr) const
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in Contains(U*). Passed type does not derive from type of container!");

			if (rawPtr == nullptr)
				return false;

			auto iter = std::find(objects.begin(), objects.end(), rawPtr);

			return iter != objects.end();
		}
		template<class U>
		SafePtr<U> Get()
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in Get(). Passed type does not derive from type of container!");

			auto iter = std::find_if(objects.begin(), objects.end(), [](const SafeObjRef<T>& objRef) -> bool { return objRef.CanGetSafePtr<U>(); });

			if (iter != objects.end())
			{
				return iter->GetSafePtr<U>();
			}
			else
			{
				return SafePtr<U>(nullptr);
			}			
		}
		template<class U>
		std::vector<SafePtr<U>> GetAll()
		{
			static_assert(std::is_base_of<T, U>::value, "Type mismatch in GetAll(). Passed type does not derive from type of container!");

			std::vector<SafePtr<U>> toReturn;

			for (SafeObjRef<T>& obj : objects)
			{
				if (obj.CanGetSafePtr<U>())
				{
					toReturn.push_back(obj.GetSafePtr<U>());
				}
			}

			return toReturn;
		}

	private:
		std::vector<SafeObjRef<T>> objects;
	};
}