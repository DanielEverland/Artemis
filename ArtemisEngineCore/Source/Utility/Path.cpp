#include <string>

#include "Include/Utility/Path.h"
#include "Include/Exceptions/OutOfRangeException.h"

using namespace ArtemisEngine::IO;
using std::string;

string Path::GetFilenameWithoutExtension(const string& path)
{
	const int lastPathDeliminator = path.find_last_of('\\');
	const int firstExtensionDeliminator = path.find_first_of('.');

	const int begin = lastPathDeliminator;
	const int count = firstExtensionDeliminator - lastPathDeliminator;

	if(begin < 0 || begin >= path.length() || count < 0 || count >= path.length())
		throw OutOfRangeException("Substring index is out of range! begin = " + std::to_string(begin) + ", count = " + std::to_string(count) + ", path length = " + std::to_string(path.length()));

	string finalPath = path.substr(begin + 1, count - 1);
	
	return finalPath;
}