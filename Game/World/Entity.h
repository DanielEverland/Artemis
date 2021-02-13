#pragma once

#include <type_traits>

#include "Object.h"

class EntityType;

class Entity : public Object
{
public:
	Entity(const EntityType* type, World* world);

	[[nodiscard]] const EntityType* GetType() const { return Type; }

private:
	const EntityType* Type;
};