#pragma once

class Window
{
public:

	Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState, WNDPROC procedureCallback);

	const UnicodeChar* Title = L"Window Title";
	UnicodeChar* Arguments;
	int WindowBehaviour = 0;

	void Create();

private:
	
	HandleInstance handleInstance;
	const UnicodeChar* className;
	WNDPROC procedureCallback;
	int windowState;

	void RunMessageLoop();
	WindowHandle CreateWindowHandle(HandleInstance handleInstance);
	WindowClass CreateWindowClass(HandleInstance handleInstance);
	
};

LONG_PTR CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, UINT_PTR wParam, LONG_PTR lParam);
