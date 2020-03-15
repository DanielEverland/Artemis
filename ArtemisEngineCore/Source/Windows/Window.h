#pragma once

#include <algorithm>
#include <stdint.h>

#include "IWindow.h"
#include "Include/Game/Color.h"

// The min/max macros conflict with like-named member functions.
// Only use std::min and std::max defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

using ArtemisEngine::Color;

namespace ArtemisWindow
{
	class Window : public IWindow
	{
	public:
		const WCHAR* Title = L"Window Title";

		int WindowBehaviour = 0;
		Color BackgroundColor = Color::White;

		explicit Window(HINSTANCE handleInstance, const LPCWSTR className, int windowState);

		inline unsigned int GetWidth() const { return width; }
		inline void SetWidth(unsigned int value) { width = value; }

		inline unsigned int GetHeight() const { return height; }
		inline void SetHeight(unsigned int value) { height = value; }

		inline HWND GetHandle() const { return windowHandle; }

		virtual void Show();

	protected:
		static const bool AllowAltEnterFullscreen = false;

		const int DefaultXPosition = CW_USEDEFAULT;
		const int DefaultYPosition = CW_USEDEFAULT;
		const int DefaultWidth = CW_USEDEFAULT;
		const int DefaultHeight = CW_USEDEFAULT;
		const long DefaultWindowOptions = WS_OVERLAPPEDWINDOW;
		
		unsigned int width = 1280;
		unsigned int height = 720;

		LPCWSTR className;
		HINSTANCE handleInstance;
		HWND windowHandle;
		int windowState;
		bool fullscreen = false;
		RECT previousWindowRect;

		void Resize(unsigned int width, unsigned int height);

		virtual void SetFullscreen(bool fullscreen);
		virtual void SwitchToFullscreen();
		virtual void SwitchToWindowed();
		virtual void ToggleFullscreen();
		virtual void HasResized() { }

		virtual void RunMessageLoop() const;
		virtual HWND CreateWindowHandle();
		virtual void CreateWindowClass() const;
		virtual LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
		
		// Messages
		virtual void OnClose();
		virtual void OnPaint();
		virtual void OnSystemKeyDown(UINT_PTR wParam) { }
		virtual void OnSystemKeyUp(UINT_PTR wParam) { }
		virtual void OnKeyDown(UINT_PTR wParam) { }
		virtual void OnKeyUp(UINT_PTR wParam) { }
		virtual void OnResize() { }
		virtual void OnLostFocus() { }
		virtual void OnGainedFocus() { }

		friend LONG_PTR CALLBACK WindowProcedure(HWND handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
		friend Window* CreateStateInformation(HWND handle, LONG_PTR lParam);
	};
}