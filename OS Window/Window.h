#pragma once

#include "PrettyWin32.h"

class Window
{
public:

	Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState);

	const UnicodeChar* Title = L"Window Title";
	UnicodeChar* Arguments;
	int WindowBehaviour = 0;
	Brush BackgroundBrush = (Brush)(COLOR_WINDOW + 1);

	void Create();

private:
	
	HandleInstance handleInstance;
	WindowHandle windowHandle;
	const UnicodeChar* className;
	int windowState;

	static LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);

	void OnClose();
	void OnPaint(WindowHandle windowHandle);
	void RunMessageLoop();
	WindowHandle CreateWindowHandle(HandleInstance handleInstance);
	WindowClass CreateWindowClass(HandleInstance handleInstance);
	LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
};
