#include "Entity.h"

#include <ArgumentException.h>
#include <Game/Modding/EntityType.h>

#include "Core/Debugging/Logger.h"
#include "Core/Debugging/Verbosity.h"

namespace
{
	const string LogCategoryEntity = "Entity";
}

Entity::Entity(const EntityType* type, World* world) : Object(world), Type(type)
{
	if(type == nullptr)
		throw ArgumentException("Type is null");

	Logger::Log(LogCategoryEntity, Verbosity::VeryVerbose, "Creating entity of type \"" + type->ToString() + "\"");
}

const Json* Entity::GetData() const
{
	return GetType()->GetData();
}
