#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

// Handles
typedef HWND WindowHandle;
typedef HDC DisplayDeviceHandle;
typedef HINSTANCE HandleInstance;

typedef WCHAR UnicodeChar;
typedef WNDCLASS WindowClass;
typedef MSG Message;
typedef HBRUSH Brush;