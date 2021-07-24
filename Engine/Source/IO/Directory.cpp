#include "Directory.h"

#include <Shlwapi.h>
#include <filesystem>

#include "Path.h"

using namespace ArtemisEngine;
using namespace std::filesystem;

string Directory::GetProjectDirectory()
{
	char rawPathName[MAX_PATH];
	GetModuleFileNameA(nullptr, rawPathName, MAX_PATH);

	return Path::RemoveLastDeliminatorPart(std::string(rawPathName));
}

vector<string> Directory::GetAllFiles(const string& directory)
{
	std::vector<string> allFilePaths;
	for (const auto& entry : directory_iterator(directory))
	{
		if (entry.is_regular_file())
			allFilePaths.emplace_back(entry.path().string());
	}

	return allFilePaths;
}

vector<string> Directory::GetAllDirectories(const string& directory)
{
	std::vector<string> allDirectories;
	for (const auto& entry : directory_iterator(directory))
	{
		if (entry.is_directory())
			allDirectories.emplace_back(entry.path().string());
	}

	return allDirectories;
}

bool Directory::Exists(const string& directory)
{
	return is_directory(directory);
}
