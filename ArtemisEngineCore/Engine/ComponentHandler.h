#pragma once

#include <algorithm>
#include <memory>
#include <list>

#include "IComponent.h"

using std::shared_ptr;
using std::list;

class ComponentHandler
{
public:
	int GetCount() const;
	bool Contains(shared_ptr<IComponent> component) const;
	void RemoveComponent(shared_ptr<IComponent> component);

	template<class T>
	const shared_ptr<IComponent> AddComponent()
	{
		static_assert(std::is_base_of<IComponent, T>(), "Type mismatch in AddComponent() -> Component type must inherit IComponent");
		
		shared_ptr<IComponent> newComponent = shared_ptr<IComponent>(new T());
		components.push_back(newComponent);
		
		return newComponent;
	}

private:
	list<shared_ptr<IComponent>> components;
};