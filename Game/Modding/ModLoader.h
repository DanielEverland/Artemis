#pragma once

#include <string>
#include <vector>

#include "Entity.h"
#include "EntityType.h"

using std::string;

class ModLoader
{
public:
	static string EntityAssetExtension;
	static set<string> LuaFileExtensions;
	
	static string GetModdingDirectory();

	static EntityType* GetType(const string& typeName);
	static void LoadMods();
	static void LoadMods(const string& directory);
	static std::vector<string> GetAllModDirectories(const string& directory);

private:
	// First step in loading types is to load all their prototypes and typename into memory.
	// We have to load them all individually first so that all available types are known when the type hierarchy has to be loaded.
	static map<string, EntityType> LoadedTypes;
	static vector<unique_ptr<LuaState>> AllLuaFiles;

	static void LoadEntities();
	static void LoadMod(const string& directory);
	static void LoadAsset(const string& fullPath, const string& extension);
	static bool GetModInfoFilePath(const string& directory, string& modFilePath);
	
	static void LoadEntityAsset(const string& fullPath);
	static void LoadLuaAsset(const string& fullPath);
};
