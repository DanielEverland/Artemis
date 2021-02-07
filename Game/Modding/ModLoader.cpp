#include <queue>
#include <filesystem>

#include <Game.h>

#include "ModLoader.h"
#include "Mod.h"

string ModLoaderCategory = "ModLoader";
string ModLoader::EntityAssetExtension = ".entity";

set<string> ModLoader::LuaFileExtensions =
{
	".lua"
};

map<string, EntityType> ModLoader::LoadedTypes = map<string, EntityType>();
vector<unique_ptr<LuaState>> ModLoader::AllLuaFiles = { };

string ModLoader::GetModdingDirectory()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);
	return Directory::GetProjectDirectory() + "Mods";
}

EntityType* ModLoader::GetType(const string& typeName)
{
	if(!LoadedTypes.contains(typeName))
		throw ArgumentException("Attempted to get " + typeName + ", but the type isn't loaded");

	return &LoadedTypes.find(typeName)->second;
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
		LoadMod(modDirectory);
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
		LoadAsset(iter.path().string(), Path::GetFileNameExtension(iter.path().string()));
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
	
	AllLuaFiles.push_back(LuaState::CreateFromFile(fullPath));
}

bool ModLoader::GetModInfoFilePath(const string& directory, string& modFilePath)
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	for (const string& filePath : Directory::GetAllFiles(directory))
	{
		const bool matchesFilename = Path::GetFileName(filePath) == Mod::ModInfoName;
		Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, "Checking " + filePath + "\n\t" + Path::GetFileName(filePath) + " == " + Mod::ModInfoName + ": " + sbool(matchesFilename));
		if(matchesFilename)
		{
			modFilePath = Path::RemoveLastDeliminatorPart(filePath);
			return true;
		}
	}

	return false;
}
