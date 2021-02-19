#pragma once

#include <Core/Core/Vector.h>
#include <Core/Core/Rect.h>
#include "Object.h"
#include "Core/IO/Json.h"
#include "Lua/Core/LuaState.h"

class EntityType;

class Entity : public Object
{
public:
	Entity(const EntityType* type, World* world);
	virtual ~Entity() = default;

	[[nodiscard]] const EntityType* GetType() const { return Type; }
	[[nodiscard]] const Json* GetData() const;
	[[nodiscard]] virtual Rect GetBounds()  { return { { 0, 0 }, { 0, 0 } }; };

	virtual void Update();
	virtual void Draw() { }

protected:
	Vector LocalPosition;
	Vector LocalScale;
	
private:
	const EntityType* Type;
	std::vector<LuaState*> Scripts;

	void LoadScripts();
};