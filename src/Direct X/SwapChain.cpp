#include "SwapChain.h"
#include "DirectXHelper.h"

SwapChain::SwapChain(UINT width, UINT height, bool windowed, HWND windowHandle, const ComPtr<GraphicsDevice> const graphicsDevice)
{
	DXGI_SWAP_CHAIN_DESC description = GetDescription(width, height, windowed, windowHandle, graphicsDevice);

	ComPtr<IDXGIFactory> factory = GetFactory();

	HRESULT result = factory->CreateSwapChain(
		graphicsDevice.Get()->GetRawDevice().Get(),
		&description,
		&swapChain);
}
DXGI_SWAP_CHAIN_DESC SwapChain::GetDescription(UINT width, UINT height, bool windowed, HWND windowHandle, const ComPtr<GraphicsDevice> const graphicsDevice)
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
}
DXGI_RATIONAL SwapChain::GetRefreshRate()
{
	DXGI_RATIONAL refreshRate;

	refreshRate.Numerator = 1;
	refreshRate.Denominator = RefreshRate;

	return refreshRate;
}
void SwapChain::SetMSAASettings(DXGI_SWAP_CHAIN_DESC* const description, const ComPtr<GraphicsDevice> const graphicsDevice)
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
ComPtr<IDXGIFactory> SwapChain::GetFactory()
{
	ComPtr<IDXGIDevice> device = 0;	
	ThrowIfFailed(device->QueryInterface(__uuidof(IDXGIDevice), (void**)& device));

	ComPtr<IDXGIAdapter> adapter = 0;
	ThrowIfFailed(device->GetParent(__uuidof(IDXGIAdapter), (void**)&device));

	ComPtr<IDXGIFactory> factory = 0;
	ThrowIfFailed(adapter->GetParent(__uuidof(IDXGIFactory), (void**)&device));
	
	return factory;
}