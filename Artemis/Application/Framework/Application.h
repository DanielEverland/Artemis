#pragma once

#include "ApplicationCore.h"

namespace ArtemisApplication
{
	class Application
	{
	public:
		Application();

        // Register the window class and call methods for instantiating drawing resources
        HRESULT Initialize();

        // Process and dispatch messages
        void RunMessageLoop();

    private:
        HWND WindowHandle;
        ComPtr<ID2D1Factory> Direct2DFactory;
        ComPtr<ID2D1HwndRenderTarget> RenderTarget;
        ComPtr<ID2D1SolidColorBrush> LightSlateGrayBrush;
        ComPtr<ID2D1SolidColorBrush> CornflowerBlueBrush;
		
        // Initialize device-independent resources.
        HRESULT CreateDeviceIndependentResources();

        // Initialize device-dependent resources.
        HRESULT CreateDeviceResources();

        // Release device-dependent resource.
        void DiscardDeviceResources();

        // Draw content.
        HRESULT OnRender();

        // Resize the render target.
        void OnResize(UINT width, UINT height);

		static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}