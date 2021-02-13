#pragma once

#include <string>

using std::string;

class Path
{
public:
	static string GetFileName(string fullPath);
	static string GetFileNameWithoutExtension(const string& fullPath);
	static string RemoveLastDeliminatorPart(string fullPath);
	static string GetFileNameExtension(const string& fullPath);
	static string GetRelativeProjectPath(const string& fullPath);
	static string GetRelativeModPath(const string& fullPath);

	// Returns true if a is a subdirectory of b
	static bool IsSubDirectory(const string& a, const string& b);
	static string GetProjectPath();
};
