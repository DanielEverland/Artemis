#pragma once

#include <Core/Core/Vector.h>
#include <Core/Core/Rect.h>
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
	[[nodiscard]] virtual Rect GetBounds() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Vector LocalPosition;
	Vector LocalScale;
	
private:
	const EntityType* Type;
};