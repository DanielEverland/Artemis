#include "World.h"

vector<shared_ptr<Entity>>* World::GetAllEntities()
{
	return &AllEntities;
}

void World::Tick()
{
	for(const shared_ptr<Entity>& entity : AllEntities)
	{
		entity->Update();
	}
}
