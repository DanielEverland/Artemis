#include <string>
#include <iostream>

#include <Exceptions/ArgumentException.h>

#include "Logger.h"
#include "Verbosity.h"

void Logger::Log(const string& category, const Verbosity& verbosity, const string& message)
{
	std::cout << category << ": " << VerbosityToString(verbosity) << ": " << message << std::endl;
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
