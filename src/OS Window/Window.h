#pragma once

#include "../Main/PrettyWin32.h"
#include "../Structs/Color.h"

class Window
{
public:

	const UnicodeChar* Title = L"Window Title";

	int WindowBehaviour = 0;
	Color BackgroundColor = Color::White;

	Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState);

	void Show();

private:
	
	const UnicodeChar* className;

	HandleInstance handleInstance;
	WindowHandle windowHandle;
	int windowState;
	
	void RunMessageLoop();
	WindowHandle CreateWindowHandle(HandleInstance handleInstance);
	WindowClass CreateWindowClass(HandleInstance handleInstance);
	LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);

	// Messages
	LONG_PTR OnClose();
	LONG_PTR OnPaint();

	friend LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
	friend Window* CreateStateInformation(WindowHandle handle, LONG_PTR lParam);
};
