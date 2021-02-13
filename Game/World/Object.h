#pragma once

#include <memory>

using std::weak_ptr;

class World;

class Object
{
public:
	Object(World* world);

 	[[nodiscard]] virtual World* GetWorld() const { return PrivateWorld; }
		
private:
	World* PrivateWorld;
};