#pragma once

#include <string>
#include <vector>

using std::string;

class ModLoader
{
public:
	static string GetModdingDirectory();
	
	static void LoadMods();
	static std::vector<string> GetAllModDirectories();

private:
	static bool GetModInfoFilePath(const string& directory, string& modFilePath);
};
