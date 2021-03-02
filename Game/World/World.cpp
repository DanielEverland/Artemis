#include "World.h"

#include "Game/Framework/Application.h"

const string World::LogCategoryWorld = "World";

shared_ptr<LuaState> World::GetGlobalState()
{
	return Application::GetGlobalLuaState();
}

void World::Tick()
{
	/*for(const shared_ptr<Entity>& entity : AllEntities)
	{
		entity->Update();
	}*/
}

int World::CFunc_ObjectGarbageCollected(lua_State* luaState)
{
	const bool topIsUserData = lua_isuserdata(luaState, lua_gettop(luaState));
	if(!topIsUserData)
		throw LuaRuntimeException(string(__FUNCTION__) + ": Top of stack is not of type userdata! Actual Type: " + TypeToString(lua_type(luaState, lua_gettop(luaState))));

	void* userData = lua_touserdata(luaState, lua_gettop(luaState));
	Application::GetWorld()->RemoveObject(userData);
	
	return 0;
}

void World::InitializeNewEntity(const shared_ptr<Entity>& newEntity)
{
	newEntity->LocalPosition.X = 1.5;
		
	lua_State* L = *GetGlobalState();
	luaL_getmetatable(L, LuaEntityMetaTableName.c_str());
	lua_pushstring(L, "__gc");
	lua_settable(L, -2);
}

void World::RemoveObject(void* rawObjPtr)
{
	AllEntities.erase(rawObjPtr);
}
