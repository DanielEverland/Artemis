#pragma once

#include "DirectXCore.h"
#include "Core.h"

namespace ArtemisEngine
{
	class Renderer;
	class Window;

	class GraphicsDevice
	{
	public:
		GraphicsDevice(Window* targetWindow);
		~GraphicsDevice();

		[[nodiscard]] ComPtr<ID3D11Device> GetRawDevice() const;
		[[nodiscard]] ComPtr<ID3D11DeviceContext> GetRawContext() const;
		[[nodiscard]] ComPtr<ID3D11DepthStencilView> GetRawStencilView() const;
		[[nodiscard]] ComPtr<ID3D11RasterizerState> GetRawRasterizerState() const;
		[[nodiscard]] ComPtr<ID3D11Texture2D> GetRawDepthStencilBuffer() const;
		[[nodiscard]] ComPtr<ID3D11DepthStencilState> GetRawDepthStencilState() const;
		
		void GetMSAASupport(DXGI_FORMAT format, UINT* sampleCount, UINT* quality) const;
		void CreateRenderTargetView(const ComPtr<ID3D11Texture2D>& backBuffer, ComPtr<ID3D11RenderTargetView>& renderTargetView) const;
		void ClearRenderTargetView(const float* clearColor);
		void ClearDepthStencilView();
		void Present();
		
	private:
		static const UINT MSAASampleCount = 4;
		static const std::map<D3D_FEATURE_LEVEL, string> FeatureLevelNames;
		static D3D_FEATURE_LEVEL FeatureLevels[];

		D3D_FEATURE_LEVEL UsedFeatureLevel;
		D3D_FEATURE_LEVEL featureLevel;
		Window* TargetWindow;
		
		ComPtr<ID3D11Device> RawDevice;
		ComPtr<ID3D11DeviceContext> RawContext;
		ComPtr<ID3D11DepthStencilState> RawDepthStencilState;
		ComPtr<ID3D11Texture2D> RawDepthStencilBuffer;
		ComPtr<ID3D11DepthStencilView> RawDepthStencilView;
		ComPtr<ID3D11RasterizerState> RawRasterizerState;
		ComPtr<ID3D11RenderTargetView> RenderTargetView;
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








		///
	public:
		void Initialize(shared_ptr<Renderer> renderer, int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
		void Shutdown();

		void BeginScene(float red, float green, float blue, float alpha);
		void EndScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		void GetProjectionMatrix(XMMATRIX&);
		void GetWorldMatrix(XMMATRIX&);
		void GetOrthoMatrix(XMMATRIX&);

		void GetVideoCardInfo(char*, int&);

	private:
		bool m_vsync_enabled;
		int m_videoCardMemory;
		char m_videoCardDescription[128];
		ComPtr<IDXGISwapChain> m_swapChain;
		XMMATRIX m_projectionMatrix;
		XMMATRIX m_worldMatrix;
		XMMATRIX m_orthoMatrix;
	};
}
