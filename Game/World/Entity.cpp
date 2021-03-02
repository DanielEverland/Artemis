#include "Entity.h"

#include <ArgumentException.h>
#include <Game/Modding/EntityType.h>

#include "Core/Debugging/Logger.h"
#include "Core/Debugging/Verbosity.h"
#include "Game/Modding/ModLoader.h"

namespace
{
	const string LogCategoryEntity = "Entity";
}

const Json* Entity::GetData() const
{
	return GetType()->GetData();
}

void Entity::Update()
{
	for(LuaState* state : Scripts)
	{
		if(state->HasFunction(LuaUpdateFunctionName))
		{
			state->CallFunction(LuaUpdateFunctionName);
		}
	}
}

LuaState* Entity::GetLuaState() const
{
	return nullptr;
}

void Entity::LoadScripts()
{
	if(!Type->GetData()->Contains(JsonVariableScriptsName))
		return;

	auto scriptNames = Type->GetData()->At<std::vector<string>>(JsonVariableScriptsName);
	for(const string& scriptName : scriptNames)
	{
		if(!ModLoader::GetAllLuaFiles().contains(scriptName))
		{
			Logger::Log(LogCategoryEntity, Verbosity::Error, "Attempted to load script " + scriptName + ", but it hasn't been loaded");
			continue;
		}

		Logger::Log(LogCategoryEntity, Verbosity::Verbose, "Loading script \"" + scriptName + "\" for type \"" + static_cast<string>(*Type) + "\"");
		Scripts.push_back(ModLoader::GetAllLuaFiles().at(scriptName).get());
	}
}

//void Entity::CreateLuaUserData()
//{
//	size_t userDataSize = LuaMembersSize;
//	
//}
