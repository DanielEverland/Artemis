#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "..\\Exceptions\Exceptions.h"

void ThrowIfFailed(HRESULT result)
{
	ThrowIfFailed(result, "Win32 routine failed");
}
void ThrowIfFailed(HRESULT result, const string message)
{
	if (FAILED(result))
	{
		throw DirectXException(message);
	}
}