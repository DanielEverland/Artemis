#include <queue>

#include <Game.h>

#include "ModLoader.h"

string DebugCategory = "ModLoader";

string ModLoader::ModInfoName = "modinfo.lua";

string ModLoader::GetModdingDirectory()
{
	return Directory::GetProjectDirectory() + "Mods";
}

void ModLoader::LoadMods()
{
	Logger::Log("ModLoader", Verbosity::VeryVerbose, "Outputting all mod directories");
	for(const string& modDirectory : GetAllModDirectories())
	{
		Logger::Log("ModLoader", Verbosity::VeryVerbose, modDirectory);
	}
}

std::vector<std::string> ModLoader::GetAllModDirectories()
{
	std::vector<string> modDirectories;
	
	std::queue<string> directoriesToSearch;
	directoriesToSearch.push(GetModdingDirectory());

	while (!directoriesToSearch.empty())
	{
		const string currentDirectory = directoriesToSearch.front();
		directoriesToSearch.pop();

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

bool ModLoader::GetModInfoFilePath(const string& directory, string& modFilePath)
{
	for (const string& filePath : Directory::GetAllFiles(directory))
	{
		if(Path::GetFileName(filePath) == ModInfoName)
		{
			modFilePath = Path::RemoveLastDeliminatorPart(filePath);
			return true;
		}
	}

	return false;
}
