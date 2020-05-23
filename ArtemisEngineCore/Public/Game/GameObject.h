#pragma once

#include "Private/Game/Object Management/ComponentContainer.h"

#include "Object.h"
#include "Transform.h"

namespace ArtemisEngine
{
	class GameObject : public Object
	{
	public:
		template<class T>
		[[nodiscard]] SafePtr<T> GetComponent() const
		{
			static_assert(std::is_base_of<IComponent, T>::value, "GetComponent() type mismatch! T must inherit IComponent");

			return components.GetComponent<T>();
		}

		template<class T>
		[[nodiscard]] std::vector<SafePtr<T>> GetComponents() const
		{
			static_assert(std::is_base_of<IComponent, T>::value, "GetComponents() type mismatch! T must inherit IComponent");

			return components.GetComponents<T>();
		}

		[[nodiscard]] Vector3 GetPosition() const;
		[[nodiscard]] Quaternion GetRotation() const;
		[[nodiscard]] Vector3 GetScale() const;
		[[nodiscard]] const Transform* GetTransform() const;
		
	protected:
		Transform transform;

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
		
	private:
		ComponentContainer components;
	};
}