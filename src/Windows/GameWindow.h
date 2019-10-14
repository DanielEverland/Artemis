#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>

// STL Headers
#include <algorithm>
#include <cassert>
#include <chrono>

#include "Window.h"
#include "..\\Direct X\GraphicsDevice.h"
#include "..\\Direct X\SwapChain.h"
#include "..\\Direct X\DepthBuffer.h"
#include "..\\Direct X\RenderTargetView.h"

// The min/max macros conflict with like-named member functions.
// Only use std::min and std::max defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

using namespace Microsoft::WRL;

using std::chrono::milliseconds;

namespace ArtemisWindow
{
	class GameWindow : public Window
	{
	public:
		explicit GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState);

		inline bool GetUseWARPAdapter() const { return useWARPAdapter; }
		inline void SetUseWARPAdapter(bool value) { useWARPAdapter = value; }

		virtual void Show();

	private:
		static const bool AllowAltEnterFullscreen = false;
		static const uint8_t swapChainBufferSize = 3;
				
		static Color BackbufferColor;

		bool useWARPAdapter = false;

		bool directXInitialized = false;

		RECT previousWindowRect;

		bool fullscreen = false;
		float rawBackBufferColor[4] = {};

		shared_ptr<GraphicsDevice> graphicsDevice;
		shared_ptr<SwapChain> swapChain;
		shared_ptr<RenderTargetView> renderTargetView;
		shared_ptr<DepthBuffer> depthBuffer;

		virtual void RunMessageLoop() final;
		virtual void CreateWindowClass() const;
		virtual HWND CreateWindowHandle();

		void Update();
		void Render();
		void Resize(uint32_t width, uint32_t height);
		void SetFullscreen(bool fullscreen);
		void SwitchToFullscreen();
		void SwitchToWindowed();
		void ToggleVSync();
		void ToggleFullscreen();
		void HandleKeyBindings();
		void OutputFramerate() const;

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
		
		// DirectX
		void InitializeDirectX();
		void CreateDirectXObjects();
		void CreateViewport();
		void CreateRawBackBufferColor();
	};
}