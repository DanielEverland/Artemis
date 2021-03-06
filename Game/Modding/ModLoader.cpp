﻿#include <queue>
#include <filesystem>

#include <Game/Game.h>
#include <Core/IO/Directory.h>
#include <Core/Exceptions/ArgumentException.h>
#include <Core/Core/StringUtility.h>

#include "ModLoader.h"
#include "Mod.h"
#include "Core/IO/JsonException.h"
#include "Core/IO/Path.h"

string ModLoaderCategory = "ModLoader";
string ModLoader::EntityAssetExtension = ".entity";

set<string> ModLoader::LuaFileExtensions =
{
	".lua"
};

set<string> ModLoader::TextureFileExtensions =
{
	".png",
	".bmp"
};

map<string, EntityType> ModLoader::LoadedTypes = map<string, EntityType>();
map<string, unique_ptr<LuaState>> ModLoader::AllLuaFiles = { };
map<string, Texture> ModLoader::LoadedTextures = { };

string ModLoader::GetModdingDirectory()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);
	return Directory::GetProjectDirectory() + "Mods";
}

const map<string, unique_ptr<LuaState>>& ModLoader::GetAllLuaFiles()
{
	return AllLuaFiles;
}

EntityType* ModLoader::GetType(const string& typeName)
{
	if(!LoadedTypes.contains(typeName))
		throw ArgumentException("Attempted to get type \"" + typeName + "\", but the type isn't loaded");

	return &LoadedTypes.find(typeName)->second;
}

Texture* ModLoader::GetTexture(const string& textureName)
{
	if(!LoadedTextures.contains(textureName))
		throw ArgumentException("Attempted to get texture \"" + textureName + "\", but it isn't loaded");

	return &LoadedTextures.find(textureName)->second;
}

void ModLoader::LoadMods()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	LoadMods(GetModdingDirectory());
}

void ModLoader::LoadMods(const string& directory)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	Logger::Log(ModLoaderCategory, Verbosity::Verbose, "Outputting all mod directories");
	for (const string& modDirectory : GetAllModDirectories(directory))
	{
		TRY_START

		LoadMod(modDirectory);

		TRY_END_CUSTOM(ModLoaderCategory, Verbosity::Error, "Failed to load mod at directory " + directory);
	}

	LoadEntities();
}

std::vector<std::string> ModLoader::GetAllModDirectories(const string& directory)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	std::vector<string> modDirectories;
	
	std::queue<string> directoriesToSearch;
	directoriesToSearch.push(directory);

	while (!directoriesToSearch.empty())
	{
		const string currentDirectory = directoriesToSearch.front();
		directoriesToSearch.pop();

		Logger::Log(ModLoaderCategory, Verbosity::Verbose, "Checking directory " + currentDirectory);

		string modinfoPath;
		if(GetModInfoFilePath(currentDirectory, modinfoPath))
		{
			modDirectories.push_back(modinfoPath);
		}
		else
		{
			for(const string& subDirectory : Directory::GetAllDirectories(currentDirectory))
			{
				directoriesToSearch.push(subDirectory);
			}
		}
	}

	return modDirectories;
}

void ModLoader::LoadEntities()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);
	
	for(auto& [typeName, typeData] : LoadedTypes)
	{
		typeData.LoadData();
	}
}

void ModLoader::LoadMod(const string& directory)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);
	
	for (const auto iter : std::filesystem::recursive_directory_iterator(directory))
	{
		TRY_START
		
		LoadAsset(iter.path().string(), Path::GetFileNameExtension(iter.path().string()));

		TRY_END_CUSTOM(ModLoaderCategory, Verbosity::Error, "Failed loading asset " + directory);
	}
}

void ModLoader::LoadAsset(const string& fullPath, const string& extension)
{
	const string funcName = __FUNCTION__;
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, funcName + ": " + fullPath);

	if(extension == EntityAssetExtension)
	{
		LoadEntityAsset(fullPath);
	}

	if(LuaFileExtensions.contains(extension))
	{
		LoadLuaAsset(fullPath);
	}

	if(TextureFileExtensions.contains(extension))
	{
		LoadTexture(fullPath);
	}
}

void ModLoader::LoadEntityAsset(const string& fullPath)
{
	const string funcName = __FUNCTION__;
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, funcName + ": " + fullPath);

	auto json = Json::FromFile(fullPath);
	if(!json.Contains(JsonKeyType))
		throw JsonException(fullPath + ": Doesn't contain key " + JsonKeyType);

	if (!json.Contains(JsonKeyName))
		throw JsonException(fullPath + ": Doesn't contain key " + JsonKeyName);

	const auto typeName = json.At<string>(JsonKeyType);
	const EntityType entityType(typeName, json);

	LoadedTypes.insert(LoadedTypes.begin(), std::pair<string, EntityType>(typeName, entityType));
}

void ModLoader::LoadLuaAsset(const string& fullPath)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	const string luaName = Path::GetFileNameWithoutExtension(fullPath);
	Logger::Log(ModLoaderCategory, Verbosity::Verbose, "Loading Lua file: \"" + fullPath + "\" as Lua name \"" + luaName + "\"");
	
	AllLuaFiles.insert_or_assign(luaName, LuaState::CreateFromFile(fullPath));
}

void ModLoader::LoadTexture(const string& fullPath)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	const string textureName = Path::GetFileNameWithoutExtension(fullPath);
	Logger::Log(ModLoaderCategory, Verbosity::Verbose, "Loading texture: \"" + textureName+ "\"");

	LoadedTextures.insert_or_assign(textureName, Texture(fullPath));
}

bool ModLoader::GetModInfoFilePath(const string& directory, string& modFilePath)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	for (const string& filePath : Directory::GetAllFiles(directory))
	{
		const bool matchesFilename = Path::GetFileName(filePath) == Mod::ModInfoName;
		Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, "Checking " + filePath + "\n\t" + Path::GetFileName(filePath) + " == " + Mod::ModInfoName + ": " + StringUtility::BoolToString(matchesFilename));
		if(matchesFilename)
		{
			modFilePath = Path::RemoveLastDeliminatorPart(filePath);
			return true;
		}
	}

	return false;
}
