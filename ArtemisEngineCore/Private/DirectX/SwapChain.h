#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>
#include <memory>
#include <d3d11.h>

#include "GraphicsDevice.h"
#include "Source/Windows/IWindow.h"

using namespace Microsoft::WRL;
using namespace ArtemisWindow;

using std::shared_ptr;

class SwapChain
{
public:
	explicit SwapChain(const IWindow* window, const shared_ptr<const GraphicsDevice> graphicsDevice);

	ComPtr<IDXGISwapChain> GetRawSwapChain() const;
	void Present() const;
	void Resize() const;
	void GetBuffer(ComPtr<ID3D11Texture2D>& backBuffer) const;
	void Release() const;

private:
#pragma warning(disable : 26812)
	const static UINT RefreshRate = 60;
	const static DXGI_FORMAT PixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	const static DXGI_MODE_SCANLINE_ORDER ScanlineOrder = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	const static DXGI_MODE_SCALING Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	const static DXGI_USAGE BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	const static DXGI_SWAP_EFFECT SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	const static UINT BufferCount = 1;
	const static UINT Flags = 0;
	
	ComPtr<IDXGISwapChain> swapChain;

	const IWindow* window;
	shared_ptr<const GraphicsDevice> graphicsDevice;
#pragma warning(default : 26812)

	DXGI_SWAP_CHAIN_DESC GetDescription();
	ComPtr<IDXGIFactory> GetFactory();

	static DXGI_RATIONAL GetRefreshRate();	
};