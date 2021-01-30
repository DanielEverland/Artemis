#include <string>
#include <iostream>

#include <boost/algorithm/string/predicate.hpp>

#include <Core.h>

#include <Exceptions/ArgumentException.h>

#include "Logger.h"
#include "Verbosity.h"

map<string, Verbosity> Logger::CachedCategoryVerbosities = { };
string Logger::ConfigurationSectionName = "Logging";

map<string, Verbosity> Logger::FromStringLookup =
{
	{ "VeryVerbose", Verbosity::VeryVerbose },
	{ "Verbose", Verbosity::Verbose },
	{ "Log", Verbosity::Log },
	{ "Warning", Verbosity::Warning },
	{ "Error", Verbosity::Error },
	{ "Fatal", Verbosity::Fatal }
};

void Logger::Log(const string& category, const Verbosity& verbosity, const string& message)
{
	const Verbosity minimumVerbosity = GetMinimumVerbosity(category);
	if(MoreOrEquallyVerbose(verbosity, minimumVerbosity))
	{
		std::cout << category << ": " << VerbosityToString(verbosity) << ": " << message << std::endl;
	}
}

string Logger::VerbosityToString(const Verbosity& verbosity)
{
	switch(verbosity)
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
	if(TryParseVerbosity(verbosityString, temp))
		return temp;

	throw ArgumentException("Could not convert " + verbosityString + " to Verbosity enum");
}

bool Logger::TryParseVerbosity(string verbosityString, Verbosity& outValue)
{
	trim(verbosityString);

	for (const auto& [verbosityString, verbosityEnum] : FromStringLookup)
	{
		if (IsEqual(verbosityString, verbosityString))
		{
			outValue = verbosityEnum;
			return true;
		}
	}

	return false;
}

Verbosity Logger::GetMinimumVerbosity(const string& category)
{
	if(!CachedCategoryVerbosities.contains(category))
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
	return boost::iequals(verbosityString, comparer);
}

bool Logger::MoreOrEquallyVerbose(const Verbosity& a, const Verbosity& b)
{
	return static_cast<int>(a) >= static_cast<int>(b);
}
