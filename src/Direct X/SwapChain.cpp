#include "SwapChain.h"

SwapChain::SwapChain(UINT width, UINT height, bool windowed, HWND windowHandle, const GraphicsDevice* const graphicsDevice)
{

}
DXGI_SWAP_CHAIN_DESC SwapChain::GetDescription(UINT width, UINT height, bool windowed, HWND windowHandle, const GraphicsDevice* const graphicsDevice)
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
void SwapChain::SetMSAASettings(DXGI_SWAP_CHAIN_DESC* const description, const GraphicsDevice* const graphicsDevice)
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