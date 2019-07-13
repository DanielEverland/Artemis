#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Output.h"

void Output::Log(const char* const text)
{
	LogToVS(text);
}

void Output::Log(const string text)
{
	Log(text.c_str());
}

void Output::LogToVS(const char* const text)
{
	OutputDebugString(text);
}