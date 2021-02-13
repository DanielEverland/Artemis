#pragma once

#include <memory>

#include "../Modding/EntityType.h"

#include "Entity.h"

using std::weak_ptr;
using std::shared_ptr;

class World
{
public:	
	template<class T, typename = typename std::enable_if<std::is_base_of<Entity, T>::value, T>::type>
	weak_ptr<T> CreateEntity(const EntityType* type)
	{
		AllEntities.push_back(std::make_unique<T>(Entity(type, this)));
		return AllEntities.back();
	}
	
private:
	vector<shared_ptr<Entity>> AllEntities;
};