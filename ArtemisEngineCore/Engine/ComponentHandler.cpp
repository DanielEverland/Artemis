#include "ComponentHandler.h"

int ComponentHandler::GetCount() const
{
	return components.size();
}
bool ComponentHandler::Contains(shared_ptr<IComponent> component) const
{
	return std::find(components.begin(), components.end(), component) != components.end();
}
void ComponentHandler::RemoveComponent(shared_ptr<IComponent> component)
{
	components.remove(component);
}