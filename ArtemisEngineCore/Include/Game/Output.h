#pragma once

#include <string>

#include "Include/Game/IDebugStringReturner.h"
#include "Include/Exceptions/Exception.h"

using std::string;

namespace ArtemisEngine
{
	class Output
	{
	public:
		static void Space();

		static void LogException(const Exception& e);
		static void LogError(const IDebugStringReturner& stringReturner);
		static void LogError(const string& text);
		static void LogError(const wchar_t* text);
		static void LogWarning(const IDebugStringReturner& stringReturner);
		static void LogWarning(const string& text);
		static void LogWarning(const wchar_t* text);

		static void Log(const IDebugStringReturner& stringReturner);
		static void Log(unsigned int value);
		static void Log(unsigned short value);
		static void Log(long long value);
		static void Log(unsigned long long value);
		static void Log(double value);
		static void Log(const string& text);
		static void Log(const wchar_t* text);

		static void LogSameLine(unsigned int value);
		static void LogSameLine(unsigned short value);
		static void LogSameLine(long long value);
		static void LogSameLine(unsigned long long value);
		static void LogSameLine(double value);
		static void LogSameLine(const string& text);
		static void LogSameLine(const wchar_t* text);

	private:
		static void LogLineToVS(const string& text);
		static void LogLineToVS(const wchar_t* text);
		static void LogToVS(const string& text);
		static void LogToVS(const wchar_t* text);
	};
}