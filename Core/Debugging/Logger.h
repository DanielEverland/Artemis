#pragma once

enum class Verbosity;

class Logger
{
public:
	static void Log(const string& category, const Verbosity& verbosity, const string& message);
	static string VerbosityToString(const Verbosity& verbosity);
};
