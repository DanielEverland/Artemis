#pragma once

#include <SDL_video.h>
#include <d3d11.h>

#include "Core.h"
#include "DirectXCore.h"
#include "GraphicsDevice.h"
#include "RenderTargetView.h"
#include "SwapChain.h"
#include "Application/Window.h"
#include "Core/Color.h"

namespace ArtemisEngine
{
	using namespace std;
	
	class Renderer
	{
	public:
		Renderer(Window* targetWindow);
		~Renderer();

		void DoRender();
	
	private:
		static Color BackbufferColor;
		
		Window* MainWindow;
		float* RawBackbufferColor;

		shared_ptr<GraphicsDevice> Device;
		shared_ptr<SwapChain> SwapChain;
		shared_ptr<RenderTargetView> RenderTargetView;
		
		static uint32 GetDeviceFlags();
		void OutputDebugInfo() const;
		
		void InitializeD3D();
		void CreateRenderTarget();
		void CreateDevice();
		void CreateSwapChain();
	};
}
