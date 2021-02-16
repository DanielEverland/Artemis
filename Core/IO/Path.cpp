#include "Path.h"

#include "../Exceptions/ArgumentException.h"

string Path::GetFileName(string fullPath)
{
    const size_t last_slash_idx = fullPath.find_last_of("\\/");
    if (std::string::npos == last_slash_idx)
    {
        throw ArgumentException("No deliminators present in path \"" + fullPath + "\"");
    }

	return fullPath.erase(0, last_slash_idx + 1);
}

string Path::GetFileNameWithoutExtension(const string& fullPath)
{
	string fileName = GetFileName(fullPath);
	
    const size_t period_idx = fileName.rfind('.');
    if (std::string::npos == period_idx)
    {
        throw ArgumentException("No extension deliminator dot (.) present in path \"" + fullPath + "\"");
    }

	return fileName.erase(period_idx);
}

string Path::RemoveLastDeliminatorPart(string fullPath)
{
	const char finalChar = fullPath.at(fullPath.length() - 1);
	if(finalChar == '/' || finalChar == '\\')
	{
		fullPath = fullPath.substr(0, fullPath.length() - 1);
	}
	
    const size_t last_slash_idx = fullPath.find_last_of("\\/");
    if (std::string::npos == last_slash_idx)
    {
        throw ArgumentException("No deliminators present in path \"" + fullPath + "\"");
    }

	string toReturn = fullPath.erase(last_slash_idx + 1, fullPath.length());
	return toReturn;
}

string Path::GetFileNameExtension(const string& fullPath)
{
    const size_t last_slash_idx = fullPath.find_last_of('.');
    if (std::string::npos == last_slash_idx)
    {
        throw ArgumentException("No extension deliminator present in path \"" + fullPath + "\"");
    }

    return fullPath.substr(last_slash_idx, fullPath.length());
}

string Path::GetRelativeProjectPath(const string& fullPath)
{
	if(!IsSubDirectory(fullPath, GetProjectPath()))
		throw ArgumentException("Path \"" + fullPath + "\" is not a subdirectory of project directory \"" + GetProjectPath() + "\"");

	const size_t projectPathLength = GetProjectPath().length();
	return fullPath.substr(projectPathLength, fullPath.length() - projectPathLength);
}

string Path::GetRelativeModPath(const string& fullPath)
{
	const string modDirectory = GetProjectPath() + "\\Mods";
	
    if (!IsSubDirectory(fullPath, GetProjectPath()))
        throw ArgumentException("Path \"" + fullPath + "\" is not a subdirectory of project directory \"" + modDirectory + "\"");

    const size_t modPathLength = modDirectory.length();
    return fullPath.substr(modPathLength, fullPath.length() - modPathLength);
}

bool Path::IsSubDirectory(const string& a, const string& b)
{
	return b.rfind(a, 0);
}

string Path::GetProjectPath()
{
	char fileName[255];
	GetModuleFileNameA(nullptr, fileName, sizeof(fileName));
	return RemoveLastDeliminatorPart(fileName);
}
