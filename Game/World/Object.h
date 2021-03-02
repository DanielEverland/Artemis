#pragma once

#include <memory>

using std::weak_ptr;

class World;

class Object
{
public:
	virtual ~Object() = default;
	//Object(World* world);

 	[[nodiscard]] virtual World* GetWorld() const { return PrivateWorld; }
		
private:
	World* PrivateWorld;
};