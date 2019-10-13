#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <memory>

#include "SwapChain.h"
#include "GraphicsResource.h"

using namespace Microsoft::WRL;

using std::shared_ptr;

class RenderTargetView : protected GraphicsResource
{
public:
	explicit RenderTargetView(const shared_ptr<const SwapChain> swapChain, const shared_ptr<const GraphicsDevice> graphicsDevice);

	ComPtr<ID3D11RenderTargetView> GetRawRenderTargetView() const;
	void Clear(const float* clearColor) const;

private:
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11Texture2D> backBuffer;
};