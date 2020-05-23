#pragma once

using std::string;

namespace ArtemisEngine::IO
{
	class Path
	{
	public:
		static string GetFilenameWithoutExtension(const string& path);
	};
}
