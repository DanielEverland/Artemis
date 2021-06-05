#include "Path.h"

#include <Shlwapi.h>

#include "Core.h"
#include "Exception/ArgumentException.h"

using namespace ArtemisEngine;

string Path::GetFileName(string fullPath)
{
    const size_t last_slash_idx = fullPath.find_last_of("\\/");

	Assert(std::string::npos != last_slash_idx, ArgumentException("No deliminators present in path \"" + fullPath + "\""))

    return fullPath.erase(0, last_slash_idx + 1);
}

string Path::GetFileNameWithoutExtension(const string& fullPath)
{
    string fileName = GetFileName(fullPath);

    const size_t period_idx = fileName.rfind('.');
    Assert(std::string::npos != period_idx, ArgumentException("No extension deliminator dot (.) present in path \"" + fullPath + "\""))

    return fileName.erase(period_idx);
}

string Path::RemoveLastDeliminatorPart(string fullPath)
{
    const char finalChar = fullPath.at(fullPath.length() - 1);
    if (finalChar == '/' || finalChar == '\\')
    {
        fullPath = fullPath.substr(0, fullPath.length() - 1);
    }

    const size_t last_slash_idx = fullPath.find_last_of("\\/");
    Assert(std::string::npos != last_slash_idx, ArgumentException("No deliminators present in path \"" + fullPath + "\""))

    string toReturn = fullPath.erase(last_slash_idx + 1, fullPath.length());
    return toReturn;
}

string Path::GetFileNameExtension(const string& fullPath)
{
    const size_t last_slash_idx = fullPath.find_last_of("\\/");
    Assert(std::string::npos != last_slash_idx, ArgumentException("No deliminators present in path \"" + fullPath + "\""))
	
    const size_t last_dot_idx = fullPath.find_last_of('.');
    Assert(std::string::npos != last_dot_idx, ArgumentException("No extension deliminator present in path \"" + fullPath + "\""))

    return fullPath.substr(last_dot_idx, fullPath.length());
}

string Path::GetRelativeProjectPath(const string& fullPath)
{
    Assert(IsSubDirectory(fullPath, GetProjectPath()), ArgumentException("Path \"" + fullPath + "\" is not a subdirectory of project directory \"" + GetProjectPath() + "\""))

    const size_t projectPathLength = GetProjectPath().length();
    return fullPath.substr(projectPathLength, fullPath.length() - projectPathLength);
}

string Path::GetRelativeModPath(const string& fullPath)
{
    const string modDirectory = GetProjectPath() + "\\Mods";

    Assert(IsSubDirectory(fullPath, GetProjectPath()), ArgumentException("Path \"" + fullPath + "\" is not a subdirectory of project directory \"" + modDirectory + "\""))

    const size_t modPathLength = modDirectory.length() + 1;
    return fullPath.substr(modPathLength, fullPath.length() - modPathLength);
}

bool Path::IsSubDirectory(const string& a, const string& b)
{
    return a.find_last_of("\\/") > b.find_last_of("\\/");
}

string Path::GetProjectPath()
{
    char fileName[255];
    GetModuleFileNameA(nullptr, fileName, sizeof(fileName));
    return RemoveLastDeliminatorPart(fileName);
}