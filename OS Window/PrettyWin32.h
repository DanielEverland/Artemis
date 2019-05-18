#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

// Handles
#define WindowHandle HWND
#define DisplayDeviceHandle HDC

#define UnicodeChar WCHAR
#define HandleInstance HINSTANCE
#define WindowClass WNDCLASS
#define DefaultWindowOptions WS_OVERLAPPEDWINDOW
#define DefaultXPosition CW_USEDEFAULT
#define DefaultYPosition CW_USEDEFAULT
#define DefaultWidth CW_USEDEFAULT
#define DefaultHeight CW_USEDEFAULT
#define Message MSG
#define Brush HBRUSH