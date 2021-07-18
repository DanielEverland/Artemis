#pragma once

#include "Core.h"
#include "SwapChain.h"

namespace ArtemisEngine
{
	class RenderTargetView
	{
	public:
		RenderTargetView(shared_ptr<SwapChain> swapChain, shared_ptr<GraphicsDevice> graphicsDevice);
		void Clear(const float* clearColor) const;

		ComPtr<ID3D11RenderTargetView> GetRawRenderTargetView() const;

	private:
		ComPtr<ID3D11Texture2D> BackBuffer;
		ComPtr<ID3D11RenderTargetView> RawRenderTargetView;
		
		shared_ptr<SwapChain> SwapChain;
		shared_ptr<GraphicsDevice> GraphicsDevice;
	};
}
