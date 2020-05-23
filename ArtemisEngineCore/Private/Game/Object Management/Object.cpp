#include "Include/Game/Object.h"
#include "Include/Game/World.h"

using namespace ArtemisEngine;

unsigned int Object::GetUniqueID() const
{
	return uniqueID;
}

bool Object::IsInstantiated() const
{
	return instantiated;
}

void Object::Begin()
{
}

World* Object::GetWorld()
{
	return World::GetWorld();
}

void Object::SetInstantiated(bool value)
{
	instantiated = true;
}
