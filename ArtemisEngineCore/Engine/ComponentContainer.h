#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Object Management/IComponent.h"

using std::weak_ptr;
using std::unique_ptr;
using std::vector;

class ComponentContainer
{
public:
	ComponentContainer() = default;
	~ComponentContainer()
	{
		(*releasedPointers.back()) = nullptr;
		delete components.back();
	}

	int GetCount() const;
	//bool Contains(const IComponent* component) const;
	//void RemoveComponent(const IComponent* component);
	
	template<class T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<IComponent, T>(), "Type mismatch in AddComponent() -> Component type must inherit IComponent");
		
		T* newComponent = new T();
		components.push_back(newComponent);
		releasedPointers.push_back(&newComponent);

		return newComponent;
	}

	/*template<class T>
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
	}*/

private:
	vector<IComponent**> releasedPointers;
	vector<IComponent*> components;

	//bool IsEqual(const vector<IComponent*>::const_iterator& iter, const IComponent* const other) const;
};