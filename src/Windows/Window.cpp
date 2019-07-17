#ifndef UNICODE
#define UNICODE
#endif

#include "WindowProcedure.h"
#include "Window.h"

#include "..\\Debug\Output.h"

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
		CreateWindowClass();
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
	void Window::CreateWindowClass() const
	{
		WNDCLASS windowClass{ };

		windowClass.lpfnWndProc = WindowProcedure;
		windowClass.hInstance = handleInstance;
		windowClass.lpszClassName = className;

		RegisterClass(&windowClass);
	}

	//-------------------------------------------------------------------------------------------------------------
	//------------------------------------------MESSAGE HANDLER----------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------
	LONG_PTR Window::HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
	{
		switch (messageCode)
		{
		case WM_KILLFOCUS:
			OnLostFocus();
			return S_OK;

		case WM_SETFOCUS:
			OnGainedFocus();
			return S_OK;

		case WM_DESTROY:
			OnClose();
			return S_OK;

		case WM_PAINT:
			OnPaint();
			return S_OK;

		case WM_KEYDOWN:
			OnKeyDown(wParam);
			return S_OK;

		case WM_SYSKEYDOWN:
			OnSystemKeyDown(wParam);
			return S_OK;

		case WM_SYSKEYUP:
			OnSystemKeyUp(wParam);
			return S_OK;

		case WM_KEYUP:
			OnKeyUp(wParam);
			return S_OK;

		case WM_SIZE:
			OnResize();
			return S_OK;

			// The default window procedure will play a system notification sound 
			// when pressing the Alt+Enter keyboard combination if this message is 
			// not handled.
		case WM_SYSCHAR:
			return S_OK;

		default:
			return DefWindowProcW(windowHandle, messageCode, wParam, lParam);
		}

		return S_FALSE;
	}


	//-------------------------------------------------------------------------------------------------------------
	//---------------------------------------MESSAGE IMPLEMENTATIONS-----------------------------------------------
	//-------------------------------------------------------------------------------------------------------------
	void Window::OnClose()
	{
		PostQuitMessage(0);
	}
	void Window::OnPaint()
	{
		PAINTSTRUCT paintData;
		HDC handleDisplayDevice = BeginPaint(windowHandle, &paintData);
		{
			FillRect(handleDisplayDevice, &paintData.rcPaint, BackgroundColor);
		}
		EndPaint(windowHandle, &paintData);
	}
}