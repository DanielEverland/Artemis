#include "Entity.h"

Entity::Entity(const EntityType* type, World* world) : Object(world), Type(type)
{
}
