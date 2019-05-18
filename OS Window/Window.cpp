#include "PrettyWin32.h"
#include "Window.h"

Window::Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState)
{
	this->handleInstance = handleInstance;
	this->className = className;
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
	Message message;
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
		this
	);

	if (handle == NULL)
		return 0;

	return handle;
}
WindowClass Window::CreateWindowClass(HandleInstance handleInstance)
{
	WindowClass windowClass = { };

	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.hInstance = handleInstance;
	windowClass.lpszClassName = className;

	return windowClass;
}
LONG_PTR Window::HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	switch (messageCode)
	{
	case WM_DESTROY:
		OnClose();
		return 0;

	case WM_PAINT:
		OnPaint(windowHandle);
		return 0;
	}

	return DefWindowProc(windowHandle, messageCode, wParam, lParam);
}
void Window::OnClose()
{
	PostQuitMessage(0);
}
void Window::OnPaint(WindowHandle windowHandle)
{
	PAINTSTRUCT paintData;
	DisplayDeviceHandle handleDisplayDevice = BeginPaint(windowHandle, &paintData);
	{
		FillRect(handleDisplayDevice, &paintData.rcPaint, (Brush)(COLOR_WINDOW + 1));
	}
	EndPaint(windowHandle, &paintData);
}

LONG_PTR CALLBACK Window::WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	Window* instancePointer = NULL;

	if (messageCode == WM_NCCREATE)
	{
		CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
		instancePointer = (Window*)createStruct->lpCreateParams;
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)instancePointer);

		instancePointer->windowHandle = handle;
	}
	else
	{
		instancePointer = (Window*)GetWindowLongPtr(handle, GWLP_USERDATA);
	}

	if (instancePointer)
	{
		return instancePointer->HandleMessage(messageCode, wParam, lParam);
	}
	else
	{
		return DefWindowProc(handle, messageCode, wParam, lParam);
	}
}