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
	static constexpr size_t LuaMembersSize = sizeof(Vector) + sizeof(Vector);
	
	[[nodiscard]] const EntityType* GetType() const { return Type; }
	[[nodiscard]] const Json* GetData() const;
	[[nodiscard]] virtual Rect GetBounds()  { return { { 0, 0 }, { 0, 0 } }; };

	virtual void Update();
	virtual void Draw() { }


	Entity(Entity&& other)
		: Object(std::move(other)),
		  LocalPosition(std::move(other.LocalPosition)),
		  LocalScale(std::move(other.LocalScale)),
		  Type(other.Type),
		  Scripts(std::move(other.Scripts))
	{
	}

	Entity& operator=(Entity&& other)
	{
		if (this == &other)
			return *this;
		Object::operator =(std::move(other));
		LocalPosition = std::move(other.LocalPosition);
		LocalScale = std::move(other.LocalScale);
		Type = other.Type;
		Scripts = std::move(other.Scripts);
		return *this;
	}
	std::vector<LuaState*> Scripts;

	Vector LocalPosition;
protected:
	Vector LocalScale;

	LuaState* GetLuaState() const;
	
private:
	const EntityType* Type;

	void LoadScripts();
	//void CreateLuaUserData();
};