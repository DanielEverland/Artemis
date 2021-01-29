#pragma once

#include <string>
#include <vector>

using std::string;

class Directory
{
public:
	static string GetProjectDirectory();
	static std::vector<string> GetAllFiles(const string& directory);
	static std::vector<string> GetAllDirectories(const string& directory);
};