#include "ComponentContainer.h"

int ComponentContainer::GetCount() const
{
	return components.size();
}
bool ComponentContainer::Contains(const IComponent* component) const
{
	for (auto iter = components.begin(); iter != components.end(); iter++)
	{
		if ((*iter).get() == component)
			return true;
	}

	return false;
}
void ComponentContainer::RemoveComponent(const IComponent* toRemove)
{
	components.remove_if([toRemove](unique_ptr<IComponent> storedComponent) -> bool { return storedComponent.get() == toRemove;  });
}