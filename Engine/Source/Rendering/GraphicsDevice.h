#pragma once

#include "DirectXCore.h"
#include "Core.h"

namespace ArtemisEngine
{
	class GraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice();

		[[nodiscard]] ComPtr<ID3D11Device> GetRawDevice() const;
		[[nodiscard]] ComPtr<ID3D11DeviceContext> GetRawContext() const;
		
		void GetMSAASupport(DXGI_FORMAT format, UINT* sampleCount, UINT* quality) const;
		void CreateRenderTargetView(const ComPtr<ID3D11Texture2D>& backBuffer, ComPtr<ID3D11RenderTargetView>& renderTargetView) const;
		

	private:
		static const UINT MSAASampleCount = 4;
		static const std::map<D3D_FEATURE_LEVEL, string> FeatureLevelNames;
		static D3D_FEATURE_LEVEL FeatureLevels[];

		D3D_FEATURE_LEVEL UsedFeatureLevel;
		
		ComPtr<ID3D11Device> RawDevice;
		ComPtr<ID3D11DeviceContext> RawContext;

		string GetFeatureLevelString() const;
		static uint32 GetDeviceFlags();
		void OutputDebugInfo() const;
		string GetGraphicsAdapterString() const;
	};
}
