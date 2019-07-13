#pragma once

#include <string>

using std::string;

class Output
{
public:
	static void Log(const char* const text);
	static void Log(const string text);

private:
	static void LogToVS(const char* const text);
};