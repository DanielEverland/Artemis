#include "SwapChain.h"
#include "DirectXHelper.h"

SwapChain::SwapChain(UINT width, UINT height, bool windowed, HWND windowHandle, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	DXGI_SWAP_CHAIN_DESC description = GetDescription(width, height, windowed, windowHandle, graphicsDevice);

	ComPtr<IDXGIFactory> factory = GetFactory(graphicsDevice);

	HRESULT result = factory->CreateSwapChain(
		graphicsDevice->GetRawDevice().Get(),
		&description,
		&swapChain);
}
ComPtr<IDXGISwapChain> SwapChain::GetRawSwapChain() const
{
	return swapChain;
}
DXGI_SWAP_CHAIN_DESC SwapChain::GetDescription(UINT width, UINT height, bool windowed, HWND windowHandle, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	DXGI_MODE_DESC bufferDescription
	{
		width,
		height,
		GetRefreshRate(),
		PixelFormat,
		ScanlineOrder,
		Scaling
	};

	DXGI_SWAP_CHAIN_DESC description;
	description.BufferDesc = bufferDescription;
	description.BufferUsage = BufferUsage;
	description.BufferCount = BufferCount;
	description.OutputWindow = windowHandle;
	description.Windowed = windowed;
	description.SwapEffect = SwapEffect;
	description.Flags = Flags;
	
	SetMSAASettings(&description, graphicsDevice);

	return description;
}
DXGI_RATIONAL SwapChain::GetRefreshRate()
{
	DXGI_RATIONAL refreshRate;

	refreshRate.Numerator = 1;
	refreshRate.Denominator = RefreshRate;

	return refreshRate;
}
void SwapChain::SetMSAASettings(DXGI_SWAP_CHAIN_DESC* const description, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	if (graphicsDevice->SupportsMSAA())
	{
		description->SampleDesc.Count = graphicsDevice->GetMSAASampleCount();
		description->SampleDesc.Quality = graphicsDevice->GetMSAAQuality();
	}
	else
	{
		description->SampleDesc.Count = 1;
		description->SampleDesc.Quality = 0;
	}
}
ComPtr<IDXGIFactory> SwapChain::GetFactory(const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	ComPtr<ID3D11Device> device = graphicsDevice->GetRawDevice();

	ComPtr<IDXGIDevice> dxgiDevice;
	ThrowIfFailed(device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	ComPtr<IDXGIAdapter> adapter = 0;
	ThrowIfFailed(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&adapter));

	ComPtr<IDXGIFactory> factory = 0;
	ThrowIfFailed(adapter->GetParent(__uuidof(IDXGIFactory), (void**)&device));
	
	return factory;
}