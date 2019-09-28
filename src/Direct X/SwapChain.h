#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>

#include <d3d11.h>

#include "GraphicsDevice.h"

using namespace Microsoft::WRL;

class SwapChain
{
public:
	explicit SwapChain(UINT width, UINT height, bool windowed, HWND windowHandle, const ComPtr<GraphicsDevice> const graphicsDevice);

private:
	const static UINT RefreshRate = 60;
	const static DXGI_FORMAT PixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	const static DXGI_MODE_SCANLINE_ORDER ScanlineOrder = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	const static DXGI_MODE_SCALING Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	const static DXGI_USAGE BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	const static DXGI_SWAP_EFFECT SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	const static UINT BufferCount = 1;
	const static UINT Flags = 0;
	
	ComPtr<IDXGISwapChain> swapChain;

	static void SetMSAASettings(DXGI_SWAP_CHAIN_DESC* const description, const ComPtr<GraphicsDevice> const graphicsDevice);
	static DXGI_SWAP_CHAIN_DESC GetDescription(UINT width, UINT height, bool windowed, HWND windowHandle, const ComPtr<GraphicsDevice> const graphicsDevice);
	static ComPtr<IDXGIFactory> GetFactory();
	static DXGI_RATIONAL GetRefreshRate();	
};