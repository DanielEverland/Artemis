#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <atlstr.h>

#include "Include/Exceptions/DirectXException.h"
#include "Include/Game/Output.h"

using namespace ArtemisEngine;

inline void ThrowIfFailed(HRESULT result)
{
	if (FAILED(result))
	{
		CString hexString;
		hexString.Format("%X", result);
		
		throw DirectXException("Win32 failed with code " + std::to_string(result) + " (0x" + hexString.GetString() + ")");
	}
}
inline void ThrowIfFailed(HRESULT result, string message)
{
	if (FAILED(result))
	{
		throw DirectXException(message);
	}
}

// Output
inline void DirectXLogError(const string& text)
{
	Output::LogError("DirectX: " + text);
}
inline void DirectXLogError(const wchar_t* text)
{
	Output::LogError("DirectX: ");
	Output::LogSameLine(text);
}
inline void DirectXLogWarning(const string& text)
{
	Output::LogWarning("DirectX: " + text);
}
inline void DirectXLogWarning(const wchar_t* text)
{
	Output::LogWarning("DirectX: ");
	Output::LogSameLine(text);
}
inline void DirectXLog(const string& text)
{
	Output::Log("DirectX: " + text);
}
inline void DirectXLog(const wchar_t* text)
{
	Output::LogSameLine("DirectX: ");
	Output::Log(text);
}
inline void DirectXLogSameLine(const string& text)
{
	Output::LogSameLine("DirectX: " + text);
}
inline void DirectXLogSameLine(const wchar_t* text)
{
	Output::LogSameLine("DirectX: ");
	Output::LogSameLine(text);
}