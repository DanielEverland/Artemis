#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace ArtemisEngine
{
	class Directory
	{
	public:
		static string GetProjectDirectory();
		static vector<string> GetAllFiles(const string& directory);
		static vector<string> GetAllDirectories(const string& directory);
		static bool Exists(const string& directory);
	};
}