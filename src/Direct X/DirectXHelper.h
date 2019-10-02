#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "..\\Exceptions\DirectXException.h"

void ThrowIfFailed(HRESULT result, const char* message = "Win32 routine failed")
{
	if (FAILED(result))
	{
		throw DirectXException(message);
	}
}