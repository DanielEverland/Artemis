#pragma once

#include "PrettyWin32.h"

class Window
{
public:

	Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState);

	const UnicodeChar* Title = L"Window Title";
	int WindowBehaviour = 0;
	Brush BackgroundBrush = (Brush)(COLOR_WINDOW + 1);

	void Create();

private:
	
	HandleInstance handleInstance;
	WindowHandle windowHandle;
	const UnicodeChar* className;
	int windowState;


	void RunMessageLoop();
	WindowHandle CreateWindowHandle(HandleInstance handleInstance);
	WindowClass CreateWindowClass(HandleInstance handleInstance);
	LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);

	// Messages
	LONG_PTR OnClose();
	LONG_PTR OnPaint();	

	// Window Procedure
	static LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
	static Window* CreateStateInformation(WindowHandle handle, LONG_PTR lParam);
	static void SetStateInformation(Window * instancePointer, WindowHandle handle);
	static LONG_PTR GetStateInformation(WindowHandle handle);
	static Window* GetInstancePointer(WindowHandle handle, UINT messageCode, LONG_PTR lParam);
};
