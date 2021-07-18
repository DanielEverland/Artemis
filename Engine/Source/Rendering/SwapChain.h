#pragma once

#include "Core.h"
#include "GraphicsDevice.h"

namespace ArtemisEngine
{
	class Window;
	
	class SwapChain
	{
	public:
		SwapChain(Window* window, shared_ptr<GraphicsDevice> graphicsDevice);
		
		[[nodiscard]] DXGI_SWAP_CHAIN_DESC GetDescription() const;
		[[nodiscard]] DXGI_MODE_DESC GetBufferDescription() const;
		[[nodiscard]] ComPtr<IDXGIFactory> GetFactory() const;
		void GetBuffer(ComPtr<ID3D11Texture2D>& backBuffer) const;
		void Present() const;

	private:
		ComPtr<IDXGISwapChain> RawSwapChain;
		Window* TargetWindow;
		shared_ptr<GraphicsDevice> Device;
	};
}
