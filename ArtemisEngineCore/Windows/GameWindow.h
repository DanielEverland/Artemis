#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>

#include <memory>
#include <cassert>
#include <chrono>

#include "Window.h"
#include "Direct X/Renderer.h"

using namespace Microsoft::WRL;

using std::chrono::milliseconds;

namespace ArtemisWindow
{
	class GameWindow : public Window
	{
	public:
		explicit GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState);
		
		inline shared_ptr<Renderer> GetRenderer() { return renderer; }

		inline bool IsFullscreen() const { return fullscreen; }

		virtual void Show() override;

	private:
		shared_ptr<Renderer> renderer;

		virtual void RunMessageLoop() final;
		virtual void CreateWindowClass() const;
		virtual HWND CreateWindowHandle();

		void Update();
		void Render();
		
		void InitializeRenderer();
		void ToggleVSync();
		void HandleKeyBindings();
		void OutputFramerate() const;
		virtual void HasResized() override;

		// Messages
		virtual LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
		virtual void OnPaint();
		virtual void OnSystemKeyDown(UINT_PTR wParam);
		virtual void OnSystemKeyUp(UINT_PTR wParam);
		virtual void OnKeyDown(UINT_PTR wParam);
		virtual void OnKeyUp(UINT_PTR wParam);
		virtual void OnResize();
		virtual void OnClose();
		virtual void OnGainedFocus();
	};
}