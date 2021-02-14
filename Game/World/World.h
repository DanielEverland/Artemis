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
	shared_ptr<T> CreateEntity(const EntityType* type)
	{
		AllEntities.push_back(std::make_shared<T>(T(type, this)));
		return std::dynamic_pointer_cast<T>(AllEntities.back());
	}

	vector<shared_ptr<Entity>>* GetAllEntities();
	
private:
	vector<shared_ptr<Entity>> AllEntities;
};