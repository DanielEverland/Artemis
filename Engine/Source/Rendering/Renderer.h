#pragma once

#include <SDL_video.h>
#include <d3d11.h>

#include "Core.h"
#include "DirectXCore.h"

namespace ArtemisEngine
{
	using namespace std;
	
	class Renderer
	{
	public:
		Renderer(SDL_Window* targetWindow);
	
	private:
		static const std::map<D3D_FEATURE_LEVEL, string> FeatureLevelNames;
		static D3D_FEATURE_LEVEL FeatureLevels[];

		D3D_FEATURE_LEVEL UsedFeatureLevel;
		SDL_Window* Window;
		ComPtr<ID3D11Device> Device;
		ComPtr<ID3D11DeviceContext> Context;

		static uint32 GetDeviceFlags();
		void OutputDebugInfo() const;
		
		[[nodiscard]] string GetFeatureLevelString() const;
		[[nodiscard]] string GetGraphicsAdapterString() const;

		void InitializeD3D();
	};
}
