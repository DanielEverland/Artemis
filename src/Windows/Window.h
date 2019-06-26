#pragma once

#include "../Main/PrettyWin32.h"
#include "../Structs/Color.h"

using ArtemisEngine::Color;

namespace ArtemisWindow
{
	class Window
	{
	public:

		const UnicodeChar* Title = L"Window Title";

		int WindowBehaviour = 0;
		Color BackgroundColor = Color::White;

		explicit Window(HandleInstance handleInstance, const UnicodeChar* className, int windowState);

		void Show();

	protected:
		const int DefaultXPosition = CW_USEDEFAULT;
		const int DefaultYPosition = CW_USEDEFAULT;
		const int DefaultWidth = CW_USEDEFAULT;
		const int DefaultHeight = CW_USEDEFAULT;
		const long DefaultWindowOptions = WS_OVERLAPPEDWINDOW;
		const UnicodeChar* className;

		HandleInstance handleInstance;
		WindowHandle windowHandle;
		int windowState;

		virtual void RunMessageLoop() const;
		virtual WindowHandle CreateWindowHandle(HandleInstance handleInstance);
		virtual WindowClass CreateWindowClass(HandleInstance handleInstance) const;
		virtual LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);

		// Messages
		LONG_PTR OnClose();
		LONG_PTR OnPaint();

		friend LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
		friend Window* CreateStateInformation(WindowHandle handle, LONG_PTR lParam);
	};
}