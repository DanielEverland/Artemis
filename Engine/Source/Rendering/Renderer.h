#pragma once

#include <SDL_video.h>
#include <d3d11.h>

#include "Core.h"
#include "DirectXCore.h"
#include "GraphicsDevice.h"
#include "SwapChain.h"
#include "Application/Window.h"

namespace ArtemisEngine
{
	using namespace std;
	
	class Renderer
	{
	public:
		Renderer(Window* targetWindow);
		~Renderer();
	
	private:
		static const std::map<D3D_FEATURE_LEVEL, string> FeatureLevelNames;
		static D3D_FEATURE_LEVEL FeatureLevels[];

		D3D_FEATURE_LEVEL UsedFeatureLevel;
		Window* MainWindow;

		shared_ptr<GraphicsDevice> Device;
		shared_ptr<SwapChain> SwapChain;
		ComPtr<ID3D11DeviceContext> Context;

		static uint32 GetDeviceFlags();
		void OutputDebugInfo() const;
		
		[[nodiscard]] string GetFeatureLevelString() const;
		[[nodiscard]] string GetGraphicsAdapterString() const;

		void InitializeD3D();
		void CreateDevice();
		void CreateSwapChain();
	};
}
