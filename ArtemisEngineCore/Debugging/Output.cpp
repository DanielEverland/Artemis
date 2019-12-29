#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <typeinfo>

#include "Output.h"

void Output::Space()
{
	Output::Log(" ");
}

void Output::LogException(const Exception& e)
{
	string str;
	str += "\n";

	str += e.GetTypeName();
	str += "(\"";
	str += e.GetMessage();
	str += "\"):";
	str += "\n";
	str += e.GetStackTrace();

	str += "\n";

	Output::Log(str);
}

void Output::LogError(const IDebugStringReturner& stringReturner)
{
	LogError(stringReturner.ToString());
}

void Output::LogError(const string& text)
{
	string errorText = "Error: " + string(text);
	LogLineToVS(errorText);
}

void Output::LogError(const wchar_t* text)
{
	LogToVS("Error: ");
	LogLineToVS(text);
}

void Output::LogWarning(const IDebugStringReturner& stringReturner)
{
	LogWarning(stringReturner.ToString());
}

void Output::LogWarning(const string& text)
{
	string warningText = "Warning: " + string(text);
	LogLineToVS(warningText);
}

void Output::LogWarning(const wchar_t* text)
{
	LogToVS("Warning: ");
	LogLineToVS(text);
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------LOG LINE-------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

void Output::Log(const IDebugStringReturner& stringReturner)
{
	Log(stringReturner.ToString());
}

void Output::Log(unsigned int value)
{
	LogLineToVS(std::to_string(value));
}

void Output::Log(unsigned short value)
{
	LogLineToVS(std::to_string(value));
}

void Output::Log(long long value)
{
	LogLineToVS(std::to_string(value));
}

void Output::Log(unsigned long long value)
{
	LogLineToVS(std::to_string(value));
}

void Output::Log(double value)
{
	LogLineToVS(std::to_string(value));
}

void Output::Log(const string& text)
{
	LogLineToVS(text);
}

void Output::Log(const wchar_t* text)
{
	LogLineToVS(text);
}

//-------------------------------------------------------------------------------------------------------------
//--------------------------------------------LOG-SAME-LINE----------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

void Output::LogSameLine(unsigned int value)
{
	LogToVS(std::to_string(value));
}

void Output::LogSameLine(unsigned short value)
{
	LogToVS(std::to_string(value));
}

void Output::LogSameLine(long long value)
{
	LogToVS(std::to_string(value));
}

void Output::LogSameLine(unsigned long long value)
{
	LogToVS(std::to_string(value));
}

void Output::LogSameLine(double value)
{
	LogToVS(std::to_string(value));
}

void Output::LogSameLine(const string& text)
{
	LogToVS(text);
}

void Output::LogSameLine(const wchar_t* text)
{
	LogToVS(text);
}

//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------ROOT---------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

void Output::LogToVS(const string& text)
{
	OutputDebugString(text.c_str());
}
void Output::LogToVS(const wchar_t* text)
{
	OutputDebugStringW(text);
}

void Output::LogLineToVS(const string& text)
{
	string newLineString = string(text) + "\n";
	OutputDebugString(newLineString.c_str());
}
void Output::LogLineToVS(const wchar_t* text)
{
	OutputDebugStringW(text);
	OutputDebugString("\n");
}