#pragma once

#include <string>
#include <filesystem>

using std::string;
using std::filesystem::recursive_directory_iterator;

typedef recursive_directory_iterator RecursiveDirectoryIterator;

namespace ArtemisEngine
{
	class Path
	{
	public:
		static string GetFileName(string fullPath);
		static string GetFileNameWithoutExtension(const string& fullPath);
		static string GetFullPathWithoutExtension(string fullPath);
		static string RemoveLastDeliminatorPart(string fullPath);
		static string GetFileNameExtension(const string& fullPath);
		static string GetRelativeProjectPath(const string& fullPath);
		static string GetRelativeModPath(const string& fullPath);

		// Returns true if a is a subdirectory of b
		static bool IsSubDirectory(const string& a, const string& b);
		static string GetProjectPath();
		static string GetRelativePath(const string& fullPath, const string& toRemove);

		// Wrappers for filesystem
		static RecursiveDirectoryIterator GetRecursiveIterator(const string& directory);
	};
}