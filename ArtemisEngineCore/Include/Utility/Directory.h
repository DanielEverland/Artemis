#pragma once

#include <functional>
#include <list>

using std::string;
using std::list;

namespace ArtemisEngine
{
	class Directory
	{
	public:
		
		/* Returns a list of all the files in a given directory that matches an extension */
		static list<string> GetAllFilesWithExtension(string& directory, string extension);
		
		/* Returns a list of all the files in a given directory */
		static list<string> GetAllFiles(string& directory);

		/* Iterates over a directory using a lambda or functor */
		static void IterateDirectory(string& directory, std::function<void(string&)> func);

		/* Returns path to compiled shaders */
		static string GetShaderDirectory();

		/* Returns path to the root directory */
		static string GetRoot();

		/* Returns path to the executable file */
		static string GetExecutablePath();

		/// <summary>Returns whether the given filepath has a certain extension</summary>
		/// <param name="filePath">Full path to file</param>
		/// <param name="extension">Must include dot - i.e. ".txt"</param>
		/// <returns>Whether file has extension</returns>
		static bool HasExtension(const string& filePath, const string& extension);

	private:
		static const int BufferLength;
		static char* Buffer;
	};
}
