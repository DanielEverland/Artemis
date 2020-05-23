#ifndef UNICODE
#define UNICODE
#endif

#include "WindowProcedure.h"
#include "Window.h"

#include "Public/Game/Output.h"

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

	void Window::SetFullscreen(bool newFullscreenState)
	{
		if (fullscreen != newFullscreenState)
		{
			fullscreen = newFullscreenState;

			if (fullscreen)
			{
				SwitchToFullscreen();
			}
			else
			{
				SwitchToWindowed();
			}
		}
	}

	void Window::Resize(unsigned int newWidth, unsigned int newHeight)
	{
		if (width != newWidth || height != newHeight)
		{
			width = std::max(1u, newWidth);
			height = std::max(1u, newHeight);

			HasResized();
		}
	}

	void Window::ToggleFullscreen()
	{
		SetFullscreen(!fullscreen);
	}

	void Window::SwitchToFullscreen()
	{
		// Store the current window dimensions so they can be restored 
		// when switching out of fullscreen state.
		GetWindowRect(windowHandle, &previousWindowRect);

		UINT windowStyle = WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
		SetWindowLong(windowHandle, GWL_STYLE, windowStyle);

		HMONITOR monitor = MonitorFromWindow(windowHandle, MONITOR_DEFAULTTONEAREST);
		MONITORINFOEX monitorInfo = { };
		monitorInfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(monitor, &monitorInfo);

		SetWindowPos(windowHandle, HWND_TOP,
			monitorInfo.rcMonitor.left,
			monitorInfo.rcMonitor.top,
			monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
			monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);

		ShowWindow(windowHandle, SW_MAXIMIZE);
	}

	void Window::SwitchToWindowed()
	{
		SetWindowLong(windowHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		SetWindowPos(windowHandle, HWND_NOTOPMOST,
			previousWindowRect.left,
			previousWindowRect.top,
			previousWindowRect.right - previousWindowRect.left,
			previousWindowRect.bottom - previousWindowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);

		ShowWindow(windowHandle, SW_NORMAL);
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