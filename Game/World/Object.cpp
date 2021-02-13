#include "Object.h"

#include <ArgumentException.h>

Object::Object(World* world) : PrivateWorld(world)
{
	if(world == nullptr)
		throw ArgumentException("World is null");
}
