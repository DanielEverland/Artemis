#include <queue>

#include <iostream>

#include "ModLoader.h"
#include <IO/Directory.h>
#include <IO/Path.h>

string ModLoader::ModInfoName = "modinfo.lua";

string ModLoader::GetModdingDirectory()
{
	return Directory::GetProjectDirectory() + "\Mods";
}

void ModLoader::LoadMods()
{
	std::cout << "outputting all mod directories" << std::endl;
	for(const string& modDirectory : GetAllModDirectories())
	{
		std::cout << modDirectory << std::endl;
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
