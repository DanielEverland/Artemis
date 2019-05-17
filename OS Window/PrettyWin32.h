#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

namespace Windows
{
#define UnicodeChar WCHAR
#define HandleInstance HINSTANCE
#define WindowClass WNDCLASS
#define WindowHandle HWND
#define DefaultWindowOptions WS_OVERLAPPEDWINDOW
#define DefaultXPosition CW_USEDEFAULT
#define DefaultYPosition CW_USEDEFAULT
#define DefaultWidth CW_USEDEFAULT
#define DefaultHeight CW_USEDEFAULT
#define Message MSG
}