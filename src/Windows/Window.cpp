#ifndef UNICODE
#define UNICODE
#endif

#include "WindowProcedure.h"
#include "Window.h"

namespace ArtemisWindow
{
	Window::Window(HINSTANCE handleInstance, const LPCWSTR className, int windowState)
	{
		this->handleInstance = handleInstance;
		this->className = className;
		this->windowState = windowState;
		this->windowHandle = NULL;
	}

	void Window::Show()
	{
		WNDCLASS windowClass = CreateWindowClass();
		RegisterClass(&windowClass);

		HWND windowHandle = CreateWindowHandle();
		ShowWindow(windowHandle, windowState);

		RunMessageLoop();
	}
	void Window::RunMessageLoop() const
	{
		MSG message;
		while (GetMessage(&message, NULL, 0, 0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	HWND Window::CreateWindowHandle()
	{
		HWND handle = CreateWindowEx(
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
	WNDCLASS Window::CreateWindowClass() const
	{
		WNDCLASS windowClass = { };

		windowClass.lpfnWndProc = WindowProcedure;
		windowClass.hInstance = handleInstance;
		windowClass.lpszClassName = className;

		return windowClass;
	}

	//-------------------------------------------------------------------------------------------------------------
	//------------------------------------------MESSAGE HANDLER----------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------
	LONG_PTR Window::HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
	{
		switch (messageCode)
		{
		case WM_DESTROY:
			return OnClose();

		case WM_PAINT:
			return OnPaint();
		}

		return DefWindowProc(windowHandle, messageCode, wParam, lParam);
	}


	//-------------------------------------------------------------------------------------------------------------
	//---------------------------------------MESSAGE IMPLEMENTATIONS-----------------------------------------------
	//-------------------------------------------------------------------------------------------------------------
	LONG_PTR Window::OnClose()
	{
		PostQuitMessage(0);
		return 0;
	}
	LONG_PTR Window::OnPaint()
	{
		PAINTSTRUCT paintData;
		HDC handleDisplayDevice = BeginPaint(windowHandle, &paintData);
		{
			FillRect(handleDisplayDevice, &paintData.rcPaint, BackgroundColor);
		}
		EndPaint(windowHandle, &paintData);

		return 0;
	}
}