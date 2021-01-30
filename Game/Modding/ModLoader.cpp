#include <queue>

#include <Game.h>

#include "ModLoader.h"
#include "Mod.h"

string ModLoaderCategory = "ModLoader";

string ModLoader::GetModdingDirectory()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);
	return Directory::GetProjectDirectory() + "Mods";
}

void ModLoader::LoadMods()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	std::vector<string> modDirectories = GetAllModDirectories();
	Logger::Log(ModLoaderCategory, Verbosity::Verbose, "Outputting all mod directories");
	for(const string& modDirectory : GetAllModDirectories())
	{
		Logger::Log(ModLoaderCategory, Verbosity::Verbose, modDirectory);
		Mod currentMod(modDirectory);
	}
}

std::vector<std::string> ModLoader::GetAllModDirectories()
{
	Logger::Log(ModLoaderCategory, Verbosity::VeryVerbose, __FUNCTION__);

	std::vector<string> modDirectories;
	
	std::queue<string> directoriesToSearch;
	directoriesToSearch.push(GetModdingDirectory());

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
