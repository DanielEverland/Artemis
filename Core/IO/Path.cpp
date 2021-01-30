#include "Path.h"
#include <Core.h>

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
    const size_t last_slash_idx = fullPath.find_last_of("\\/");
    if (std::string::npos == last_slash_idx)
    {
        throw ArgumentException("No deliminators present in path \"" + fullPath + "\"");
    }
	
	return fullPath.erase(last_slash_idx + 1, fullPath.length());
}
