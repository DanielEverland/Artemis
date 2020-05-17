#include <string>

#include "Include/Utility/Path.h"

using namespace ArtemisEngine::IO;
using std::string;

string Path::GetFilenameWithoutExtension(const string& path)
{
	const int lastPathDeliminator = path.find_last_of('//');
	const int firstExtensionDeliminator = path.find_first_of('.');

	const int begin = lastPathDeliminator;
	const int count = firstExtensionDeliminator - lastPathDeliminator;

	return path.substr(begin, count);
}