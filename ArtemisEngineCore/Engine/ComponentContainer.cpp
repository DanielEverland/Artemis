#include "ComponentContainer.h"

int ComponentContainer::GetCount() const
{
	return components.size();
}
bool ComponentContainer::Contains(const IComponent* component) const
{
	for (auto iter = components.begin(); iter != components.end(); iter++)
	{
		if (IsEqual(iter, component))
			return true;
	}

	return false;
}
void ComponentContainer::RemoveComponent(const IComponent* toRemove)
{
	for (auto iter = components.begin(); iter != components.end(); iter++)
	{
		if (IsEqual(iter, toRemove))
		{
			components.erase(iter);
			return;
		}
	}
}
bool ComponentContainer::IsEqual(const vector<unique_ptr<IComponent>>::const_iterator& iter, const IComponent* const other) const
{
	return (*iter).get() == other;
}