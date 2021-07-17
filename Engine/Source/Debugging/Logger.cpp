#include <string>
#include <iostream>
#include <windows.h>
#include <format>
#include <codecvt>

#include "Logger.h"
#include "Verbosity.h"
#include "../Config/GameConfiguration.h"
#include "Core/StringUtility.h"
#include "Exception/ArgumentException.h"
#include <debugapi.h>

using namespace ArtemisEngine;
using namespace std;

map<string, Verbosity> Logger::CachedCategoryVerbosities = { };
string Logger::ConfigurationSectionName = "Logging";
Verbosity Logger::GlobalVerbosity = Verbosity::Log;
bool Logger::HasLoadedGlobalVerbosity = false;

map<string, Verbosity> Logger::FromStringLookup =
{
	{ "VeryVerbose", Verbosity::VeryVerbose },
	{ "Verbose", Verbosity::Verbose },
	{ "Log", Verbosity::Log },
	{ "Warning", Verbosity::Warning },
	{ "Error", Verbosity::Error },
	{ "Fatal", Verbosity::Fatal }
};

void Logger::LogMessage(const string& category, const Verbosity& verbosity, const string& message)
{
	if (MoreOrEquallyVerbose(verbosity, GetMinimumVerbosity(category)))
	{
		const string formattedMessage = std::format("{}: {}: {}\n", category, VerbosityToString(verbosity), message);
		std::cout << formattedMessage;
		
		OutputDebugString(StringUtility::ConvertUtf8ToWide(formattedMessage).c_str());
	}
}

string Logger::VerbosityToString(const Verbosity& verbosity)
{
	switch (verbosity)
	{
	case Verbosity::Error:
		return "Error";
	case Verbosity::Fatal:
		return "Fatal";
	case Verbosity::Log:
		return "Log";
	case Verbosity::Verbose:
		return "Verbose";
	case Verbosity::VeryVerbose:
		return "VeryVerbose";
	case Verbosity::Warning:
		return "Warning";
	default:
		throw ArgumentException("Couldn't convert verbosity to string");
	}
}

Verbosity Logger::ParseVerbosity(const string& verbosityString)
{
	Verbosity temp;
	if (TryParseVerbosity(verbosityString, temp))
		return temp;

	throw ArgumentException(std::format("Could not convert {} to Verbosity enum", verbosityString));
}

bool Logger::TryParseVerbosity(string verbosityString, Verbosity& outValue)
{
	StringUtility::Trim(verbosityString);

	for (const auto& [lookupString, lookupEnum] : FromStringLookup)
	{
		if (IsEqual(lookupString, verbosityString))
		{
			outValue = lookupEnum;
			return true;
		}
	}

	return false;
}

Verbosity Logger::GetGlobalVerbosity()
{
	if (!HasLoadedGlobalVerbosity)
	{
		HasLoadedGlobalVerbosity = true;
		GlobalVerbosity = GetMinimumVerbosity("Global");
	}

	return GlobalVerbosity;
}

Verbosity Logger::GetMinimumVerbosity(const string& category)
{
	if (!CachedCategoryVerbosities.contains(category))
		LoadMinimumVerbosity(category);

	return CachedCategoryVerbosities[category];
}

void Logger::LoadMinimumVerbosity(const string& category)
{
	const string verbosityString = GameConfiguration::GetReader().Get<string>(ConfigurationSectionName, category, "Log");
	const Verbosity verbosityEnum = ParseVerbosity(verbosityString);
	CachedCategoryVerbosities.insert(CachedCategoryVerbosities.begin(), std::pair<string, Verbosity>(category, verbosityEnum));
}

bool Logger::IsEqual(const string& verbosityString, const string& comparer)
{
	return verbosityString == comparer;
}

bool Logger::MoreOrEquallyVerbose(const Verbosity& a, const Verbosity& b)
{
	return static_cast<int>(a) >= static_cast<int>(b) || static_cast<int>(a) >= static_cast<int>(GetGlobalVerbosity());
}