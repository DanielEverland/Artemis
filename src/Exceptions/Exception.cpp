#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <typeinfo>

#include <stdexcept>
#include <DbgHelp.h>

#include "Exceptions.h"

const unsigned long Exception::FramesToSkip = 2;
const unsigned long Exception::FramesToCapture = 25;
const unsigned long Exception::MaximumNameLength = 1024;
const unsigned long long Exception::SymbolBufferSize = (sizeof(SYMBOL_INFO) + MaximumNameLength + sizeof(ULONG64) - 1) / sizeof(ULONG64);
HANDLE Exception::processHandle = {};

bool Exception::InitializeSymbols()
{
	processHandle = GetCurrentProcess();
	return SymInitialize(processHandle, NULL, TRUE);
}

void Exception::CreateStacktrace()
{
	stackTrace = "";

	IMAGEHLP_LINE line = CreateFileLineStruct();
	void* frames[FramesToCapture] = { };

	unsigned short framesCount = CaptureStackBackTrace(FramesToSkip, FramesToCapture, frames, nullptr);

	for (unsigned short i = 0; i < framesCount; i++)
	{
		ULONG64 buffer[SymbolBufferSize] = { };
		SYMBOL_INFO* info = CreateInfoPointer(buffer);

		DWORD64 displacement = 0;
		if (TryGetSymbolInfo(frames[i], &displacement, info))
		{
			if (TryGetFileInfo(frames[i], &displacement, &line))
			{
				AppendFrameWithFileData(info, &line);
			}
			else
			{
				AppendFrame(info);
			}
		}
		else
		{
			DWORD errorCode = GetLastError();
		}
	}
}

bool Exception::TryGetSymbolInfo(const void* const address, DWORD64* displacement, SYMBOL_INFO* info) const
{
	return SymFromAddr(processHandle, (DWORD64)address, displacement, info);
}

bool Exception::TryGetFileInfo(const void* const address, const DWORD64* displacement, IMAGEHLP_LINE* const linePointer) const
{
	return SymGetLineFromAddr(processHandle, DWORD64(address), PDWORD(&displacement), linePointer);
}

IMAGEHLP_LINE Exception::CreateFileLineStruct() const
{
	IMAGEHLP_LINE line = { };
	line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

	return line;
}

SYMBOL_INFO* Exception::CreateInfoPointer(ULONG64* buffer) const
{
	SYMBOL_INFO* info = (SYMBOL_INFO*)buffer;
	info->SizeOfStruct = sizeof(SYMBOL_INFO);
	info->MaxNameLen = MaximumNameLength;

	return info;
}

void Exception::AppendFrame(const SYMBOL_INFO* const info)
{
	stackTrace.append(info->Name);
	stackTrace.append("()\n");
}

void Exception::AppendFrameWithFileData(const SYMBOL_INFO* const info, const IMAGEHLP_LINE* const line)
{
	string prettyFileName = GetPrettyFileName(line->FileName);

	stackTrace.append(prettyFileName);
	stackTrace.append(":::");
	stackTrace.append(info->Name);
	stackTrace.append("(");
	stackTrace.append(std::to_string(line->LineNumber));
	stackTrace.append(")\n");
}

string Exception::GetPrettyFileName(const char* fileName) const
{
	string str(fileName);
	size_t lastIndex = str.find_last_of("\\");
	return str.substr(lastIndex + 1);
}

const string Exception::GetTypeName() const
{
	string name = typeid(*this).name();

	int index = 0;
	while (name[index] != ' ')
		index++;

	name = name.substr(index + 1);

	return name;
}