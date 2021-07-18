#pragma once

#include "DirectXCore.h"
#include "Core.h"

namespace ArtemisEngine
{
	class Window;

	class GraphicsDevice
	{
	public:
		GraphicsDevice(Window* targetWindow);
		~GraphicsDevice();

		[[nodiscard]] ComPtr<ID3D11Device> GetRawDevice() const;
		[[nodiscard]] ComPtr<ID3D11DeviceContext> GetRawContext() const;
		[[nodiscard]] ComPtr<ID3D11DepthStencilView> GetRawStencilView() const;
		
		void GetMSAASupport(DXGI_FORMAT format, UINT* sampleCount, UINT* quality) const;
		void CreateRenderTargetView(const ComPtr<ID3D11Texture2D>& backBuffer, ComPtr<ID3D11RenderTargetView>& renderTargetView) const;
		void ClearDepthStencilView();
		
	private:
		static const UINT MSAASampleCount = 4;
		static const std::map<D3D_FEATURE_LEVEL, string> FeatureLevelNames;
		static D3D_FEATURE_LEVEL FeatureLevels[];

		D3D_FEATURE_LEVEL UsedFeatureLevel;
		Window* TargetWindow;
		
		ComPtr<ID3D11Device> RawDevice;
		ComPtr<ID3D11DeviceContext> RawContext;
		ComPtr<ID3D11DepthStencilState> RawDepthStencilState;
		ComPtr<ID3D11Texture2D> RawDepthStencilBuffer;
		ComPtr<ID3D11DepthStencilView> RawDepthStencilView;
		ComPtr<ID3D11RasterizerState> RawRasterizerState;
		D3D11_VIEWPORT Viewport;

		string GetFeatureLevelString() const;
		static uint32 GetDeviceFlags();
		void OutputDebugInfo() const;
		string GetGraphicsAdapterString() const;
		void CreateDevice();
		void CreateDepthStencilBuffer();
		void CreateDepthStencilState();
		void CreateDepthStencilView();
		void CreateRasterizerState();
		void CreateViewport();
	};
}
