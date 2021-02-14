#pragma once

#include <type_traits>

#include "Object.h"
#include "Core/IO/Json.h"

class EntityType;

class Entity : public Object
{
public:
	Entity(const EntityType* type, World* world);
	virtual ~Entity() = default;

	[[nodiscard]] const EntityType* GetType() const { return Type; }
	[[nodiscard]] const Json* GetData() const;

	virtual void Draw() = 0;

private:
	const EntityType* Type;
};