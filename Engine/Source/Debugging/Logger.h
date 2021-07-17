#pragma once

#include <string>
#include <map>
#include <Debugging/Verbosity.h>

using std::map;
using std::string;

namespace ArtemisEngine
{	
	class Logger
	{
	public:
		static void LogMessage(const string& category, const Verbosity& verbosity, const string& message);
		static string VerbosityToString(const Verbosity& verbosity);
		static Verbosity ParseVerbosity(const string& verbosityString);
		static bool TryParseVerbosity(string verbosityString, Verbosity& outValue);

	private:
		static Verbosity GlobalVerbosity;
		static bool HasLoadedGlobalVerbosity;
		static string ConfigurationSectionName;
		static map<string, Verbosity> FromStringLookup;
		static map<string, Verbosity> CachedCategoryVerbosities;

		static Verbosity GetGlobalVerbosity();
		static Verbosity GetMinimumVerbosity(const string& category);
		static void LoadMinimumVerbosity(const string& category);
		static bool IsEqual(const string& verbosityString, const string& comparer);

		// Returns true if a is more or equally verbose than b
		static bool MoreOrEquallyVerbose(const Verbosity& a, const Verbosity& b);
	};

#define DefineLogCategory(Category, CompileTimeVerbosity) \
	constexpr Verbosity CompileTimeVerbosity_##Category = CompileTimeVerbosity;

#define Log(Category, Verbosity, Message) \
	if constexpr(static_cast<int>(CompileTimeVerbosity_##Category) <= static_cast<int>(Verbosity)) { Logger::LogMessage(#Category, Verbosity, Message); }

#define FuncName __FUNCTION__
}
