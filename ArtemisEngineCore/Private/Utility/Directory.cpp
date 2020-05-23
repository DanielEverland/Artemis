#include <string>
#include <Windows.h>
#include <filesystem>

#include "Public/Utility/Directory.h"

#include "Public/Game/Output.h"

using std::filesystem::directory_iterator;
using std::string;

using namespace ArtemisEngine;

const int Directory::BufferLength = 512;
char* Directory::Buffer = new char[BufferLength];

list<string> Directory::GetAllFilesWithExtension(const string& directory, const string& extension)
{
	list<string> allFiles;

	IterateDirectory(directory, [&allFiles, extension](string& currentPath) -> void
	{
		if (HasExtension(currentPath, extension))
		{
			allFiles.push_back(currentPath);
		}
	});

	return allFiles;
}

list<string> Directory::GetAllFiles(const string& directory)
{
	list<string> allFiles;

	IterateDirectory(directory, [&allFiles](string& currentPath) -> void
	{
		allFiles.push_back(currentPath);
	});
	
	return allFiles;
}

void Directory::IterateDirectory(const string& directory, std::function<void(string&)> func)
{
	directory_iterator iterator(directory);
	for (auto& entry : iterator)
	{
		string currentPath = entry.path().string();
		func(currentPath);
	}
}

string Directory::GetShaderDirectory()
{
	string path = GetRoot();
	path.append("Shaders\\");

	return path;
}

string Directory::GetRoot()
{
	const string executablePath = GetExecutablePath();
	const int lastBackslashIndex = executablePath.find_last_of('\\');

	return executablePath.substr(0, lastBackslashIndex + 1);
}

string Directory::GetExecutablePath()
{
	GetModuleFileNameA(nullptr, Buffer, BufferLength);
	return string(Buffer);
}

bool Directory::HasExtension(const string& filePath, const string& extension)
{
	const string actualExtension = filePath.substr(filePath.find_last_of('.'));
	return extension == actualExtension;
}