#include "World.h"

vector<shared_ptr<Entity>>* World::GetAllEntities()
{
	return &AllEntities;
}
