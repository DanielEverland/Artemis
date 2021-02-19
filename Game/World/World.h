#pragma once

#include <memory>

#include <Core/Debugging/Logger.h>
#include <Core/Debugging/Verbosity.h>

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
		Logger::Log(LogCategoryWorld, Verbosity::Verbose, "Creating entity of type \"" + static_cast<string>(*type) + "\"");
			
		AllEntities.push_back(std::make_shared<T>(T(type, this)));
		return std::dynamic_pointer_cast<T>(AllEntities.back());
	}

	vector<shared_ptr<Entity>>* GetAllEntities();
	void Tick();
	
private:
	vector<shared_ptr<Entity>> AllEntities;

	static const string LogCategoryWorld;
};