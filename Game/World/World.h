#pragma once

#include <memory>
#include <map>

#include <Core/Debugging/Logger.h>
#include <Core/Debugging/Verbosity.h>

#include "../Modding/EntityType.h"

#include "Entity.h"
#include "InvalidOperationException.h"

using std::weak_ptr;
using std::shared_ptr;

template<class T> class EntityIterator;

class World
{
public:
	template<class T, typename = typename std::enable_if<std::is_base_of<Entity, T>::value, T>::type>
	shared_ptr<T> CreateEntity(const EntityType* type)
	{
		Logger::Log(LogCategoryWorld, Verbosity::Verbose, "Creating entity of type \"" + static_cast<string>(*type) + "\"");

		void* rawObjPtr = lua_newuserdata(GetGlobalState()->GetRaw(), sizeof(Entity));
		if(rawObjPtr == nullptr)
			throw LuaRuntimeException("Unable to create new object of type " + string(typeid(T).name()));

		shared_ptr<T> smartPtr = shared_ptr<T>(static_cast<T*>(rawObjPtr));

		map<void*, shared_ptr<Entity>>::iterator iter;
		bool inserted = false;
		std::tie(iter, inserted) = AllEntities.try_emplace(rawObjPtr, std::dynamic_pointer_cast<Entity>(smartPtr));

		if(!inserted)
			throw InvalidOperationException("Insertion of new object failed");
		
		InitializeNewEntity(smartPtr);
		
		return smartPtr;
	}

	static shared_ptr<LuaState> GetGlobalState();

	template<class T>
	EntityIterator<T> GetEntityIterator();
	
	void Tick();
	
private:
	map<void*, shared_ptr<Entity>> AllEntities;

	static const string LogCategoryWorld;

	static int CFunc_ObjectGarbageCollected(lua_State* luaState);
	
	void InitializeNewEntity(const shared_ptr<Entity>& newEntity);
	void RemoveObject(void* rawObjPtr);
};

template <class T>
EntityIterator<T> World::GetEntityIterator()
{
	return EntityIterator<T>(AllEntities);
}
