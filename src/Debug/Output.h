#pragma once

#include <string>

#include "..\\Exceptions\Exceptions.h"

using std::string;

class Output
{
public:
	static void Space();

	static void LogException(const Exception& e);
	static void LogError(const string& text);
	static void LogWarning(const string& text);

	static void LogLine(unsigned int value);
	static void LogLine(unsigned short value);
	static void LogLine(long long value);
	static void LogLine(unsigned long long value);
	static void LogLine(double value);
	static void LogLine(const string& text);

	static void Log(unsigned int value);
	static void Log(unsigned short value);
	static void Log(long long value);
	static void Log(unsigned long long value);
	static void Log(double value);
	static void Log(const string& text);

private:
	static void LogLineToVS(const string& text);
	static void LogToVS(const string& text);
};