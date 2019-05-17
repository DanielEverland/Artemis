#include "PrettyWin32.h"
#include "Window.h"

Window::Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState, WNDPROC procedureCallback)
{
	this->handleInstance = handleInstance;
	this->className = className;
	this->procedureCallback = procedureCallback;
	this->windowState = windowState;
}

void Window::Create()
{
	WindowClass windowClass = CreateWindowClass(handleInstance);
	RegisterClass(&windowClass);

	WindowHandle windowHandle = CreateWindowHandle(handleInstance);
	ShowWindow(windowHandle, windowState);

	RunMessageLoop();
}
void Window::RunMessageLoop()
{
	Message message = { };
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}
WindowHandle Window::CreateWindowHandle(HandleInstance handleInstance)
{
	WindowHandle handle = CreateWindowEx(
		WindowBehaviour,
		className,
		Title,
		DefaultWindowOptions,

		// Size and position
		DefaultXPosition, DefaultYPosition, DefaultWidth, DefaultHeight,

		NULL,			// Parent window
		NULL,			// Menu
		handleInstance,
		NULL			// Additional application data
	);

	if (handle == NULL)
		return 0;

	return handle;
}
WindowClass Window::CreateWindowClass(HandleInstance handleInstance)
{
	WindowClass windowClass = { };

	windowClass.lpfnWndProc = procedureCallback;
	windowClass.hInstance = handleInstance;
	windowClass.lpszClassName = className;

	return windowClass;
}