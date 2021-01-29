#pragma once

#include <string>

using std::string;

class Path
{
public:
	static string GetFileName(string fullPath);
	static string GetFileNameWithoutExtension(const string& fullPath);
	static string RemoveLastDeliminatorPart(string fullPath);
};
