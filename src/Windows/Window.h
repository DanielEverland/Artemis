#pragma once

#include "../Structs/Color.h"

using ArtemisEngine::Color;

namespace ArtemisWindow
{
	class Window
	{
	public:

		const WCHAR* Title = L"Window Title";

		int WindowBehaviour = 0;
		Color BackgroundColor = Color::White;

		explicit Window(HINSTANCE handleInstance, const LPCWSTR className, int windowState);

		void Show();

	protected:
		const int DefaultXPosition = CW_USEDEFAULT;
		const int DefaultYPosition = CW_USEDEFAULT;
		const int DefaultWidth = CW_USEDEFAULT;
		const int DefaultHeight = CW_USEDEFAULT;
		const long DefaultWindowOptions = WS_OVERLAPPEDWINDOW;
		
		LPCWSTR className;
		HINSTANCE handleInstance;
		HWND windowHandle;
		int windowState;

		virtual void RunMessageLoop() const;
		virtual HWND CreateWindowHandle();
		virtual void CreateWindowClass() const;
		LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);

		// Messages
		LONG_PTR OnClose();
		LONG_PTR OnPaint();

		friend LONG_PTR CALLBACK WindowProcedure(HWND handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
		friend Window* CreateStateInformation(HWND handle, LONG_PTR lParam);
	};
}