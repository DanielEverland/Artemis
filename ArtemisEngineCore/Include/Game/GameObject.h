#pragma once

#include "Source/Game/Object Management/ComponentContainer.h"

namespace ArtemisEngine
{
	class GameObject
	{
	public:
		template<class T>
		SafePtr<T> AddComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "AddComponent() type mismatch! T must inherit IComponent");

			return components.AddComponent<T>();
		}

		template<class T>
		void RemoveComponent(const T* ptr)
		{
			static_assert(std::is_base_of<IComponent, T>::value, "RemoveComponent(T*) type mismatch! T must inherit IComponent");

			components.RemoveComponent(ptr);
		}

		template<class T>
		SafePtr<T> GetComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "GetComponent() type mismatch! T must inherit IComponent");

			return components.GetComponent<T>();
		}

		template<class T>
		std::vector<SafePtr<T>> GetComponents()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "GetComponents() type mismatch! T must inherit IComponent");

			return components.GetComponents<T>();
		}

	private:
		ComponentContainer components;
	};
}