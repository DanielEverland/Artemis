#pragma once

#include <vector>

#include "ObjectContainer.h"

using std::vector;

namespace ArtemisEngine
{
	class IComponent;
	
	template<class T>
	class SafePtr;

	template<class T>
	class SafeObjRef;

	class ComponentContainer
	{
	public:
		template<class T>
		SafePtr<T> AddComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "AddComponent() type mismatch! T must inherit IComponent");

			return objContainer.Add();
		}

		template<class T>
		void RemoveComponent(const T* ptr)
		{
			static_assert(std::is_base_of<IComponent, T>::value, "RemoveComponent(T*) type mismatch! T must inherit IComponent");

			objContainer.Remove(ptr);
		}

		template<class T>
		SafePtr<T> GetComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "GetComponent() type mismatch! T must inherit IComponent");

			return objContainer.Get<T>();
		}

		template<class T>
		std::vector<SafePtr<T>> GetComponents()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "GetComponents() type mismatch! T must inherit IComponent");

			return std::move(objContainer.GetAll<T>());
		}

	private:
		ObjectContainer<IComponent> objContainer;
	};
}