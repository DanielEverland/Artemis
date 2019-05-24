#pragma once

#include "Window.h"
#include "PrettyWin32.h"

LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
Window* GetInstancePointer(WindowHandle handle, UINT messageCode, LONG_PTR lParam);
Window* CreateStateInformation(WindowHandle handle, LONG_PTR lParam);
void SetStateInformation(Window* instancePointer, WindowHandle handle);
LONG_PTR GetStateInformation(WindowHandle handle);