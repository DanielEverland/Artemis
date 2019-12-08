#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <atlstr.h>

#include "Exceptions/DirectXException.h"
#include "Debugging/Output.h"

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
	Output::Log(text);
}
inline void DirectXLogWarning(const string& text)
{
	Output::LogWarning("DirectX: " + text);
}
inline void DirectXLogWarning(const wchar_t* text)
{
	Output::LogWarning("DirectX: ");
	Output::Log(text);
}
inline void DirectXLogLine(const string& text)
{
	Output::LogLine("DirectX: " + text);
}
inline void DirectXLogLine(const wchar_t* text)
{
	Output::Log("DirectX: ");
	Output::LogLine(text);
}
inline void DirectXLog(const string& text)
{
	Output::Log("DirectX: " + text);
}
inline void DirectXLog(const wchar_t* text)
{
	Output::Log("DirectX: ");
	Output::Log(text);
}