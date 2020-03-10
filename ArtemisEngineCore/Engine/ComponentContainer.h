#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "IComponent.h"

using std::unique_ptr;
using std::vector;

class ComponentContainer
{
public:
	int GetCount() const;
	bool Contains(const IComponent* component) const;
	void RemoveComponent(const IComponent* component);

	template<class T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<IComponent, T>(), "Type mismatch in AddComponent() -> Component type must inherit IComponent");
		
		components.push_back(unique_ptr<IComponent>(new T()));
		T* newComponent = components.back().get();
		
		return newComponent;
	}

	template<class T>
	T* GetComponent()
	{
		static_assert(std::is_base_of<IComponent, T>(), "Type mismatch in GetComponent() -> Component type must inherit IComponent");
		T* componentToReturn = nullptr;

		for (auto iter = components.begin(); iter != components.end(); iter++)
		{
			componentToReturn = dynamic_cast<T*>((*iter).get());

			if (componentToReturn)
				return componentToReturn;
		}

		return componentToReturn;
	}

private:
	vector<unique_ptr<IComponent>> components;

	bool IsEqual(const vector<unique_ptr<IComponent>>::const_iterator& iter, const IComponent* const other) const;
};