#include <assert.h>

#include "SwapChain.h"
#include "DirectXHelper.h"

#include "Public/Game/Application.h"

SwapChain::SwapChain(const IWindow* window, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	this->window = window;
	this->graphicsDevice = graphicsDevice;

	DXGI_SWAP_CHAIN_DESC description = GetDescription();
	ComPtr<IDXGIFactory> factory = GetFactory();

	ThrowIfFailed(factory->CreateSwapChain(
		graphicsDevice->GetRawDevice().Get(),
		&description,
		&swapChain));
}

void SwapChain::GetBuffer(ComPtr<ID3D11Texture2D>& backBuffer) const
{
	ThrowIfFailed(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
}

void SwapChain::Present() const
{
	ThrowIfFailed(swapChain->Present(Application::GetVSync(), 0));
}

void SwapChain::Resize() const
{
	ThrowIfFailed(swapChain->ResizeBuffers(BufferCount, window->GetWidth(), window->GetHeight(), PixelFormat, Flags));
}

void SwapChain::Release() const
{
	swapChain->Release();
}

ComPtr<IDXGISwapChain> SwapChain::GetRawSwapChain() const
{
	return swapChain;
}

DXGI_SWAP_CHAIN_DESC SwapChain::GetDescription()
{
	DXGI_MODE_DESC bufferDescription
	{
		window->GetWidth(),
		window->GetHeight(),
		GetRefreshRate(),
		PixelFormat,
		ScanlineOrder,
		Scaling
	};

	DXGI_SWAP_CHAIN_DESC description;
	description.BufferDesc = bufferDescription;
	description.BufferUsage = BufferUsage;
	description.BufferCount = BufferCount;
	description.OutputWindow = window->GetHandle();
	description.Windowed = window->IsWindowed();
	description.SwapEffect = SwapEffect;
	description.Flags = Flags;

	graphicsDevice->GetMSAASupport(bufferDescription.Format, &description.SampleDesc.Count, &description.SampleDesc.Quality);

	return description;
}
DXGI_RATIONAL SwapChain::GetRefreshRate()
{
	DXGI_RATIONAL refreshRate;

	refreshRate.Numerator = 1;
	refreshRate.Denominator = RefreshRate;

	return refreshRate;
}
ComPtr<IDXGIFactory> SwapChain::GetFactory()
{
	ComPtr<ID3D11Device> device = graphicsDevice->GetRawDevice();

	ComPtr<IDXGIDevice> dxgiDevice;
	ThrowIfFailed(device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	ComPtr<IDXGIAdapter> adapter = 0;
	ThrowIfFailed(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&adapter));
	
	ComPtr<IDXGIFactory> factory = 0;
	ThrowIfFailed(adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory));
	
	return factory;
}