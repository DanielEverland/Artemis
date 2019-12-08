#pragma once

#include "Window.h"

namespace ArtemisWindow
{
	LONG_PTR CALLBACK WindowProcedure(HWND handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
	Window* GetInstancePointer(HWND handle, UINT messageCode, LONG_PTR lParam);
	Window* CreateStateInformation(HWND handle, LONG_PTR lParam);
	void SetStateInformation(Window* instancePointer, HWND handle);
	LONG_PTR GetStateInformation(HWND handle);
}